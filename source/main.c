/**
 * @mainpage
 * @file main.c
 */

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "malloc.h"
#include "strings.h"
#include "debugging.h"

#include "model/global.h"
#include "model/new-stat-model.h"

#include "options/options.h"
#include "features/time/time.h"
#include "parsing/parse-file.h"
#include "processing/process-input.h"

/* ── ── Declarations ── ─────────────────────────────────────────────────────────────────────────────────────────── */

static inline const char *getArgv0(const int argc, char *restrict argv[]);

path_t G_DOTDIR_PATH;
const char *argv0;

/* ── ── main() ── ───────────────────────────────────────────────────────────────────────────────────────────────── */

int main(const int argc, char *argv[]) {
	initDebugging(argv);

	// set the locale to the system default (it'll check the env vars)
	//	(this is to ensure that multibyte characters can be printed as file icons)
	const char *const locale = setlocale(LC_ALL, "");
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

	/* —— Process & Parse Inputs ————————————————————————————————————————————————————————————————— */

	// unfortunately, this has to be allocated on the heap, since wah wah, variable-size arrays are bad
	//	boo hoo, and I want to be a good programmer, so I don't use them. bollocks >:(
	/// An array of pointers to FileStat objects, each representing the inputted files/dirs.
	FileStat **pfs_input_arr = ecalloc(file_count, sizeof(FileStat*));
	FileStat  *pfs_input;

	// iterate through each input, and get a pointer to the input's `FileStat` object to add to the array
	for (int i = 0; i < file_count; i++) {
		printf("%s\n", file_paths[i]);
		pfs_input = pfs_input_arr[i];

		// firstly, process the input - i.e. extract the raw info that we can get from various syscalls
		pfs_input = processInput(file_paths[i]);

		// make sure we were actually able to get anything from `processInput()`
		if (pfs_input == NULL) continue;

		// then parse the file - i.e. go through and convert things from raw data into displayable output
		parseFile(pfs_input);
	}

	/* —— Cleanup ———————————————————————————————————————————————————————————————————————————————— */

	for (int i = 0; i < file_count; i++) {
		/* Memory Allocated
		 * ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
		 *	- `FileStat *pfs_input_arr[]` - one for each input that was successfully statted (set to NULL on failure)
		 *		- `struct stat    *FileStat::s` - same conditions as above
		 *		- `FileStatFields *FileStat::f` - same conditions as above
		 *			- `FileStat (*FileStatFields::children)[]` - allocated if input is a directory
		 *				- `char        *FileStat::name` - allocated unconditionally for every child created
		 *				- `struct stat *FileStat::s` - allocated if child was statted successfully (NULL otherwise)
		 */
		FileStat *fsobj = pfs_input_arr[i];
		if (fsobj != NULL) efree(fsobj);
	}

	efree(pfs_input_arr);

	/* —— Return ————————————————————————————————————————————————————————————————————————————————— */

	// checkMemLeak();
	return EXIT_SUCCESS;
}

/* ── ── Helper Functions ── ─────────────────────────────────────────────────────────────────────────────────────── */

static inline const char *getArgv0(const int argc, char *restrict argv[]) {
	if ((argc < 1) || (argv[0] == NULL) || (argv[0][0] == '\0')) return PROGRAM_NAME;

	const char *basename = strrchr(argv[0], '/');
	if (basename != NULL) return basename + 1;

	return argv[0];
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
