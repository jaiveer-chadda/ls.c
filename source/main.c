/**
 * @mainpage
 * @file main.c
 */

#include <stdio.h> // printf()
#include <string.h> // strrchr()
#include <locale.h> // setlocale()

#include "malloc.h" // efree()
#include "strings.h" // strends()
#include "debugging.h" // initDebugging(), debug()

#include "model/global.h" // argv0
#include "sorting/sort.h" // sortFiles()
#include "output/output.h" // printFile()
#include "form/formatting.h" // initFormatting()
#include "options/options.h" // setOptions(), DO_CLEAR()
#include "parsing/parse-file.h" // parseFile()
#include "processing/process-input.h" // processInput()

/* ── ── Declarations ── ─────────────────────────────────────────────────────────────────────────────────────────── */

static inline const char *getArgv0(const int argc, char *restrict argv[]);
const char *argv0;

/* ── ── main() ── ───────────────────────────────────────────────────────────────────────────────────────────────── */

int main(const int argc, char *argv[]) {
	// set the locale to the system default (it'll check the env vars)
	//	(this is to ensure that multibyte characters can be printed as file icons)
	const char *const locale = setlocale(LC_ALL, "");
	if(!strends(locale, "UTF-8")) debug(WARNING, "Non-UTF-8 locale - locale is '%s'", locale);

	argv0 = getArgv0(argc, argv);
	initDebugging(argv);

	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	// parse the user's inputted options, and find where the options end (& where the files start)
	//	e.g. if the program is run as `lk --clear --sort name ~/.config/options`, then `files_start` will be 4
	const int opt_count = setOptions(argc, argv);
	initFormatting();

	/* —— Determine Input Paths —————————————————————————————————————————————————————————————————— */

	/// How many filepaths were entered after the options ended.
	/// If there were no path entered, then assume there was just one path (`.`).
	const int file_count = opt_count < argc ? argc - opt_count : 1;

	/// The raw string paths inputted by the user.
	char **file_paths = argv + opt_count;
	// if there were no paths entered, then assume the user inputted the path `.`
	if (opt_count >= argc) file_paths[0] = DOTDIR;

	/* —— Process & Parse Inputs ————————————————————————————————————————————————————————————————— */

	bool any_valid_input = false;

	// unfortunately, this has to be allocated on the heap, since wah wah, variable-size arrays are bad
	//	boo hoo, and I want to be a good programmer, so I don't use them. bollocks >:(
	/// An array of pointers to FileStat objects, each representing the inputted files/dirs.
	FileStat **inputs = ecalloc(file_count, sizeof(FileStat*));

	// iterate through each input, and get a pointer to the input's `FileStat` object to add to the array
	for (int i = 0; i < file_count; i++) {
		// firstly, process the input - i.e. extract the raw info that we can get from various syscalls
		inputs[i] = processInput(file_paths[i]);

		// make sure we were actually able to get anything from `processInput()`
		if (inputs[i] == NULL) continue;
		any_valid_input = true;

		// then parse the file - i.e. go through and convert things from raw data into displayable output
		parseFile(inputs[i]);
	}

	// if none of the inputs were valid, don't bother with even trying to print them - just return failure
	if (!any_valid_input) return EXIT_FAILURE;

	/* —— Sort Files ————————————————————————————————————————————————————————————————————————————— */

	for (int i = 0; i < file_count; i++) {
		if (inputs[i]->f->child_count <= 1) continue;

		sortFiles(
			(inputs[i]->f->children),
			&inputs[i]->f->child_count
		);
	}

	/// @todo implement `--sort-input`/`DO_SORT_INPUT`
	/* if (DO_SORT_INPUTS()) */ sortFiles(*inputs, &file_count);

	/* —— Print —————————————————————————————————————————————————————————————————————————————————— */

	// clear the screen after all the processing is done, but before we start printing
	//	this should hopefully lead to the smoothest output
	clearScreen();

	#if defined(DEBUG_MODE) && defined(DUMP)
		dump(inputs[0]);
	#endif

	if (DO_HEADER()) printHeaders();

	// print each of the inputs in the order they were given
	// `printFile` will recurse into the file and print as many levels as was specified
	for (int i = 0; i < file_count; i++) {
		printFile(inputs[i], /*level*/0, /*is_last*/i == file_count - 1, NO_LINES);
	}

	/* —— Cleanup ———————————————————————————————————————————————————————————————————————————————— */

	/// @todo move most of this into the printing section
	for (int i = 0; i < file_count; i++) {
		/* Memory Allocated
		 * ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
		 *	- `FileStat *inputs[]` - one for each input that was successfully statted (set to NULL on failure)
		 *		- `struct stat    *FileStat::s` - same conditions as above
		 *		- `FileStatFields *FileStat::f` - same conditions as above
		 *			- `FileStat (*FileStatFields::children)[]` - allocated if input is a directory
		 *				- `char        *FileStat::name` - allocated unconditionally for every child created
		 *				- `struct stat *FileStat::s` - allocated if child was statted successfully (NULL otherwise)
		 */
		FileStat *fsobj = inputs[i];
		if (fsobj != NULL) efree(fsobj);
	}

	efree(inputs);

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
