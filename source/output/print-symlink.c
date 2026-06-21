/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../options/options.h"

#define IF_COLOUR(str) (DO_COLOUR ? (str) : "")
#define GET_COLOUR(var) IF_COLOUR(is_valid_path ? VALID_##var##_COLOUR : INVALID_##var##_COLOUR)

void printSymlink(const path_t target_path, const type_t suffix) {
	if (!do_link_to || suffix == NOT_LINK) return;

	const bool is_valid_path = (suffix != INVALID_LINK);
	printf("%s%s" "%s%s" "%s",
		GET_COLOUR(ARROW), SYMLINK_ARROW,
		GET_COLOUR(LINK),  target_path,
		IF_COLOUR(RESET)
	);

	if (do_suffix && is_valid_path && suffix != '\0') printf("%c", suffix);
}
