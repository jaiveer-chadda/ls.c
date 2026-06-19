/// @file output/print-symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../options/options.h"

bool isValidPath(const path_t target_path) {
	if (strlen(target_path) == 0) return false;

	const char *HOME = getenv("HOME");
	path_t target;

	if (HOME == NULL || strlen(HOME) == 0)	strcpy(target, target_path);
	else if (target_path[0] == '~')			sprintf(target, "%s%s", HOME, target_path + 1);
	else									strcpy(target, target_path);

	return (access(target, F_OK) == 0);
}

#define IF_COLOUR(print) (DO_COLOUR ? print : "")
#define GET_COLOUR(var) IF_COLOUR(is_valid_path ? VALID_##var##_COLOUR : INVALID_##var##_COLOUR)

void printSymlink(const path_t target_path, const type_t suffix) {
	if (!do_link_to || strlen(target_path) == 0) return;

	const bool is_valid_path = isValidPath(target_path);
	printf("%s%s%s%s%s", GET_COLOUR(ARROW), SYMLINK_ARROW, GET_COLOUR(LINK), target_path, IF_COLOUR(RESET));

	if (do_suffix && suffix != '\0') printf("%c", suffix);
}
