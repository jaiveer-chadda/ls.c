/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_SUFFIX()	(do_suffix() && (suffix != '\0' && is_valid_path))

#define PRINT_SUFFIX() if (DO_SUFFIX()) { putchar(suffix); }
#define GET_TARGET_COLOUR()	(link_col != FC_REGULAR ? file_colour_esc[link_col] : "")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printSymlink(link_t p_target_path, const suff_t suffix, const FileColour link_col) {
	const bool is_valid_path = (suffix != INVALID_LINK);

	/* ————————————————————————————————————————————————————— */

	// /*DEBUG*/ printf("<0>"); fflush(stdout);

	if (!DO_COLOUR()) {
		path_t escd_path;
		escapeName(escd_path, p_target_path, "");
		free(p_target_path);

		printf("%s%s", SYMLINK_ARROW, escd_path);

		PRINT_SUFFIX();
		return;
	}

	// /*DEBUG*/ printf("<1>"); fflush(stdout);

	if (!is_valid_path) {
		path_t escd_path;
		escapeName(escd_path, p_target_path, INVALID_LINK_COLOUR);
		free(p_target_path);

		printf("%s%s" "%s%s" "%s",
			ANSI(INVALID_ARROW_COLOUR), SYMLINK_ARROW,
			ANSI(INVALID_LINK_COLOUR ), escd_path,
			RESET
		);

		PRINT_SUFFIX();
		return;
	}

	// /*DEBUG*/ printf("<2>"); fflush(stdout);

	/* ————————————————————————————————————————————————————— */

	// printf("%p", p_target_path);
	// return;

	const char *p_last_slash  = strrchr(p_target_path, '/'); // `strchr()` is the function that causes the segfault
	const bool contains_slash = (p_last_slash != NULL);
	const char *p_filename	  = contains_slash ? p_last_slash + 1 : p_target_path;

	path_t escd_filename, escd_dirname = "";


	// /*DEBUG*/ printf("<3>"); fflush(stdout);

	if (contains_slash) {
		path_t orig_dirname;
		const size_t dirname_len = p_filename - p_target_path;

		strncpy(orig_dirname, p_target_path, dirname_len);
		orig_dirname[dirname_len] = '\0';

		escapeName(escd_dirname, orig_dirname, LINK_PATH_COLOUR);
	}

	// /*DEBUG*/ printf("<4>"); fflush(stdout);

	escapeName(escd_filename, p_filename, GET_TARGET_COLOUR());

	printf("%s%s%s" "%s%s" "%s%s%s%s" "%s",
		ANSI(VALID_ARROW_COLOUR), SYMLINK_ARROW, RESET,

		// print the dirname (path to the file's parent dir)
		contains_slash ? ANSI(LINK_PATH_COLOUR) : "", escd_dirname,
		// print the actual filename (basename)
		CSI, GET_TARGET_COLOUR(), END, escd_filename,

		RESET
	);

	free(p_target_path); // this memory is allocated in `getLink()` (symlink.c)

	/* ————————————————————————————————————————————————————— */

	PRINT_SUFFIX();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore escd
