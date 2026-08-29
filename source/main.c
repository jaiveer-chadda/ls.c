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

	// set the locale to the system default (it'll check the env vars)
	//	(this is to ensure that multibyte characters can be printed as file icons)
	const char *locale = setlocale(LC_ALL, "");
	if(!strends(locale, "UTF-8")) debug(WARNING, "Non-UTF-8 locale - locale is '%s'", locale);

	argv0 = getArgv0(argc, argv);
		
	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	// parse the user's inputted options, and find where the options end (& where the files start)
	//	e.g. if the program is run as `lk --clear --sort name ~/.config/options`, then `files_start` will be 4
	const int opt_count = setOptions(argc, (const char**)argv);

	/* —— Determine Input Paths —————————————————————————————————————————————————————————————————— */

	/// How many filepaths were entered after the options ended.
	/// If there were no path entered, then assume there was just one path (`.`).
	const int file_count = opt_count < argc ? argc - opt_count : 1;

	/// The raw string paths inputted by the user.
	char **file_paths = argv + opt_count;
	// if there were no paths entered, then assume the user inputted the path `.`
	if (opt_count >= argc) file_paths[0] = DOTDIR;

	/* —— Find Target Files/Dirs ————————————————————————————————————————————————————————————————— */

	/// Whether the user inputted at least one valid input into the function.
	bool any_valid_input = false;

	/// An array of pointers to FileStat objects, each representing the inputted files/dirs.
	FileStat *fs_input_arr[file_count];

	for (int i = 0; i < file_count; i++) {
		const char *path = file_paths[i];
		struct stat file_stat;

		printf("%d: %s\n", i, path);

		/* ———————————————————————————————————————————————————————————— */

		// firstly, try to `stat` the input path
		if (stat(path, &file_stat) == -1) {
			// if it fails, print an error and move onto the next file
			const int stat_errno = errno;
			if (stat_errno == ENOENT) { /* handle */ }

			fprintf(stderr, "%s: %s: %s\n", argv0, path, strerror(stat_errno));

			// set the pointer to this input to NULL, so we know not to process it later
			fs_input_arr[i] = NULL;
			continue;
		}

		// file was `stat`ted successfully - note down that we've had at least 1 valid input
		any_valid_input = true;

		/* ———————————————————————————————————————————————————————————— */

		// since we successfully got the `stat` information, we can start building the `FileStat` object

		// allocate memory for this file's `FileStat` object
		FileStat *p_fsobj = emalloc(sizeof(FileStat));

		// then zero the memory
		*p_fsobj = (FileStat){0};
		// and add its pointer to the input array
		fs_input_arr[i] = p_fsobj;

		/* ———————————————————————————————————————————————————————————— */

		// allocate memory for the `stat` object that will be pointed to by `FileStat::s`
		struct stat *p_stat = emalloc(sizeof(struct stat));

		// copy `file_stat` from the stack into the newly-allocated heap memory,
		//	and then assign the pointer to that heap memory to `FileStat::s`
		p_fsobj->s = memcpy(p_stat, &file_stat, sizeof(struct stat));

		/* ———————————————————————————————————————————————————————————— */

		if (S_ISDIR(file_stat.st_mode)) {}
	}

	// if none of the inputted directories were valid, exit with failure
	if (!any_valid_input) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char *getArgv0(const int argc, char *restrict argv[]) {
	if ((argc < 1) || (argv[0] == NULL) || (argv[0][0] == '\0')) return PROGRAM_NAME;

	const char *basename = strrchr(argv[0], '/');
	if (basename != NULL) return basename + 1;

	return argv[0];
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
