/// @file features/path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "path.h"
#include "../../info/info.h"

void abbrPath(path_t out_path, const path_t abs_path) {
	// by default, copy the abs_path
	strcpy(out_path, abs_path);

	const char *HOME = getenv("HOME");

	if (HOME != NULL) {
		const size_t home_len = strlen(HOME);
		const size_t path_len = strlen(abs_path);

		if (home_len > 0								// if `$HOME` has some value,
			&& home_len < path_len						// and the full path isn't `$HOME` itself
			&& strncmp(HOME, abs_path, home_len) == 0	// and if it's a prefix of `abs_path`
		) {
			// then replace `$HOME` with `~`
			sprintf(out_path, "~%s", abs_path + home_len);
		}
	}
	// if anything fails, just return the absolute path we got earlier
}

int getDirPath(path_t out_path, const path_t path) {
	path_t abs_path;

	// if path is already an absolute path, then just copy it over
	if (path[0] == '/') strcpy(abs_path, path);

	else { // if it's not an absolute path:

		// we're getting the env var instead of running `getcwd`,
		//  since `getcwd` will chase links when finding the absolute path of `path`
		const char *PWD = getenv("PWD"); // get PWD
		path_t base_path;

		if (PWD == NULL) {
			// if `getenv` failed, try `getcwd`, and if that fails, then exit
			if (getcwd(base_path, MAX_PATH_LEN) == NULL) {
				perror("getenv,getcwd");
				return EXIT_FAILURE;
			}

		} else {
			strncpy(base_path, PWD, MAX_PATH_LEN - 1);
			base_path[MAX_PATH_LEN - 1] = '\0';
		}

		// if path == `.`, copy the path we just calculated over to `abs_path`
		if (strcmp(path, DOTDIR) == 0) {
			strncpy(abs_path, base_path, MAX_PATH_LEN);

		} else {
			// if path != `.` , concatenate abs_path and base_path together
			//  and make sure the buffer doesn't overflow
			if (sprintf(abs_path, "%s/%s", base_path, path) >= MAX_PATH_LEN) {
				perror("path buffer overflow");
				return EXIT_FAILURE;
			}
		}
	}

	// once we've got the absolute path, try and abbreviate it by replacing $HOME with `~`.
	abbrPath(out_path, abs_path);

	// abbrPath will always succeed, so return with success
	return EXIT_SUCCESS;
}
