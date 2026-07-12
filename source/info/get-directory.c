/// @file info/get-directory.c

#include <stdio.h>
#include <string.h>

#include "info.h"

DIR* getDirectory(path_t dotdir_path, const int files_start, const int argc, const char *argv[]) {
	// if there's no input or the input is empty, then the target directory is `.`
	if (argc == files_start || strlen(argv[files_start]) == 0) {
		strcpy(dotdir_path, DOTDIR);

	} else { // otherwise, copy the user's input verbatim into `dotdir_path`
		strncpy(dotdir_path, argv[files_start], MAX_NAME_LEN - 1);
		dotdir_path[MAX_NAME_LEN - 1] = '\0';
	}

	DIR *directory = opendir(dotdir_path);
	// if we couldn't open the directory (usually cos it doesn't exist), then exit with an error
	if (directory == NULL) perror("opendir");

	return directory;
}
