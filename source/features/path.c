/// @file features/path/path.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "malloc.h"
#include "debugging.h"

#include "features.h"
#include "output/output.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RETURN_PATH(path, len) (				 \
	is_link_tg									 \
		? path : memcpy(emalloc(len), path, len) \
)

const char *getDisplayPath(const char *const path, const namlen_t path_len) {
	assert(path != NULL);

	// path_len is being overloaded, so that it can track whether this function is being
	//	called to create a display path for a main input file, or for the target of a symlink
	const bool is_link_tg = (path_len == IS_LINK_TARGET);

	path_t path_buffer = {0};
	ssize_t adj_len = -1; // the length of the path after it's been adjusted
	char *adj_path, *PWD = path_buffer;

	// if this func is being called to create a path for a main input file ...
	if (!is_link_tg) {
		// ... then check if the path is the dot dir, i.e. `if (path == ".")`
		if ((path[0] == '.' && path[1] == '\0')) {
			// if `path` _is_ ".", then convert that into the full path to `$PWD`
			// `getenv` returns a pointer to a string ...
			PWD = getenv("PWD");

			if (PWD != NULL) {
				// ... so we need to fill the path buffer with the result of `getenv`.
				// note: since we're going to need the length of `PWD` later, we might as well get its `strlen` now
				memcpy(path_buffer, PWD, ( adj_len = strlen(PWD) ));

			} else { // if `getenv` fails for some reason, then fall back to using `getcwd`
				// unlike `getenv`, `getcwd` fills the path buffer directly
				//	note: the reason we use `getenv("PWD")` first, is because the `$PWD` environment variable
				//		preserves symlinks, whereas `getcwd` will resolve symlinks when getting `$PWD`
				PWD = getcwd(PWD, sizeof(path_buffer));
				// if `getcwd` also doesn't work, then there's nothing we can really do - return failure
				if (PWD == NULL) return NULL;

				// if `getcwd` succeeds, then to avoid really complex checks later, get its `strlen` now
				adj_len = strlen(PWD);
			}

		} else { // if `path` isn't ".", then just copy `path` into `path_buffer`
			assert(path_len >= 1);
			// fill the path buffer with the inputted string
			memcpy(path_buffer, path, ( adj_len = path_len ));
		}
		adj_path = path_buffer; // by this point, `path_buffer` is definitely full, so we can point `adj_path` to it

	} else { // if we _are_ just making a link target, then `path` is mutable, so point `adj_path` to the input
		adj_path = (char*)path;
		adj_len = strlen(path);
	}

	// no matter which route we went down above, we need to try and replace `$HOME` with `~` - so find `$HOME`.
	const char *const HOME = getenv("HOME");
	const ssize_t home_len = strlen(HOME); // and find its length too - this is unavoidable

	if (HOME == NULL || home_len == 0				// make sure that we successfully got the `$HOME` var,
		|| adj_len <= home_len						// that `$PWD != $HOME`, so we don't replace the bare path
		|| strncmp(HOME, adj_path, home_len) != 0	// and make sure that we're actually in a subdir of $HOME
	) return RETURN_PATH(adj_path, adj_len + 1); // if we can't replace `$HOME` with `~`, then return `adj_path` as-is

	// replace `$HOME` with `~`
	adj_path[home_len - 1] = '~';

	adj_path += home_len - 1;
	adj_len  -= home_len - 1;

	// if we're not creating a link target, allocate some memory for this newly created path
	//	also note: I'm using `memcpy` & `malloc` instead of `strdup`, since I already know the path's length
	return RETURN_PATH(adj_path, adj_len + 1);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char* choosePath(const FileStat *const pFS) {
	if (pFS->display != NULL			 ) return pFS->display;
	if (pFS->path	 != NULL && DO_PATH()) return pFS->path;

	return pFS->name;
}

void print_name(const FileStat *const pFS) {
	const char *const name_or_path = choosePath(pFS);
	printEscdName(name_or_path, file_colour_esc[pFS->file_col], true);

	if (pFS->display != NULL) efree((void*)pFS->display);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)|escd/g
