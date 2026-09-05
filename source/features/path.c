/// @file features/path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void abbrPath(path_t out_path, const path_t abs_path) {
	// by default, copy the `abs_path` over to `out_path`
	strcpy(out_path, abs_path);
	const char *HOME = getenv("HOME");

	if (HOME != NULL) {
		const size_t
			home_len = strlen(HOME),
			path_len = strlen(abs_path);

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

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int getDirPath(path_t out_path, const path_t path) {
	path_t abs_path;

	// if `path` is already an absolute path, then just copy it over
	if (path[0] == '/') {
		strcpy(abs_path, path);

	} else { // if it's not an absolute path:

		// all the ...errno variables will be unused when not in debug mode
		#ifndef DEBUG_MODE
		#	pragma clang diagnostic push
		#	pragma clang diagnostic ignored "-Wunused-variable"
		#endif

		// we're getting the env var instead of running `getcwd`,
		//  since `getcwd` will chase links when finding the absolute path of `path`
		const char *PWD = getenv("PWD"); // get PWD
		const int getenv_errno = errno;

		/* ———————————————————————————————————————————————————————————————————— */

		path_t base_path;

		// if `$PWD` can't be found, or if its empty
		if (PWD == NULL || *PWD == '\0') {
			debug(WARNING, "getenv(\"PWD\"): \n", strerror(getenv_errno));

			// if `getenv` failed, try `getcwd`. if that fails, then give up
			if (getcwd(base_path, MAX_PATH_LEN) == NULL) {
				const int getcwd_errno = errno;

				debug(ERROR, "getenv(\"PWD\"): %s\ngetcwd(): %s\n", strerror(getenv_errno), strerror(getcwd_errno));
				return EXIT_FAILURE;
			}

		} else {
			// if `$PWD` was found, copy it into the base path var
			strncpy(base_path, PWD, MAX_PATH_LEN - 1);
			base_path[MAX_PATH_LEN - 1] = '\0';
		}

		/* ———————————————————————————————————————————————————————————————————— */

		// if path == `.`, copy the base path we just got to `abs_path`
		if (strcmp(path, DOTDIR) == 0) {
			strncpy(abs_path, base_path, MAX_PATH_LEN);

		} else {
			// if path != `.` , concatenate abs_path and base_path together,
			//	while making sure the buffer doesn't overflow
			if (sprintf(abs_path, "%s/%s", base_path, path) >= MAX_PATH_LEN) {
				const int sprintf_errno = errno;

				debug(ERROR, "sprintf: %s\n", strerror(sprintf_errno));
				return EXIT_FAILURE;
			}
		}

		#ifndef DEBUG_MODE
		#	pragma clang diagnostic pop
		#endif
	}

	/* ———————————————————————————————————————————————————————————————————— */

	// once we've got the absolute path, try and abbreviate it by replacing $HOME with `~`.
	abbrPath(out_path, abs_path);

	// abbrPath will always succeed, so return with success
	return EXIT_SUCCESS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)/g
