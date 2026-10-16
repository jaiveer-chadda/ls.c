/// @file features/path/path.c

#include <stdio.h>
#include <errno.h>
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
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Get the program's `$PWD`, and cache it for further use.
 */
static inline const char *getPWD(size_t *const len) {
	/**
	 * The `PWD_buffer` is here in case we need to use `getwd`,
	 *	which writes to a buffer directly, rather than returning a pointer
	 */
	static char PWD_buffer[MAX_PATH_LEN];
	static bool did_init = false;
	static int PWD_errno = 0;

	static char *PWD = NULL;
	static size_t PWD_len = 0;

	if (did_init) {
		*len = PWD_len;
		errno = PWD_errno;
		return PWD;
	}

	/* ——————————————————————————————————————————————— */

	did_init = true;

	PWD = getenv("PWD");

	if (PWD == NULL) { // if `getenv` fails for some reason, then fall back to using `getwd`
		// unlike `getenv`, `getwd` fills the path buffer directly
		//	note: the reason we use `getenv("PWD")` first, is because the `$PWD` environment variable
		//		preserves symlinks, whereas `getwd` will resolve symlinks when getting `$PWD`
		PWD = getwd(PWD_buffer);

		// if `getwd` also doesn't work, then there's nothing we can really do - return failure
		if (PWD == NULL) {
			if (len != NULL) *len = 0;

			PWD_len = 0, PWD_errno = errno;
			return NULL;
		}
	}

	// if `getwd` succeeds, then to avoid really complex checks later, get its `strlen` now
	if (len != NULL) *len = strlen(PWD);

	PWD_len = *len, PWD_errno = 0;
	return PWD;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getAbsolutePath(const FileStat *const pFS) {
	char *path;

	if (pFS->path[0] == '/') {
		path = (char*)pFS->path;
	} else {
		path = ecalloc(1, MAX_PATH_LEN);

		size_t pwd_len;
		const char *const PWD = getPWD(&pwd_len);

		memcpy(path, PWD, pwd_len);
		path[pwd_len] = '/';
		memcpy(path + pwd_len + 1, pFS->path, getPathLen(pFS));
	}

	char segments[MAX_NAME_LEN][32];
	int seg_count = 0;

	char buffer[MAX_PATH_LEN];
	char *bufptr = buffer;

	for (const char *pathptr = path; *pathptr != '\0'; pathptr++) {
		if (*pathptr != '/') {
			*bufptr++ = *pathptr;
			continue;
		}

		if (pathptr != path && pathptr[-1] == '/') continue;

		*bufptr = '\0';

		if (buffer[0] == '.') {
			if (buffer[1] == '\0' || (buffer[1] == '.' && buffer[2] == '\0')) {
				if (buffer[1] == '.') seg_count--;
				bufptr = buffer;
				continue;
			}
		}

		memcpy(&segments[seg_count++], buffer, (bufptr - buffer) + 1);
		bufptr = buffer;
	}

	*bufptr = '\0';
	memcpy(&segments[seg_count++], buffer, (bufptr - buffer) + 1);

	for (int i = 0; i < seg_count; i++) {
		printf("%s", segments[i]);
		if (i != seg_count - 1) putchar('/');
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const char *getBasename(const char *const path) {
	const char *definite = NULL, *running = NULL;

	// iterate through the entire string - whenever you see a slash, update the `running` pointer, which tracks the
	//	location of the last slash we've seen, no matter what.
	// only move the `running` pointer into the `definite` variable if we've passed a character that isn't a slash.
	//	this guarantees that the slash returned by the function will never be a trailing slash
	for (const char *chr = path; *chr != '\0'; chr++) {
		if (*chr == '/') running = chr;
		else definite = running;
	}

	return definite;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RETURN_PATH(path, len) ( \
	is_link_tg ? path : memcpy(emalloc(len), path, len) /* [alloc:display-path] - freed in `print_name` */ \
)

const char *getDisplayPath(const char *const path, const namlen_t path_len) {
	assert(path != NULL);

	// path_len is being overloaded, so that it can track whether this function is being
	//	called to create a display path for a main input file, or for the target of a symlink
	const bool is_link_tg = (path_len == IS_LINK_TARGET);

	path_t path_buffer = {0};
	size_t adj_len = 0; // the length of the path after it's been adjusted
	char *adj_path;

	// if this func is being called to create a path for a main input file ...
	if (!is_link_tg) {
		// ... then check if the path is the dot dir, i.e. `if (path == ".")`
		if ((path[0] == '.' && path[1] == '\0')) {
			// if `path` _is_ ".", then convert that into the full path to `$PWD`
			const char *const PWD = getPWD(&adj_len);
				if (PWD == NULL) return NULL;

			// `getPWD` returns a pointer to a string, so we need to fill the path buffer with its result
			memcpy(path_buffer, PWD, adj_len);

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
	const size_t  home_len = strlen(HOME); // and find its length too - this is unavoidable

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

#define isFSHardlink(p_fs) \
	((!S_ISDIR((p_fs)->mode)) && ((p_fs)->s != NULL) && ((p_fs)->s->st_nlink > 1))

static inline const char* choosePath(const FileStat *const pFS) {
	if (pFS->display != NULL			 ) return pFS->display;
	if (pFS->abspath != NULL && DO_ABS ()) return pFS->abspath;
	if (pFS->path	 != NULL && DO_PATH()) return pFS->path;
	return pFS->name;
}

void print_name(const FileStat *const pFS) {
	const char *const name_or_path = choosePath(pFS);

	Colour colour = file_colour_esc[pFS->file_col];
	if (isFSHardlink(pFS)) colour.style |= G_HARDLINK;
	if (doDimFile(pFS) && !has_bg(colour)) colour.style |= G_DIM;

	printEscdName(name_or_path, colour, true);
	efree((void*)pFS->display); /* [free:display-path] - allocated in `getDisplayPath` */
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)|escd/g
