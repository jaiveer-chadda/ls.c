/// @file processing/process-input.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"
#include "options/options.h"

#include "model/global.h"
#include "model/new-stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// Approximately multiplies a number by 1.5
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

#define printError(path_, errmsg) \
	fprintf(stderr, "\33[31m%s: %s: %s\33[m\n", argv0, path_, errmsg)

/* ── ── processChild ── ─────────────────────────────────────────────────────────────────────────────────────────── */

static inline void processChild(
	FileStat *pFS_child,
	const struct dirent *const pdirent_child,
	const char *const dirpath,
	const int16_t dirpath_len
) {
	/* —— basic child info (dirent) ——————————————————————————————— */

	// copy the info from `dirent` over to the child's `FileStat` object
	*pFS_child = (FileStat){
		// allocate memory for the name, since the `dirent` memory won't last forever
		.name		= emalloc(pdirent_child->d_namlen + 1), // +1 for the nullbyte
		.name_len	= pdirent_child->d_namlen,
		.type		= DTTOIF(pdirent_child->d_type), // converting to the correct format
		.inum		= pdirent_child->d_ino,
	};

	// copy the name from `dirent` to `FileStat`
	//	we're using `memcpy` and not `strcpy` since we already know how long the string is
	memcpy(pFS_child->name, pdirent_child->d_name, pdirent_child->d_namlen + 1);

	/* —— get path to child ——————————————————————————————————————— */

	// make sure that the resultant child path won't be too long once we create it
	if ((size_t)(dirpath_len + 1 + pFS_child->name_len) >= sizeof(path_t)) {
		printError(pFS_child->name, "path name too long");
		return;
	}

	// allocate the memory for the child's `stat` struct
	pFS_child->s = emalloc(sizeof(struct stat));

	// create a buffer to hold the path needed to pass to `stat`
	path_t child_path = "";

	// build the full path to the child from its component parts
	memcpy(child_path, dirpath, dirpath_len); // no need to include the nullbyte, so no +1
	child_path[dirpath_len] = '/'; // add the path separator
	memcpy(child_path + 1 + dirpath_len, pFS_child->name, pFS_child->name_len + 1); // +1 for '\0' this time

	/* —— `stat` child file ——————————————————————————————————————— */

	// run `lstat` on the path
	if (lstat(child_path, pFS_child->s) == -1) {
		// if it fails, print an error
		#ifdef DEBUG_MODE
			debug(WARNING, "failed to `stat`: %s", child_path);
		#else
			printError(child_path, strerror(errno));
		#endif

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

/* ── ── processDir ── ───────────────────────────────────────────────────────────────────────────────────────────── */

static inline FileStat *processDir(char *const dirpath, FileStat *pfilestat_dir) {
	// firstly, open the directory and get a pointer to a `DIR` object
	//	note: we can't get any info from `DIR`, it's use is to be passed into other functions
	DIR *p_dir = opendir(dirpath);

	if (p_dir == NULL) { // if we can't open the directory...
		// set the number of children to -1, so we know the difference between having 0 children,
		//	and not being able to search for children
		pfilestat_dir->f->child_count = -1;

		printError(dirpath, strerror(errno));

		// make sure to close the dir - memory leaks!!
		closedir(p_dir);

		// even though we didn't get any of the dir's contents, this shouldn't be too bad for the base directory itself
		//	since we `stat`ted it back when we were treating it like any other file, but the children will be an issue
		return pfilestat_dir;
	}

	// bite the bullet and use `strlen` to calculate the dir's length now,
	//	bc we're going to need it to get the path to the children in a moment
	const int16_t dirpath_len = (int16_t)strlen(dirpath);
	pfilestat_dir->name_len = dirpath_len;

	// allocate some memory for an arbitrary number of children, with the intention that
	//	we'll realloc if we need more memory later
	int32_t child_alloc_count = INIT_CHILD_COUNT;

	pfilestat_dir->f->children = ecalloc(child_alloc_count, sizeof(FileStat));
	FileStat **children = &pfilestat_dir->f->children;

	/* —— For Each Child in Dir ——————————————————————————————————— */

	// iterate through the directory until you run out of children (or there's an error)
	const struct dirent *pdirent_child;
	while (( pdirent_child = readdir(p_dir) ) != NULL) {

		/* —— check for dotdir ———————————————————————————————————————— */

		// if this child has the name ".", then it's not a child, but the dir itself
		if (strcmp(pdirent_child->d_name, DOTDIR) == 0) {
			// get the few pieces of information that we care about from the `dirent` object
			// note: we're not keeping `d_name` or `d_namlen`, since these would just
			//	return "." and 1 respectively, which isn't much help to us
			pfilestat_dir->type = DTTOIF(pdirent_child->d_type);
			pfilestat_dir->inum = pdirent_child->d_ino;

			continue; // continue - the rest of the information we need is already in `pfilestat_dir->s`
		}

		/* —— check for ignored files ————————————————————————————————— */

		// with the output structure I'm building, I don't think it makes sense to show `..`
		//	if I want to add an option to keep it later, I can just add it to this condition
		if (strcmp(pdirent_child->d_name, "..") == 0) continue;
		// note: when I add the `-a` and `-A` options later, this is where I'll add a check for them

		/* —— alloc mem for children —————————————————————————————————— */

		if (pfilestat_dir->f->child_count >= child_alloc_count) {
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

		// find the position where the child's `FileStat` object will start
		FileStat *pFS_child = *children + pfilestat_dir->f->child_count;

		// only increment the child count now that we've used it as an index to calculate where the child should be
		pfilestat_dir->f->child_count++;

		processChild(pFS_child, pdirent_child, dirpath, dirpath_len);
	}

	closedir(p_dir);
	return pfilestat_dir;
}

/* ── ── processInput ── ─────────────────────────────────────────────────────────────────────────────────────────── */

FileStat *processInput(char *path) {
	struct stat statobj = {0};

	/* —— `stat` input file ——————————————————————————————————————— */

	// firstly, try to run `lstat` on the input path
	//	the reason we're `stat`ting the file upfront is because we absolutely _need_ to know
	//	whether its a directory or not, so we might as well store the stat information if we have it
	if (lstat(path, &statobj) == -1) {
		// if it fails, print an error and move onto the next file
		const int stat_errno = errno;
		if (stat_errno == ENOENT) { /* handle */ }

		printError(path, strerror(stat_errno));

		// set the pointer to this input to NULL, so we know not to process/print it later
		return NULL;
	}

	// file was `stat`ted successfully

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
	if (!S_ISDIR(statobj.st_mode) || DIRS_AS_FILES())
		return pfilestat;

	// if the input was a directory, however, we need to find & process its children
	return processDir(path, pfilestat);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
