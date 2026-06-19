/// @file features/path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "path.h"
#include "../../info/info.h"

#define FAILURE(err) do {	\
		perror(err);		\
		return EXIT_FAILURE;\
	} while (0)

int getDirPath(path_t out_path, const path_t path) {
	path_t abs_path;

	// if it isn't already an absolute path
	if (path[0] != '/') {
		if (getcwd(abs_path, MAX_PATH_LEN) == NULL)				FAILURE("getcwd");	// get PWD
		if (strlen(abs_path) + strlen(path) + 2 > MAX_PATH_LEN) FAILURE("strlen");	// make sure we don't overflow

		if (strcmp(path, CURRENT_DIR) != 0) {
			strcat(abs_path, path);

			abs_path[strlen(abs_path)	 ] = '/';
			abs_path[strlen(abs_path) + 1] = '\0';
		}

	} else strcpy(abs_path, path);

	const char *HOME = getenv("HOME");

	const int home_len = strlen(HOME);
	const int path_len = strlen(abs_path);

	if (HOME != NULL
		&& home_len > 0
		&& home_len < path_len
		&& strncmp(HOME, abs_path, home_len) == 0
	) {
		sprintf(out_path, "~%s", abs_path + home_len);
	} else strcpy(out_path, abs_path);

	return EXIT_SUCCESS;
}
