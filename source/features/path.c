/// @file features/path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "output/output.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const char *getDisplayPath(FileStat *const pFS) {
	// if the path has a parent, then we don't want to analyse it.
	//	we only want the most root-level files
	if (pFS->parent != NULL) return NULL;

	path_t path_buffer = {0};
	char *PWD = path_buffer;
	PWD = getcwd(PWD, sizeof(path_buffer));

	if (PWD == NULL) return NULL;
	char *adj_path = PWD;

	const char *const HOME = getenv("HOME");
	const size_t home_len = strlen(HOME), path_len = strlen(adj_path);

	if (HOME == NULL		// make sure we actually
		|| home_len == 0	//	got the $HOME var
		|| path_len <= home_len		// check that `$PWD != $HOME`
		|| strncmp(HOME, adj_path, home_len) != 0	// and make sure that we're actually in a subdir of $HOME
	) return strdup(adj_path);

	// replace `$HOME` with `~`
	adj_path[home_len - 1] = '~';
	adj_path += home_len - 1;

	return strdup(adj_path);
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
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)|escd/g
