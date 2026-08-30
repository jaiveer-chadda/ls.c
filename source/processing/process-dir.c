/// @file processing/process-dir.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process-dir.h"

#include "utils/malloc.h"
#include "output/output.h"
#include "form/formatting.h"
#include "options/options.h"
#include "info/sorting/sort.h"

#include "features/path/path.h"

#include "debugging.h"

// `is_first` will be unused when compiled in debug mode
#ifdef DEBUG_MODE
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

void processDirectory(char *path, DIR *dir, const bool do_free_path_0, const bool is_first) {
	// Resolve the path to the target directory, which'll be used to replace the `.` directory's name
	//  (casting to void, since there's nth we can rly do if we don't manage to get it)
	(void)getDirPath(G_DOTDIR_PATH, path);

	/* —— Get File Info from `stat` —————————————————————————————————————————————————————————————— */

	FileInfo
		*dirs  = emalloc(MAX_CHILDREN * sizeof(FileInfo)),
		*files = emalloc(MAX_CHILDREN * sizeof(FileInfo));

	int dir_count, file_count;

	// Run the `stat` and `lstat` syscalls, and start parsing the files' information
	getAllFileInfo(
		dirs, files,
		&dir_count, &file_count,
		dir, path
	);

	// the directory info isn't needed anymore - it can be closed
	closedir(dir);

	// If we need to free `path[0]`, and this input is `path[0]`, then free it
	//	Memory was allocated in `main()`
	if (do_free_path_0 && is_first) free(path);

	/* —— Sort Files if Dirs First ——————————————————————————————————————————————————————————————— */

	// If we're putting the directories first, then they have to be sorted separately from the files
	if (SORT_DIRS_FIRST()) {
		sortFiles( dirs, & dir_count);
		sortFiles(files, &file_count);
	}

	/* —— Combine Dirs & Files ——————————————————————————————————————————————————————————————————— */

	const int count = dir_count + file_count;

	// Concatenate the directories & files into one list by copying the memory over
	FileInfo *all_files = emalloc(count * sizeof(FileInfo));

	memcpy(all_files,			  dirs,  dir_count  * sizeof(FileInfo));
	memcpy(all_files + dir_count, files, file_count * sizeof(FileInfo));

	free(dirs); free(files);

	/* —— Sort Files if not Dirs First ——————————————————————————————————————————————————————————— */

	// If dirs aren't sorted first, then sort everything as one
	if (!SORT_DIRS_FIRST()) sortFiles(all_files, &count);

	/* —— Find Widths of Fields —————————————————————————————————————————————————————————————————— */

	// Find the min lens of each field, and set each field's printf format string
	initFormatting();

	// Run through each of the fields and find its maximum length
	getFieldLengths(all_files, &count);

	/* —— Print Header ——————————————————————————————————————————————————————————————————————————— */

	// If we're in debug mode, the screen will have already been cleared earlier
	#ifndef DEBUG_MODE
		// Only clear the screen if this is the first directory being printed
		if (DO_CLEAR() && is_first) {
			printf("%s", CLEAR_SCREEN);
			fflush(stdout);
		}
	#endif

	// Print the fields' headers
	if (DO_HEADER()) printHeader();

	/* —— Print File Info ———————————————————————————————————————————————————————————————————————— */

	// Print the fields' actual information
	printFields(all_files, &count);

	/* ——————————————————————————————————————————————————————————————————————————————————————————— */

	// Discard the date for all the files in this directory
	free(all_files);
}

#ifdef DEBUG_MODE
#pragma clang diagnostic pop
#endif

// spell:ignoreRegexp /(?<!\w)-W(\w+)/g
