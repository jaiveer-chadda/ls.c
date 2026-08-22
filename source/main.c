/**
 * @mainpage
 * @file main.c
 */

#include <errno.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "main/process-dir.h"

#include "utils/malloc.h"
#include "utils/string.h"
#include "options/options.h"
#include "features/time/time.h"

#include "debugging/debugging.h"

/// [TEMP] The maximum number of directories that can be passed to the function.
#define MAX_INPUTS 128

path_t G_DOTDIR_PATH;
const char *argv0;

int main(const int argc, const char *argv[]) {
	initDebugging(argv);

	// Set the locale to the system default (it'll check the env vars)
	//	(this is to ensure that multibyte characters can be printed as file icons)
	const char *locale = setlocale(LC_ALL, "");
	if(!strends(locale, "UTF-8")) debug(WARNING, "Non-UTF-8 locale - locale is '%s'", locale);

	argv0 = argc >= 1 && argv[0] != NULL && strlen(argv[0]) > 0
		? argv[0]
		: PROGRAM_NAME;

	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	// Parse the user's inputted options, and find where the options end (& where the files start)
	//	e.g. if the program is run as `lk --clear --sort name ~/.config/options`, then `files_start` will be 4
	const int files_start = setOptions(argc, argv);
	const int input_count = (argc == files_start) ? 1 : (argc - files_start);

	/* —— Find Target Directories ———————————————————————————————————————————————————————————————— */

	/// The raw string paths inputted by the user.
	char *input_paths[input_count];

	bool do_free_path_0 = false;

	// If there weren't any directory names passed, then default to as if the user had passed `.`
	if (argc == files_start) {
		// Since "." isn't stored anywhere, we have to alloc some memory for it
		//	This memory is freed in `processDirectory()`
		input_paths[0] = emalloc(sizeof(char *));
		do_free_path_0 = true; // & then remember to free it

		// Copy the string "." into input_paths[0]
		strcpy(input_paths[0], DOTDIR);

	} else {
		// Copy each of the arguments' addresses into `input_paths`
		for (int i = 0; i < input_count; i++) {
			input_paths[i] = (char *)argv[files_start + i];
		}
	}

	/// Whether the user inputted at least one valid input into the function.
	bool has_any_valid_input = false;

	// Get a `DIR` pointer for each path passed in to the function
	// (`DIR` being a "structure describing an open directory")
	DIR *input_dirs[input_count];

	for (int i = 0; i < input_count; i++) {
		input_dirs[i] = opendir(input_paths[i]);
		const int opendir_errno = errno;

		// If we couldn't open the directory (usually cos it doesn't exist or
		//	we don't have permissions for it), print an error
		if (input_dirs[i] == NULL) {
			fprintf(stderr, "%s: %s: %s\n", argv0, input_paths[i], strerror(opendir_errno));
		} else {
			// If at least one inputted directory is valid, then make sure we continue
			has_any_valid_input = true;
		}
	}

	// If none the inputted directories are valid, exit with failure
	if (!has_any_valid_input) return EXIT_FAILURE;

	/* —— Get Current Time ——————————————————————————————————————————————————————————————————————— */

	// Find the current time and make it available globally
	initTime();

	/* —— Process All Directories ———————————————————————————————————————————————————————————————— */

	for (int i = 0; i < input_count; i++) {
		// Don't print invalid directories
		if (input_dirs[i] == NULL) continue;

		// Do the processing & print the details for each directory inputted
		processDirectory(input_paths[i], input_dirs[i], do_free_path_0, i == 0);

		// Print a newline between each directory listing (after each dir except the last)
		if (i != input_count - 1) putchar('\n');
	}

	return EXIT_SUCCESS;
}
