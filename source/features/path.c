/// @file features/path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "malloc.h"
#include "output/output.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const char *getDisplayPath(const char *const path, const namlen_t path_len) {
	path_t path_buffer = {0};
	ssize_t pwd_len = -1;
	char *adj_path, *PWD = path_buffer;
	const bool is_link_tg = path_len == -1;

	if (!is_link_tg) {
		if ((path[0] == '.' && path[1] == '\0')) {
			// just a pointer to a string
			PWD = getenv("PWD");

			if (PWD != NULL) {
				// fill the path buffer with the result of PWD
				pwd_len = strlen(PWD);
				memcpy(path_buffer, PWD, pwd_len);

			} else {
				// `getcwd` fills the path buffer
				PWD = getcwd(PWD, sizeof(path_buffer));
				if (PWD == NULL) return NULL;
			}
		} else {
			// fill the path buffer with the inputted string
			memcpy(path_buffer, path, path_len);
		}
	}

	adj_path = is_link_tg ? (char*)path : path_buffer;

	const char *const HOME = getenv("HOME");
	const size_t home_len = strlen(HOME), adj_len = strlen(adj_path);

	if (HOME == NULL		// make sure we actually
		|| home_len == 0	//	got the $HOME var
		|| adj_len <= home_len		// check that `$PWD != $HOME`
		|| strncmp(HOME, adj_path, home_len) != 0	// and make sure that we're actually in a subdir of $HOME
	) return is_link_tg ? adj_path : strdup(adj_path);

	// replace `$HOME` with `~`
	adj_path[home_len - 1] = '~';
	adj_path += home_len - 1;

	return is_link_tg ? adj_path : strdup(adj_path);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char* choosePath(const FileStat *const pFS) {
	if (pFS->display != NULL			 ) return pFS->display;
	if (pFS->path	 != NULL && DO_PATH()) return pFS->path;

	return pFS->name;
}

void print_name(const FileStat *const pFS) {
	const char *const name_or_path = choosePath(pFS);
	printEscdName(name_or_path, file_colour_esc[pFS->file_col]);

	if (pFS->display != NULL) efree((void*)pFS->display);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)|escd/g
