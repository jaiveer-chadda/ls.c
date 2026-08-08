/**
 * @mainpage
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main/process-dir.h"

#include "utils/malloc.h"
#include "options/options.h"
#include "features/time/time.h"

#include "debugging/debugging.h"

path_t G_DOTDIR_PATH;

int main(const int argc, const char *argv[]) {

	#ifdef DEBUG_MODE
	printf("%s", CLEAR_SCREEN);
	fflush(stdout);
	Dline();
	#endif

	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	const int files_start = setOptions(argc, argv);

	/* —— Find Target Directories ———————————————————————————————————————————————————————————————— */

	char *input_paths[MAX_FILES_IN_DIR] = {0};
	bool do_free_path_0 = false;
	int input_count = 0;

	// If there weren't any directory names passed, then default to as if the user had passed `.` or `$PWD`
	if (argc == files_start || argv[files_start] == NULL) {
		// Since "." isn't stored anywhere, we have to alloc some memory for it
		input_paths[0] = emalloc(sizeof(char *));
		do_free_path_0 = true; // & then remember to free it

		// Copy the string "." into input_paths[0]
		strcpy(input_paths[0], DOTDIR);
		input_count = 1;

	} else {
		// Copy each of the arguments' addresses into `input_paths`
		for (int i = files_start; i < argc; i++) {
			input_paths[input_count++] = (char *)argv[i];
		}
	}

	#define MAX_INPUTS 128

	/// Whether the user inputted at least one valid directory into the function.
	bool has_any_valid_input = false;

	// Get a `DIR` pointer for each path passed in to the function
	// (`DIR` being a "structure describing an open directory")
	DIR *input_dirs[MAX_INPUTS];
	for (int path_idx = 0; path_idx < input_count; path_idx++) {
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

	/* —— Get Current Time ——————————————————————————————————————————————————————————————————————— */

	// Find the current time and make it available globally
	initTime();

	/* —— Process All Directories ———————————————————————————————————————————————————————————————— */

	for (int i = 0; i < input_count; i++) {
		processDirectory(input_paths[i], input_dirs[i], (i == 0 && do_free_path_0), i == 0);
		if (input_count > 1 && i != input_count - 1) puts("");
	}

	return EXIT_SUCCESS;
}
