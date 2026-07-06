/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "output.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_SYMLINK() (do_link_to() && (suffix != NOT_LINK))
#define DO_SUFFIX()	 (do_suffix()  && (suffix != '\0' && is_valid_path))

#define PRINT_SUFFIX()		if (DO_SUFFIX()) { putchar(suffix); }
#define GET_TARGET_COLOUR()	(link_col != FC_REGULAR ? file_colour_esc[link_col] : RESET)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printSymlink(const path_t p_target_path, const type_t suffix, const FileColour link_col) {
	if (!DO_SYMLINK()) return;

	const bool is_valid_path = (suffix != INVALID_LINK);

	/* ————————————————————————————————————————————————————— */

	if (!DO_COLOUR()) {
		printf("%s%s", SYMLINK_ARROW, p_target_path);
		PRINT_SUFFIX();
		return;
	}

	if (!is_valid_path) {
		printf("%s%s" "%s%s" "%s",
			INVALID_ARROW_COLOUR, SYMLINK_ARROW	,
			INVALID_LINK_COLOUR	, p_target_path	,
			RESET
		);

		PRINT_SUFFIX();
		return;
	}

	/* ————————————————————————————————————————————————————— */
	// name_t escaped_name
	// escapeName(escaped_name, (name_t)p_target_path);
	// p_target_path;
	/* ————————————————————————————————————————————————————— */

	const char *p_last_slash  = strrchr(p_target_path, '/');
	const bool contains_slash = (p_last_slash != NULL);
	const char *p_filename	  = contains_slash ? p_last_slash + 1 : p_target_path;

	path_t escd_filename, escd_basename = "";

	if (contains_slash) {
		path_t orig_basename;
		const int basename_len = p_filename - p_target_path;

		sprintf(orig_basename, "%.*s", basename_len, p_target_path);
		escapeName(escd_basename, orig_basename, LINK_PATH_COLOUR);
	}

	escapeName(escd_filename, p_filename, GET_TARGET_COLOUR());

	printf("%s%s" "%s%s" "%s%s" "%s",
		VALID_ARROW_COLOUR, SYMLINK_ARROW,

		// print the basename (path to the file's parent dir)
		strlen(escd_basename) > 0 ? LINK_PATH_COLOUR : "", escd_basename,
		// print the actual filename
		GET_TARGET_COLOUR(), escd_filename,

		RESET
	);

	/* ————————————————————————————————————————————————————— */

	PRINT_SUFFIX();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore escd
