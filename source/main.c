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
#include "parsing/parse-file.h"
#include "processing/process-input.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define ifnonull(field) (full ? ((pFSF->field) != NULL ? (pFSF->field) : "-") : "?")
#define iffull(field) (full ? (pFSF->field) : "?")

static inline void printfields(FileStat *pFS, const uint8_t depth) {
	// if an input's FileStat pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	const FileStatFields *pFSF = pFS->f;
	const bool full = pFSF != NULL;

	FileStat *parent = pFS;

	int indent = 0;
	while ((parent = parent->parent) != NULL) indent += 4;

	printf(
		"%8x %06o "    "%6s %c "    "%-14s%-8s"    "%-12s"
		"%20s"
		"%*s" "%lc %s\33[34m%c\33[m\n",

		(unsigned)pFS->inum, pFS->mode,
		ifnonull(size_str), full ? pFSF->size_unit : ' ',

		iffull(usr_name), iffull(grp_name),
		ifnonull(flag_str),

		iffull(times[M_TIME]->str),

		indent + 2, "",
		pFS->icon,
		pFS->name,
		pFS->suffix
	);

	if (!S_ISDIR(pFS->mode) || depth + 1 > MAX_DEPTH) return;

	if (!full || pFSF->child_count == -1) { printf("\t%*s[[ error ]]\n", 81, ""); return; }
	if			(pFSF->child_count ==  0) { printf("\t%*s(  empty  )\n", 81, ""); return; }

	for (int i = 0; i < pFSF->child_count; i++) {
		printfields(pFSF->children + i, depth + 1);
	}
}

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

	/// @todo figure out a way to sort the inputs before they're printed

	/* —— Print —————————————————————————————————————————————————————————————————————————————————— */

	// print each of the inputs in the order they were given
	// `printfields` will recurse into the file and print as many levels as was specified
	for (int i = 0; i < file_count; i++) printfields(inputs[i], 0);

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
