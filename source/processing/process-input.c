/// @file processing/process-input.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"
#include "options/options.h"

#include "model/global.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// Approximately multiplies a number by 1.5
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

#define printError(path_) \
	fprintf(stderr, "\33[31m%s: %s: %s\33[m\n", argv0, path_, strerror(errno))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getPath ── ──────────────────────────────────────────────────────────────────────────────────────────────── */

/**
 * @fn getPath
 * @brief Get the path to the given file, relative to its most senior parent.
 */
static inline char *getPath(FileStat *const file) {
	// if we've already found this path before, then just return a pointer to it
	if (file->path != NULL) return file->path;

	FileStat *const parent = file->parent;

	// base case: if this file doesn't have any parents, then we know that its name is already a valid path
	if (parent == NULL) {
		file->path_len = file->name_len;
		return file->name;
	}

	/* —————————————————————————————————————————————————————— */

	// allocate memory for this file's path, then copy the parent dir's path into the buffer - recurse if needed
	//	(note: no need to include the nullbyte, so no +1 for the length)
	char *const path = memcpy(emalloc(sizeof(path_t)), getPath(parent), parent->path_len);
	//v)path = "/path/to/parent"

	/* —————————————————————————————————————————————————————— */

	// only check the full size after we know that the parent definitely has a path
	const size_t full_size = parent->path_len + 1 + file->name_len;
	// make sure that the resultant child path won't be too long once we create it
	if (full_size >= sizeof(path_t)) { efree(path); return NULL; }

	/* —————————————————————————————————————————————————————— */

	// add the path separator
	path[parent->path_len] = '/';
	//v)path = "/path/to/parent/"

	// append the file's name to the end of the path
	memcpy(path + 1 + parent->path_len,
		file->name,
		file->name_len + 1 // +1 for the nullbyte this time
	);
	//v)path = "/path/to/parent/child_name"

	/* —————————————————————————————————————————————————————— */

	file->path_len = full_size;
	return path;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── processChild ── ─────────────────────────────────────────────────────────────────────────────────────────── */

static inline void processChild(FileStat *pFS_child, const struct dirent *const pDT_child) {
	/* —— basic child info (dirent) ——————————————————————————————— */

	// copy the info from `dirent` over to the child's `FileStat` object
	*pFS_child = (FileStat){
		// allocate memory for the name, since the `dirent` memory won't last forever
		.name		= emalloc(pDT_child->d_namlen + 1), // +1 for the nullbyte
		.name_len	= pDT_child->d_namlen,
		.mode		= DTTOIF(pDT_child->d_type), // converting to the correct format
		.inum		= pDT_child->d_ino,
		// make sure to copy the parent over too, so it's not set to `NULL`
		.parent		= pFS_child->parent,
	};

	// copy the name from `dirent` to `FileStat`
	//	we're using `memcpy` and not `strcpy` since we already know how long the string is
	memcpy(pFS_child->name, pDT_child->d_name, pDT_child->d_namlen + 1);

	/* —— get path to child ——————————————————————————————————————— */

	if (( pFS_child->path = getPath(pFS_child) ) == NULL) return;

	/* —— `stat` child file ——————————————————————————————————————— */

	// allocate the memory for the child's `stat` struct
	pFS_child->s = emalloc(sizeof(struct stat));

	// run `lstat` on the path
	if (lstat(pFS_child->path, pFS_child->s) == -1) {
		// if it fails, note down the errno
		pFS_child->err_no = errno;

		// free the memory we allocated for the file's `stat` object
		efree(pFS_child->s);
		// then set the pointer to all its remaining elements to NULL, so we know not to process it later
		pFS_child->s = NULL;
		pFS_child->f = NULL;

		// and move on to the next child
		return;
	}

	// finally, if all of that succeeded, allocate some zeroed memory for the child's FSF object
	pFS_child->f = ecalloc(1, sizeof(FileStatFields));
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── processDir ── ───────────────────────────────────────────────────────────────────────────────────────────── */

static inline FileStat *processDir(FileStat *pFS_dir, const uint8_t depth) {
	const char *const dirpath = getPath(pFS_dir);

	/* —— Open Dir & Error Check —————————————————————————————————— */

	// firstly, open the directory and get a pointer to a `DIR` object
	//	note: we can't get any info from `DIR`, it's use is to be passed into other functions
	DIR *p_dir = opendir(dirpath);

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

	// bite the bullet and use `strlen` to calculate the dir's length now,
	//	bc we're going to need it to get the path to the children in a moment
	const int16_t dirpath_len = (int16_t)strlen(dirpath);
	pFS_dir->name_len = dirpath_len;

	// allocate some memory for an arbitrary number of children, with the intention that
	//	we'll realloc if we need more memory later
	int32_t child_alloc_count = INIT_CHILD_COUNT;

	pFS_dir->f->children = ecalloc(child_alloc_count, sizeof(FileStat));
	FileStat **children = &pFS_dir->f->children;

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
			pFS_dir->mode = DTTOIF(pDT_child->d_type);
			pFS_dir->inum = pDT_child->d_ino;

			continue; // continue - the rest of the information we need is already in `pFS_dir->s`
		}

		/* —— check for ignored files ————————————————————————————————— */

		// with the output structure I'm building, I don't think it makes sense to show `..`
		//	if I want to add an option to keep it later, I can just add it to this condition
		if (strcmp(pDT_child->d_name, "..") == 0) continue;
		/// @todo when I add the `-a` and `-A` options later, this is where I'll add a check for them

		#ifdef DEBUG_MODE
		if (strcmp(pDT_child->d_name, ".git") == 0) continue;
		#endif

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
		FileStat *pFS_child = *children + pFS_dir->f->child_count++;

		// assign this directory as the child's parent
		pFS_child->parent = pFS_dir;

		// then send the child off for processing
		processChild(pFS_child, pDT_child);

		/* —— recurse into child —————————————————————————————————————— */

		// now that the child's been processed, check if we should recurse into it to calculate deeper
		if (!S_ISDIR(pFS_child->mode) || depth + 1 > MAX_DEPTH || pFS_child->f == NULL) continue;
		// if we should, then process the child in the same way we processed this dir
		processDir(pFS_child, depth + 1);
	}

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
 * @return `FileStat*`: A pointer to the `FileStat` object generated from the input file. `NULL` on failure.
 */
FileStat *processInput(char *const path) {
	struct stat statobj = {0};

	/* —— `stat` input file ——————————————————————————————————————— */

	// firstly, try to run `lstat` on the input path
	//	the reason we're `stat`ting the file upfront is because we absolutely _need_ to know
	//	whether its a directory or not, so we might as well store the stat information if we have it
	if (lstat(path, &statobj) == -1) {
		// if it fails, print an error and move onto the next file
		if (errno == ENOENT) { /* handle */ }

		printError(path);
		// set the pointer to this input to NULL, so we know not to process/print it later
		return NULL;
	}

	/* —— alloc FileStat for Input ———————————————————————————————— */
	// since we successfully got the `stat` information, we can start building the `FileStat` object

	// allocate memory for this file's `FileStat` object, and zero the memory
	// and add its pointer to the input array
	FileStat *const pfilestat = ecalloc(1, sizeof(FileStat));

	/* —— assign basic info to input —————————————————————————————— */

	*pfilestat = (FileStat){
		// since `path` comes from `file_paths`, which comes from `argv`, the memory containing `pfilestat->name`
		//	doesn't need to be allocated, since pointers to `argv` exist through the lifetime of the program
		.name = path,
		// we don't know the name's length, so set it to -1 for now, and we can calculate it later if needed
		.name_len = -1,

		// allocate memory for the `stat` object that will be pointed to by `FileStat::s`
		.s = emalloc(sizeof(struct stat)),
		// finally, allocate memory for the `FileStatFields` object, and assign its pointer to the FileStat object
		.f = ecalloc(1, sizeof(FileStatFields)),
	};

	// copy `statobj` from the stack into the newly-allocated heap memory at `FileStat::s pfilestat->s`
	memcpy(pfilestat->s, &statobj, sizeof(struct stat));

	/* —— Check if Input is Dir ——————————————————————————————————— */

	// if the input was just a file, i.e. not a dir (or if we're treating dirs as if they were files),
	//	then there's nothing else to do at this stage - send it off for parsing
	if (!S_ISDIR(statobj.st_mode) || !RECURSE_DIRS())
		return pfilestat;

	// if the input was a directory, however, we need to find & process its children
	return processDir(pfilestat, 1);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore prnt
