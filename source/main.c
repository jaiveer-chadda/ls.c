/**
 * @mainpage
 * @file main.c
 */

#include <errno.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "model/global.h"
#include "model/new-stat-model.h"
#include "main/process-dir.h"

#include "utils/malloc.h"
#include "utils/string.h"
#include "options/options.h"
#include "features/time/time.h"

#include "debugging/debugging.h"

static inline const char *getArgv0(const int argc, char *restrict argv[]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

path_t G_DOTDIR_PATH;
const char *argv0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, char *argv[]) {
	initDebugging(argv);

	// Set the locale to the system default (it'll check the env vars)
	//	(this is to ensure that multibyte characters can be printed as file icons)
	const char *locale = setlocale(LC_ALL, "");
	if(!strends(locale, "UTF-8")) debug(WARNING, "Non-UTF-8 locale - locale is '%s'", locale);

	argv0 = getArgv0(argc, argv);
		
	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	// Parse the user's inputted options, and find where the options end (& where the files start)
	//	e.g. if the program is run as `lk --clear --sort name ~/.config/options`, then `files_start` will be 4
	const int opt_count = setOptions(argc, (const char**)argv);

	/* —— Determine Input Paths —————————————————————————————————————————————————————————————————— */

	/// How many filepaths were entered after the options ended.
	/// If there were no path entered, then assume there was just one path (`.`).
	const int file_count = opt_count < argc ? argc - opt_count : 1;

	/// The raw string paths inputted by the user.
	char **file_paths = argv + opt_count;
	// If there were no paths entered, then assume the user inputted the path `.`
	if (opt_count >= argc) file_paths[0] = DOTDIR;

	/* —— Find Target Files/Dirs ————————————————————————————————————————————————————————————————— */

	for (int i = 0; i < file_count; i++) {
		const char *path = file_paths[i];
		printf("%d: %s\n", i, path);

		struct stat file_stat;
		stat(path, &file_stat);

		if (stat(path, &file_stat) == -1) {
			const int stat_errno = errno;
			if (stat_errno == ENOENT) { /* handle */ };

			fprintf(stderr, "%s: %s: %s\n", argv0, path, strerror(stat_errno));
			continue;
		}

		if (S_ISDIR(file_stat.st_mode)) {}
	}

	// /* ————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
	// /* ————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
	// /* ————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
	//
	// /// Whether the user inputted at least one valid input into the function.
	// bool has_any_valid_input = false;
	//
	// // Get a `DIR` pointer for each path passed in to the function
	// // (`DIR` being a "structure describing an open directory")
	// DIR *input_dirs[input_count];
	//
	// for (int i = 0; i < input_count; i++) {
	// 	input_dirs[i] = opendir(input_paths[i]);
	// 	const int opendir_errno = errno;
	//
	// 	// If we couldn't open the directory (usually cos it doesn't exist or
	// 	//	we don't have permissions for it), print an error
	// 	if (input_dirs[i] == NULL) {
	// 		fprintf(stderr, "%s: %s: %s\n", argv0, input_paths[i], strerror(opendir_errno));
	// 	} else {
	// 		// If at least one inputted directory is valid, then make sure we continue
	// 		has_any_valid_input = true;
	// 	}
	// }
	//
	// // If none the inputted directories are valid, exit with failure
	// if (!has_any_valid_input) return EXIT_FAILURE;
	//
	// /* —— Get Current Time ——————————————————————————————————————————————————————————————————————— */
	//
	// // Find the current time and make it available globally
	// initTime();
	//
	// /* —— Process All Directories ———————————————————————————————————————————————————————————————— */
	//
	// for (int i = 0; i < input_count; i++) {
	// 	// Don't process invalid directories
	// 	if (input_dirs[i] == NULL) continue;
	//
	// 	// Do the processing & print the details for each directory inputted
	// 	processDirectory(input_paths[i], input_dirs[i], do_free_path_0, i == 0);
	//
	// 	// Print a newline between each directory listing (after each dir except the last)
	// 	if (i != input_count - 1) putchar('\n');
	// }

	return EXIT_SUCCESS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char *getArgv0(const int argc, char *restrict argv[]) {
	if ((argc < 1) || (argv[0] == NULL) || (argv[0][0] == '\0')) {
		return PROGRAM_NAME;
	}

	const char *basename = strrchr(argv[0], '/');
	if (basename != NULL) {
		return basename + 1;
	}

	return argv[0];
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
