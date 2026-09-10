/// @file features/path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "output/output.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// this is defined here so that it can safely be passed to `print_name`, and then on to `printEscdName`.
static path_t path_buffer = {0};

static inline const char *formatPath(const char *path) {
	// if (path != ".")
	if (path[0] != '.' || path[1] != '\0') return path;

	char *PWD = path_buffer;
	PWD = getcwd(PWD, sizeof(path_buffer));

	if (PWD == NULL) return path;
	char *adj_path = PWD;

	const char *const HOME = getenv("HOME");
	const size_t home_len = strlen(HOME);

	if (HOME == NULL
		|| home_len == 0
		|| strncmp(HOME, adj_path, home_len) != 0
	) return adj_path;

	// replace `$HOME` with `~`
	adj_path[home_len - 1] = '~';
	adj_path += home_len - 1;

	return adj_path;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_name(const FileStat *const pFS) {
	const bool do_path = DO_PATH() && pFS->path != NULL;
	const char *name_or_path = do_path ? pFS->path : pFS->name;

	/// @todo implement the `--pwd-as-path` option
	name_or_path = formatPath(name_or_path);

	printEscdName(name_or_path, file_colour_esc[pFS->file_col]);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)|escd/g
