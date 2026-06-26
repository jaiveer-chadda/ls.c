/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../options/options.h"

#define IF_COLOUR(str) (DO_COLOUR() ? (str) : "")
#define GET_COLOUR(var) IF_COLOUR(is_valid_path ? VALID_##var##_COLOUR : INVALID_##var##_COLOUR)

#define GET_TARGET_COLOUR()				\
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

	const char *last_slash	= strrchr(target_path, '/');
	const int	name_begins	= (last_slash - target_path) + 1;
	const char *base_name	= target_path + name_begins;

	const bool is_valid_path = (suffix != INVALID_LINK);

	printf(
		"%s%s%s"
		"%s%.*s"
		"%s%s"
		"%s",

		GET_COLOUR(ARROW), SYMLINK_ARROW, IF_COLOUR(RESET),
		is_valid_path ? LINK_PATH_COLOUR : INVALID_LINK_COLOUR, name_begins, target_path,
		GET_TARGET_COLOUR(), strlen(target_path) == 0 ? "" : base_name,
		IF_COLOUR(RESET)
	);

	if (DO_PRINT_SUFFIX()) printf("%c", suffix);
}
