/// @file info/get-directory.c

#include <stdio.h>
#include <string.h>

#include "info.h"

DIR* getDirectory(char *target_dir, const int argc, const char *argv[]) {
	// if there's no input, or the input is empty, then the target directory is `.`
	if (true || argc <= 1 || strlen(argv[1]) == 0) {
		strcpy(target_dir, CURRENT_DIR);

	} else { // otherwise, copy the user's input verbatim into `target_dir`
		strncpy(target_dir, argv[1], MAX_NAME_LEN - 1);
		target_dir[MAX_NAME_LEN - 1] = '\0';
	}

	DIR *directory = opendir(target_dir);
	// if we couldn't open the directory (usually cos it doesn't exist), then exit with an error
	if (directory == NULL) perror("opendir");

	return directory;
}
