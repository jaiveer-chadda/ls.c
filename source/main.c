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

	Dline();

	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	const int files_start = setOptions(argc, argv);

	/* —— Find Target Directories ———————————————————————————————————————————————————————————————— */

	char *input_paths[MAX_FILES_IN_DIR] = {0};
	bool do_free_path_0 = false;
	int path_count = 0;

	// If there weren't any directory names passed, then default to as if the user had passed `.` or `$PWD`
	if (argc == files_start || argv[files_start] == NULL) {
		// Since "." isn't stored anywhere, we have to alloc some memory for it
		input_paths[0] = emalloc(sizeof(char *));
		do_free_path_0 = true; // & then remember to free it

		// Copy the string "." into input_paths[0]
		strcpy(input_paths[0], DOTDIR);
		path_count = 1;

	} else {
		// Copy each of the arguments' addresses into `input_paths`
		for (int i = files_start; i < argc; i++) {
			input_paths[path_count++] = (char *)argv[i];
		}
	}

	#define MAX_INPUTS 128

	/// Whether the user inputted at least one valid directory into the function.
	bool has_any_valid_input = false;

	// Get a `DIR` pointer for each path passed in to the function
	// (`DIR` being a "structure describing an open directory")
	DIR *input_dirs[MAX_INPUTS];
	for (int path_idx = 0; path_idx < path_count; path_idx++) {
		input_dirs[path_idx] = opendir(input_paths[path_idx]);

		// If we couldn't open the directory (usually cos it doesn't exist), print an error
		if (input_dirs[path_idx] == NULL) {
			fprintf(stderr, ERROR "%s: No such file or directory\n", input_paths[path_idx]);
		} else {
			// If at least one inputted directory is valid, then make sure we continue
			has_any_valid_input = true;
		}
	}

	// if all the inputted directories are invalid, then exit with failure
	if (!has_any_valid_input) exit(EXIT_FAILURE);

	// Resolve the path to the target directory, which'll be used to replace the `.` directory's name
	//  (casting to void, since there's nth we can rly do if we don't manage to get it)
	(void)getDirPath(G_DOTDIR_PATH, input_paths[0]);

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
		// TEMP: both just addressing [0] temporarily, so everything works during development
		input_dirs[0], input_paths[0]
	);

	if (do_free_path_0) free(input_paths[0]);

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
