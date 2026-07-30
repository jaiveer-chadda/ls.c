/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_SUFFIX()	(do_suffix() && (suffix != '\0' && is_valid_path))
#define GET_TARGET_COLOUR()	(link_col != FC_REGULAR ? file_colour_esc[link_col] : NO_COLOUR)

#define PRINT_SUFFIX() if (DO_SUFFIX()) { putchar(suffix); }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// ReSharper disable once CppParameterMayBeConst
void printSymlink(link_t p_target_path, const suff_t suffix, const FileColour link_col) {
	const bool is_valid_path = suffix != INVALID_LINK && suffix != INV_APPLE_LINK;

	/* ————————————————————————————————————————————————————— */

	if (!DO_COLOUR()) {
		path_t escd_path;

		escapeName(escd_path, p_target_path, NO_COLOUR);
		free(p_target_path);

		printf("%s%s", SYMLINK_ARROW, escd_path);

		PRINT_SUFFIX();
		return;
	}

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

	/* ————————————————————————————————————————————————————— */

	// FIXME: this won't work if the path ends with extra slashes
	const char *p_last_slash  = strrchr(p_target_path, '/');
	const bool contains_slash = p_last_slash != NULL;
	const char *p_basename	  = contains_slash ? p_last_slash + 1 : p_target_path;

	path_t escd_basename, escd_dirname = "";

	if (contains_slash) {
		path_t orig_dirname;
		const size_t dirname_len = p_basename - p_target_path;

		strncpy(orig_dirname, p_target_path, dirname_len);
		orig_dirname[dirname_len] = '\0';

		escapeName(escd_dirname, orig_dirname, LINK_PATH_COLOUR);
	}

	escapeName(escd_basename, p_basename, GET_TARGET_COLOUR());

	printf("%s%s%s" "%s%s" "%s%s%s%s" "%s",
		ANSI(VALID_ARROW_COLOUR), SYMLINK_ARROW, RESET,

		// print the dirname (path to the file's parent dir)
		contains_slash ? ANSI(LINK_PATH_COLOUR) : NO_COLOUR, escd_dirname,
		// print the name of the file (the basename)
		CSI, GET_TARGET_COLOUR(), END, escd_basename,

		RESET
	);

	// freeing the memory that's allocated in `getLink()` (symlink.c)
	// note: needs to be freed after everything's printed, cos `escd_(file|dir)name` will still point to this memory
	free(p_target_path);

	/* ————————————————————————————————————————————————————— */

	PRINT_SUFFIX();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore escd
