/// @file features/path/path.c

#include <errno.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "malloc.h"
#include "debugging.h"

#include "features.h"
#include "output/output.h"
#include "options/options.h"

#ifndef MAX
#	define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getPWD() ── ─────────────────────────────────────────────────────────────────────────────────────────────── */

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

	static char *PWD = NULL;
	static size_t PWD_len = 0;
	static uint8_t PWD_errno = 0;

	/* —— return cached data ————————————————————————— */

	if (did_init) {
		errno = PWD_errno;
		if (len != NULL) *len = PWD_len;
		return PWD;
	}

	did_init = true;

	/* —— try getenv & getwd ———————————————————————— */

	PWD = getenv("PWD");

	if (PWD == NULL) { // if `getenv` fails for some reason, then fall back to using `getwd`
		// unlike `getenv`, `getwd` fills the path buffer directly
		//	note: the reason we use `getenv("PWD")` first, is because the `$PWD` environment variable
		//		preserves symlinks, whereas `getwd` will resolve symlinks when getting `$PWD`
		PWD = getwd(PWD_buffer);

		// if `getwd` also doesn't work, then there's nothing we can really do - return failure
		if (PWD == NULL) {
			if (len != NULL) *len = 0;

			PWD_errno = errno,
			PWD_len = 0;

			return NULL;
		}
	}

	/* —— return ————————————————————————————————————— */

	// if `getwd` succeeds, then to avoid really complex checks later, get its `strlen` now
	if (len != NULL) *len = strlen(PWD);

	errno = PWD_errno = 0,
	PWD_len = *len;

	return PWD;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getPath() ── ────────────────────────────────────────────────────────────────────────────────────────────── */

/**
 * @fn getPath
 * @brief Get the path to the given file, relative to its most senior parent.
 */
const char *getPath(FileStat *const file) {
	// if we've already found this path before, then just return a pointer to it
	if (file->path != NULL) return file->path;

	/* —— base case ————————————————————————————————————————— */

	FileStat *const parent = file->parent;

	// if this file doesn't have any parents, then we know that its name is already a valid path
	if (parent == NULL) {
		file->path = file->name;
		return file->name;
	}

	// neither of their lengths should be 0 or -1
	assert(file->name_len >= 1 && parent->name_len >= 1);

	/* —— get parent's path ————————————————————————————————— */

	// recurse until we have the full path to the parent, then calculate its path len
	const char *const parent_path = getPath(parent);
	const namlen_t parent_plen = getPathLen(parent);

	/* —— get path len & verify size ———————————————————————— */

	// check the resultant size, including the parent path, the `/`, the child's name, and a null terminator
	const size_t child_size = parent_plen + 1 + file->name_len + 1;
	// make sure that the resultant child path won't be too long once we create it
	if (child_size > sizeof(path_t)) return NULL;

	/* —— copy parent's path ———————————————————————————————— */

	// allocate memory for this file's path, then copy the parent's path into the buffer
	//	(note: no need to copy the nullbyte, so no +1 for the length)
	char *const path = memcpy(emalloc(child_size), parent_path, parent_plen); /* [alloc:filepath] - free: printFile */
	//i)path = "/path/to/parent"

	/* —— append name to path ——————————————————————————————— */

	// add the path separator
	path[getPathLen(parent)] = '/';
	//i)path = "/path/to/parent/"

	// append the file's name to the end of the path
	memcpy(path + 1 + getPathLen(parent),
		file->name,
		file->name_len + 1 // +1 for the nullbyte this time
	);
	//i)path = "/path/to/parent/child_name"

	/* —— return ———————————————————————————————————————————— */

	file->name = &path[getPathLen(parent)] + 1;
	return path;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getPureAbsPath() ── ─────────────────────────────────────────────────────────────────────────────────────── */

void getPureAbsPath(
	const char **const output, namlen_t *const output_len,
	const char	*const	input, const namlen_t	input_len
) {

	const char *path = input;
	bool did_alloc = false;

	/* —— ensure basic abspath ——————————————————————— */

	if (input[0] != '/') {
		size_t pwd_len;
		const char *const PWD = getPWD(&pwd_len);

		if (PWD == NULL) {
			*output_len = -1, *output = NULL;
			return;
		}

		char *const new_path = ecalloc(1, pwd_len + 1 + input_len + 1); /* [alloc:new-path] - freed locally */
		did_alloc = true;

		memcpy(new_path, PWD, pwd_len);
		new_path[pwd_len] = '/';
		memcpy(new_path + pwd_len + 1, input, input_len);

		path = new_path;
	}

	/* —— set up segment vars ———————————————————————— */

	typedef char seg_t[MAX_NAME_LEN];

	seg_t  *segments = NULL;
	size_t *seg_lens = NULL;
	size_t seg_count = 0, seg_alloc = 0, total_len = 0;

	const char *ppath = path;

	/* —— create & proc segments ————————————————————— */

	while (*ppath != '\0') {
		while (*ppath == '/') ppath++; // skip leading and repeated slashes
		if (*ppath == '\0') break; // stop if there are no more segments

		const char *const segment = ppath; // find the start of the new segment
		while (*ppath != '\0' && *ppath != '/') ppath++; // then iterate to the end of the segment

		const size_t seg_len = ppath - segment;

		// ignore the `.` segment
		if (seg_len == 1 && segment[0] == '.') continue;

		// ignore the `..` segment, as well as the segment before it
		if (seg_len == 2 && segment[0] == '.' && segment[1] == '.') {
			if (seg_count > 0) { // `seg_count` should never drop below 0
				// decrement the total length by the length of the previous segment
				// decrement the count so that the next segment overwrites the previous one
				total_len -= seg_lens[--seg_count];
			}
			continue;
		}

		/* —— malloc & assign segment ———————————————————— */

		if (seg_count + 1 > seg_alloc) {
			MULT_BY_1_5(seg_alloc);
			/* [alloc:segments] - freed locally */
			segments = erealloc(segments, seg_alloc * sizeof(seg_t ));
			seg_lens = erealloc(seg_lens, seg_alloc * sizeof(size_t));
		}

		total_len += seg_len;
		seg_lens[seg_count] = seg_len;

		memcpy(segments[seg_count], segment, seg_len);
		segments[seg_count++][seg_len] = '\0';
	}

	if (did_alloc) efree((void*)path); /* [free:new-path] - alloced locally */

	/* —— concatenate segments ——————————————————————— */

	assert(total_len + seg_count + 1 <= INT16_MAX);

	// the total length of the path segments, +1 for each segment (to add `/`), +1 for the null terminator
	//	however, always make sure that the length is at least 2, in the case of the `/\0` path
	*output_len = MAX(2, total_len + seg_count + 1);

	*output = emalloc(*output_len * sizeof(char)); /* [alloc:abs-path] - freed in `printFile` */
	char *outptr = (char*)*output;

	// always begin the output with `/` - this guarantees the path is valid, even if there aren't any segments
	*outptr++ = '/';

	// iterate through the segments' array, adding each segment to the output string one by one
	for (size_t i = 0; i < seg_count; i++) {
		if (i != 0) *outptr++ = '/';

		memcpy(outptr, segments[i], seg_lens[i]);
		outptr += seg_lens[i];
	}

	/* —— set return vars & cleanup —————————————————— */

	/* [free:segments] - alloced locally */
	efree(segments);
	efree(seg_lens);

	// null-terminate the output string, and return the result
	*outptr++ = '\0';

	// the length of the output should be the same as the output length we calculated
	assert((namlen_t)(outptr - *output) == *output_len);

	(*output_len)--; // -1 to account for the null byte
}

/* ── ── getAbsPath() ── ─────────────────────────────────────────────────────────────────────────────────────────── */

const char *getAbsPath(FileStat *const pFS) {

	if (pFS->abspath != NULL) return pFS->abspath;

	if (pFS->parent == NULL) {
		getPureAbsPath(&pFS->abspath, &pFS->abs_len, pFS->path, getPathLen(pFS));
		return pFS->abspath;
	}

	/* ——————————————————————————————————————————————— */

	const char *const parent_path = ( pFS->parent->abspath = getAbsPath(pFS->parent) );
	const namlen_t parent_len = pFS->parent->abs_len;

	namlen_t path_len = parent_len + 1 + pFS->name_len + 1;
	assert(path_len <= INT16_MAX);

	char *const path = memcpy(emalloc(path_len), parent_path, parent_len); /* [alloc:abs-path] - see below */
	path[parent_len] = '/';
	memcpy(path + parent_len + 1, pFS->name, pFS->name_len);

	path[path_len - 1] = '\0';

	pFS->abs_len = path_len - 1; // -1 to account for the null byte
	return ( pFS->abspath = path );
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getBasename() ── ────────────────────────────────────────────────────────────────────────────────────────── */

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
/* ── ── print_name() ── ── ──────────────────────────────────────────────────────────────────────────────────────── */

#define isFSHardlink(p_fs) \
	((!S_ISDIR((p_fs)->mode)) && ((p_fs)->s != NULL) && ((p_fs)->s->st_nlink > 1))

static inline const char* choosePath(const FileStat *const pFS) {
	if (pFS->abspath != NULL && DO_ABS ()) return pFS->abspath;
	if (pFS->path != NULL && (DO_PATH() || pFS->parent == NULL)) return pFS->path;
	return pFS->name;
}

void print_name(const FileStat *const pFS) {
	const char *const name_or_path = choosePath(pFS);

	Colour colour = file_colour_esc[pFS->file_col];
	if (isFSHardlink(pFS)) colour.style |= G_HARDLINK;
	if (doDimFile(pFS) && !has_bg(colour)) colour.style |= G_DIM;

	printEscdName(name_or_path, colour, true);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /(?<!\w)-W(\w+)|escd/g
