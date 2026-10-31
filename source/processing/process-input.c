/// @file processing/process-input.c

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"
#include "options/options.h"
#include "features/features.h"
#include "parsing/parse-file.h"

#include "model/global.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define printError(path_) \
	fprintf(stderr, "\33[31m%s: %s: %s\33[m\n", argv0, path_, strerror(errno))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── processChild ── ─────────────────────────────────────────────────────────────────────────────────────────── */

static inline void processChild(FileStat *const pFS_child, const struct dirent *const pDT_child) {
	/* —— basic child info (dirent) ——————————————————————————————— */

	// +1 for the nullbyte
	char *child_name = emalloc(pDT_child->d_namlen + 1); /* [alloc:child-name] - freed locally */

	// copy the info from `dirent` over to the child's `FileStat` object
	*pFS_child = (FileStat){
		// allocate memory for the name, since the `dirent` memory won't last forever
		.name		= child_name,
		.name_len	= pDT_child->d_namlen,
		.mode		= DTTOIF(pDT_child->d_type), // converting to the correct format
		.inum		= pDT_child->d_ino,
		// make sure to copy the parent over too, so that it's not set to `NULL`
		.parent		= pFS_child->parent,
	};

	// copy the name from `dirent` to `FileStat`
	//	we're using `memcpy` and not `strcpy` since we already know how long the string is
	memcpy(pFS_child->name, pDT_child->d_name, pDT_child->d_namlen + 1);

	/* —— get path to child ——————————————————————————————————————— */

	// none of these files should be parentless - its pretty much impossible
	assert(pFS_child->parent != NULL);

	if (( pFS_child->path	 =	  getPath(pFS_child) ) == NULL) return;
	if (( pFS_child->abspath = getAbsPath(pFS_child) ) == NULL) return;

	// rather than being its own data, a file's name is now a pointer to where its name starts in `.path`
	//	this saves having to alloc memory for its name (hence the `free` here), and having to store the path's length
	efree(child_name); /* [free:child-name] - alloced locally */

	/* —— `stat` child file ——————————————————————————————————————— */

	// allocate the memory for the child's `stat` struct
	pFS_child->s = emalloc(sizeof(struct stat)); /* [alloc:fsstat] - freed in `printFile`; locally if error */

	// run `lstat` on the path
	if (lstat(pFS_child->abspath, pFS_child->s) == -1) {
		// if it fails, note down the errno
		pFS_child->err_no = errno;

		// free the memory we allocated for the file's `stat` object
		efree(pFS_child->s); /* [free:IF-ERROR] - alloced locally */
		// then set the pointer to all its remaining elements to NULL, so we know not to process it later
		pFS_child->s = NULL;
		pFS_child->f = NULL;

		// and move on to the next child
		return;
	}

	// finally, if all of that succeeded, allocate some zeroed memory for the child's FSF object
	pFS_child->f = ecalloc(1, sizeof(FileStatFields)); /* [alloc:filestat] - freed in `printFile` */
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── processDir ── ───────────────────────────────────────────────────────────────────────────────────────────── */

static inline FileStat *processDir(FileStat *const pFS_dir, const uint8_t depth) {

	/* —— Open Dir & Error Check —————————————————————————————————— */

	// if the file is a link, open the link's target instead of the file - symlinks will work fine, but it's
	//	especially important to do for apple aliases, since they won't automatically be interpreted as directories
	const bool do_open_alias_link = ((S_ISLNK(pFS_dir->mode) || S_ISREG(pFS_dir->mode)) && isFSDir(pFS_dir));
	const char *const dir_to_open = do_open_alias_link ? pFS_dir->f->target->path : pFS_dir->abspath;

	// firstly, open the directory and get a pointer to a `DIR` object
	//	note: we can't get any info from `DIR`, it's use is to be passed into other functions
	DIR *const p_dir = opendir(dir_to_open);

	if (p_dir == NULL) { // if we can't open the directory...
		// set the number of children to -1, so we know the difference between having 0 children,
		//	and not being able to search for children
		pFS_dir->f->child_count = -1;
		pFS_dir->err_no = errno;

		// even though we didn't get any of the dir's contents, this shouldn't be too bad for the base directory itself
		//	since we `stat`ted it back when we were treating it like any other file, but the children will be an issue
		return pFS_dir;
	}

	/* —— Set up `children` Array ————————————————————————————————— */

	// allocate some memory for an arbitrary number of children, with the intention that
	//	we'll realloc if we need more memory later
	int32_t child_alloc_count = INIT_CHILD_COUNT;

	pFS_dir->f->children = ecalloc(child_alloc_count, sizeof(FileStat)); /* [alloc:children] - freed in `printFile` */
	FileStat **const children = &pFS_dir->f->children;

	/* —— For Each Child in Dir ——————————————————————————————————— */

	// iterate through the directory until you run out of children (or there's an error)
	const struct dirent *pDT_child;
	while (( pDT_child = readdir(p_dir) ) != NULL) {

		/* —— check for dotdir ———————————————————————————————————————— */

		// if this child has the name ".", then it's not a child, but the dir itself
		if (strcmp(pDT_child->d_name, DOTDIR) == 0) {
			// get the few pieces of information that we care about from the `dirent` object
			// note: we're not keeping `d_name` or `d_namlen`, since these would just
			//	return "." and 1 respectively, which isn't much help to us
			if ((pFS_dir->mode & PERM_MASK)	== 0) pFS_dir->mode = DTTOIF(pDT_child->d_type);
			if ((pFS_dir->inum)				== 0) pFS_dir->inum = pDT_child->d_ino;

			continue; // continue - the rest of the information we need is already in `pFS_dir->s`
		}

		/* —— check for ignored files ————————————————————————————————— */

		// if we're ignoring dotfiles (and dirs), then check for dotfiles, and ignore them
		if ((!DO_DOTFILES() && pDT_child->d_name[0] == '.')
			// and always ignore `..` - with the output structure I'm building, it doesn't make sense to show it
			|| strcmp(pDT_child->d_name, "..") == 0
		) continue;

		/* —— alloc mem for children —————————————————————————————————— */

		if (pFS_dir->f->child_count >= child_alloc_count) {
			const int32_t old_alloc_count = child_alloc_count; // save the old capacity before multiplying

			// if the number of children (before we increment it) is more than we have space for,
			//	then increase the number of children we have space for, by a factor of 1.5.
			// 1.5 is the optimal multiplier to make sure we don't over-allocate memory, but also so that
			//	we aren't constantly allocating it either
			MULT_BY_1_5(child_alloc_count);

			// re-allocate the memory. note that `[e]realloc` will free the original pointer and hard exit if it
			//	fails, so we don't have to worry about memory leaks by overwriting the original pointer
			*children = erealloc(*children, sizeof(FileStat) * child_alloc_count);

			// zero out the new memory that we were just allocated
			//	this isn't strictly necessary, but it could prove rly useful for debugging
			//	(I might remove it later if I don't think it's needed)
			memset(*children + old_alloc_count, 0, sizeof(FileStat) * (child_alloc_count - old_alloc_count));
		}

		/* —— set up & process child —————————————————————————————————— */

		// find the position where the child's `FileStat` object will start, and increment the child count
		FileStat *const pFS_child = *children + pFS_dir->f->child_count++;

		// assign this directory as the child's parent
		pFS_child->parent = pFS_dir;

		// then send the child off for processing
		processChild(pFS_child, pDT_child);

		/* —— recurse into child —————————————————————————————————————— */

		// now parse the file - i.e. go through and convert things from raw data into displayable output
		parseFile(pFS_child);

		// now that the child's been processed & parsed, check if we should recurse into it to calculate deeper
		if (isFSDir(pFS_child) && depth + 1 <= MAX_DEPTH && !(pFS_child->s->st_flags & SF_DATALESS)) {
			// if we should, then process the child in the same way we processed this dir
			processDir(pFS_child, depth + 1);
		}
	}

	assert(isValidFS(pFS_dir));

	closedir(p_dir);
	return pFS_dir;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── processInput ── ─────────────────────────────────────────────────────────────────────────────────────────── */

/**
 * @fn processInput
 * @brief Process an inputted file, getting all information necessary from it.
 *
 * Note: The reason I'm recursing from `processDir`, and not from this function, is because input files and child files
 *	are processed & handled differently:
 *
 *		- For input files, I first run `lstat` on them, and immediately return if they fail (cos I can't get any other
 *			useful information from them).
 *		- However, for child files, I first get their `dirent` information, and only then do I try and run `lstat` on
 *			them. So it doesn't matter if `lstat` fails, because I'll still have _something_ to display.
 *
 * This is all due to the fact that a dirent object can only be gotten from iterating over the parent directory, which
 *	I don't have when given just the input.
 *
 * @param path[in] A string containing the path to the input file.
 * @return `FileStat`: The `FileStat` object generated from the input file. An empty object on failure.
 */
FileStat *processInput(char *const path) {
	// bite the bullet and use `strlen` to calculate the file's length now,
	//	bc we need it to properly get the absolute path.
	const size_t input_len = strlen(path);
	const char *abs_path = NULL;
	namlen_t abs_len = -1;

	assert(input_len <= INT16_MAX && input_len <= MAX_PATH_LEN);

	// get the absolute path to the input - this is the only way we can 100% guarantee that we get
	//	accurate results from `lstat` - especially in the case where the input is a symlinked dir
	getPureAbsPath(&abs_path, &abs_len, path, input_len);

	/* —— assign basic info to input —————————————————————————————— */

	FileStat *const pFS = emalloc(sizeof(FileStat));
	*pFS = (FileStat){
		// since `path` comes from `file_paths`, which comes from `argv`, the memory containing `file->name`
		//	doesn't need to be allocated, since pointers to `argv` exist through the lifetime of the program
		.name = path,
		.name_len = input_len,

		// copy over the absolute path and its size, so we don't have to calculate it again
		.abspath = abs_path,
		.abs_len = abs_len,

		// note: `s` is using `malloc`, since it's going to be assigned to immediately,
		//	and, `f` is using `calloc`, since I want to set everything to 0/NULL/false before I start processing

		// allocate memory for the `stat` object that will be pointed to by `FileStat::s`
		.s = emalloc(sizeof(struct stat)), /* [alloc:fsstat-input] - freed in `printFile` */
		// finally, allocate memory for the `FileStatFields` object, and assign its pointer to the FileStat object
		.f = ecalloc(1, sizeof(FileStatFields)), /* [alloc:filestat-input] - freed in `printFile` */
	};

	/* —— `stat` input file ——————————————————————————————————————— */

	// firstly, try to run `lstat` on the input path
	//	the reason we're `stat`ting the file upfront is because we absolutely _need_ to know
	//	whether its a directory or not, so we might as well store the stat information if we have it
	// pass the absolute path, however, if `getPureAbsPath` failed, fall back to the original input path
	if (lstat(( abs_path ? abs_path : path ), pFS->s) == -1) {
		if (errno == ENOENT) { /** @todo handle */ }

		// if it fails, free all the allocated memory, print an error, and move onto the next file
		efree((void*)pFS->abspath);
		efree((void*)pFS->s);
		efree((void*)pFS->f);

		printError(path);

		// set the pointer to this input to NULL, so we know not to process/print it later
		return NULL;
	}

	FileStat *output = pFS;

	// parse the info in `pFS`, so we know whether its a link to a directory or not
	//	but don't recurse into it, since we won't have any of the information from `processChild`
	parseFile(pFS);

	// if the input was just a file, i.e. not a dir (or if we're treating dirs as if they were files),
	//	or if we've reached the max depth, or the directory is dataless
	//	then there's nothing else to do at this stage - send it off for parsing
	if (isFSDir(pFS) && !(MAX_DEPTH == 0 || pFS->s->st_flags & SF_DATALESS)) {
		// if the input was a directory, however, we need to find & process its children
		output = processDir(pFS, 1);
	}

	return output;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
