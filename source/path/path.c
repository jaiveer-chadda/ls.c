/// @file path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../model/stat-model.h"

#define FAILURE(err) do { \
		perror(err);	   \
		free(abs_path);		\
		return EXIT_FAILURE; \
	} while (0)

int printAbsolutePath(const char path[MAX_PATH_LEN]) {
	char *abs_path = malloc(MAX_PATH_LEN);
	if (abs_path == NULL) FAILURE("malloc");	// check if malloc failed

	if (path[0] != '/') {
        if (getcwd(abs_path, MAX_PATH_LEN) == NULL)				FAILURE("getcwd");	// get PWD
        if (strlen(abs_path) + strlen(path) + 2 > MAX_PATH_LEN) FAILURE("getcwd");	// make sure we don't overflow

		if (strcmp(path, ".") != 0) {
			strcat(abs_path, path);
			strcat(abs_path, "/" );
		}

	} else strcpy(abs_path, path);

	const char *HOME = getenv("HOME");

	const int home_len = strlen(HOME);
	const int path_len = strlen(abs_path);

	if ( HOME != NULL
		&& home_len > 0
		&& home_len < path_len
		&& strncmp(HOME, abs_path, home_len) == 0
	) {
		putchar('~');
		puts(abs_path + home_len);

	} else puts(abs_path);

	free(abs_path);
	return EXIT_SUCCESS;
}
