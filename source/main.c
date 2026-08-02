/**
 * @mainpage
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info/info.h"
#include "utils/malloc.h"
#include "output/output.h"
#include "form/formatting.h"
#include "options/options.h"
#include "info/sorting/sort.h"

#include "features/path/path.h"
#include "features/time/time.h"
#include "debugging/debugging.h"

path_t G_DOTDIR_PATH = DOTDIR;

int main(const int argc, const char *argv[]) {

	#ifdef DEBUG_MODE
	printf("%s", CLEAR_SCREEN);
	fflush(stdout);
	#endif

	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	const int files_start = setOptions(argc, argv);

	debug(DEBUG, "some debugging message");

	/* —— Find Target Directory —————————————————————————————————————————————————————————————————— */

	path_t input_dir_path;

	// Get the target directory from the user's input
	DIR *input_dir = getDirectory(input_dir_path, files_start, argc, argv);
	if (input_dir == NULL) return EXIT_FAILURE;

	// Resolve the path to the target directory, which'll be used to replace the `.` directory's name
	//  (casting to void, since there's nth we can rly do if we don't manage to get it)
	(void)getDirPath(G_DOTDIR_PATH, input_dir_path);

	/* —— Get Current Time ——————————————————————————————————————————————————————————————————————— */

	// Find the current time and make it available globally
	initTime();

	/* —— Get File Info from `stat` —————————————————————————————————————————————————————————————— */

	FileInfo
		*dirs  = emalloc(MAX_FILES_IN_DIR * sizeof(FileInfo)),
		*files = emalloc(MAX_FILES_IN_DIR * sizeof(FileInfo));

	int dir_count, file_count;

	// Run the `stat` and `lstat` syscalls, and start parsing the files' information
	getAllFileInfo(
		dirs, files,
		&dir_count, &file_count,
		input_dir, input_dir_path
	);

	/* —— Sort Files if Dirs First ——————————————————————————————————————————————————————————————— */

	if (SORT_DIRS_FIRST()) {
		sortFiles( dirs,  &dir_count);
		sortFiles(files, &file_count);
	}

	/* —— Combine Dirs & Files ——————————————————————————————————————————————————————————————————— */

	const int count = dir_count + file_count;

	FileInfo *all_files = emalloc(count * sizeof(FileInfo));

	memcpy(all_files,			  dirs,  dir_count  * sizeof(FileInfo));
	memcpy(all_files + dir_count, files, file_count * sizeof(FileInfo));

	free(dirs); free(files);

	/* —— Sort Files if not Dirs First ——————————————————————————————————————————————————————————— */

	if (!SORT_DIRS_FIRST()) sortFiles(all_files, &count);

	/* —— Find Widths of Fields —————————————————————————————————————————————————————————————————— */

	// Find the min lens of each field, and set each field's printf format string
	initFormatting();

	// Run through each of the fields and find its maximum length
	getFieldLengths(all_files, &count);

	/* —— Print Header ——————————————————————————————————————————————————————————————————————————— */

	#ifndef DEBUG_MODE
	if (DO_CLEAR()) printf("%s", CLEAR_SCREEN);
	#endif

	// Print the fields' headers
	if (DO_HEADER()) printHeader();

	/* —— Print File Info ———————————————————————————————————————————————————————————————————————— */

	// Print the fields' actual information
	printFields(all_files, &count);

	/* ——————————————————————————————————————————————————————————————————————————————————————————— */

	free(all_files);

	return EXIT_SUCCESS;
}
