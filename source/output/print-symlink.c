/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_TARGET_COLOUR()	(link_col != FC_REGULAR ? file_colour_esc[link_col] : RESET)

#define DO_PRINT_SYMLINK()	(do_link_to() && suffix != NOT_LINK)
#define DO_SUFFIX()			(do_suffix () && suffix != '\0' && is_valid_path)

#define PRINT_SUFFIX() if (DO_SUFFIX()) { putchar(suffix); }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printSymlink(const path_t target_path, const type_t suffix, const FileColour link_col) {
	if (!DO_PRINT_SYMLINK()) return;

	const bool is_valid_path = (suffix != INVALID_LINK);

	/* ————————————————————————————————————————————————————— */

	if (!DO_COLOUR()) {
		printf("%s%s", SYMLINK_ARROW, target_path);

		PRINT_SUFFIX();
		return;
	}

	if (!is_valid_path) {
		printf("%s%s" "%s%s" "%s",
			INVALID_ARROW_COLOUR, SYMLINK_ARROW	,
			INVALID_LINK_COLOUR	, target_path	,
			RESET
		);

		PRINT_SUFFIX();
		return;
	}

	/* ————————————————————————————————————————————————————— */

	const char *last_slash	 = strrchr(target_path, '/');
	const int	basename_idx = (last_slash - target_path) + 1;
	const char *basename	 = target_path + basename_idx;

	printf("%s%s" "%s%.*s" "%s%s" "%s",
		VALID_ARROW_COLOUR	, SYMLINK_ARROW	,
		LINK_PATH_COLOUR	, basename_idx	, target_path,
		GET_TARGET_COLOUR()	, basename		,
		RESET
	);

	/* ————————————————————————————————————————————————————— */

	PRINT_SUFFIX();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
