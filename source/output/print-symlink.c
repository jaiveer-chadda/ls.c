/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../options/options.h"

#define IF_COLOUR(str) (DO_COLOUR() ? (str) : "")
#define GET_COLOUR(var) IF_COLOUR(is_valid_path ? VALID_##var##_COLOUR : INVALID_##var##_COLOUR)

#define GET_PATH_COLOUR()				\
	IF_COLOUR(is_valid_path				\
		? (link_col != FC_REGULAR		\
			? file_colour_esc[link_col]	\
			: RESET						\
		) : INVALID_LINK_COLOUR			\
	)

#define DO_PRINT_SYMLINK()	(do_link_to() && suffix != NOT_LINK)
#define DO_PRINT_SUFFIX()	(do_suffix () && suffix != '\0' && is_valid_path)

void printSymlink(const path_t target_path, const type_t suffix, const FileColour link_col) {
	if (!DO_PRINT_SYMLINK()) return;

	const bool is_valid_path = (suffix != INVALID_LINK);
	printf("%s%s" "%s%s" "%s",
		GET_COLOUR(ARROW), SYMLINK_ARROW,
		GET_PATH_COLOUR(), target_path,
		IF_COLOUR(RESET)
	);

	if (DO_PRINT_SUFFIX()) printf("%c", suffix);
}
