/// @file features/links/links.c

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "malloc.h"
#include "debugging.h"
#include "output/output.h"
#include "options/options.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

#define DEFAULT_ALLOCATOR	NULL /** Also equivalent to `kCFAllocatorDefault`. */
#define IGNORE_ERRORS		NULL

#define FILE_IS_APPLE_ALIAS		true
#define FILE_IS_NOT_APPLE_ALIAS	false

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Checks whether an inputted path points to an Apple alias file, and resolves the alias if it does.
 *
 * @param target_buffer[out]
 *		The string in which the path to the target of the alias file will be stored, if the function succeeds.
 * @param is_valid_alias[out]
 *		Set to `true` if `alias_path` is an Apple alias file, and points to a file which exists.
 *			Set to `false` in all other cases.
 * @param alias_path[in] The path pointing to the file to be checked.
 *
 * @return `true` if the file at `alias_path` is an Apple alias file, `false` otherwise.
 */
static inline bool resolveAppleAlias(
	path_t target_buffer, ssize_t *const target_len,
	bool *const is_valid_alias, const path_t alias_path
) {
	*is_valid_alias = false, *target_len = -1;

	/* ——————————————————————————————————————————————————————————— */

	// convert `alias_path` to a CF URL object
	//	this just reads the raw path and converts it into a format that the CF library can understand
	const CFURLRef path_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ DEFAULT_ALLOCATOR,
		/* buffer		*/ (UInt8*)alias_path,
		/* bufLen		*/ strlen(alias_path),
		/* isDirectory	*/ false
	);

	if (path_url == NULL) {
		// if the function above fails, something's gone wrong, because it doesn't actually read the file -
		//	it just converts the path into a URL - it doesn't even check if the path passed exists.
		debug(ERROR, "'%s': failed to convert path into URL object", alias_path);
		return FILE_IS_NOT_APPLE_ALIAS;
	}

	/* ——————————————————————————————————————————————————————————— */

	// read the alias file into a bookmark `CFData` object
	//	this function is the one which opens and reads the file provided
	//	- it's also what causes the program to hang when reading `SF_DATALESS` files
	const CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ DEFAULT_ALLOCATOR,
		/* fileURL	 */ path_url,
		/* errorRef	 */ IGNORE_ERRORS // we don't care about catching any errors, so don't store the errorRef
	);
	CFRelease(path_url);

	if (bookmark_data == NULL) {
		#ifdef DEBUG_MODE
			if (strcasestr(alias_path, "apple") != NULL) {
				debug(WARNING, "'%s': failed to get bookmark data", alias_path);
				dline();
			}
		#endif

		// if this function failed, it's most likely because the file isn't actually an apple alias
		//	it's at this point that we're fully certain that `is_apple_alias` is false
		return FILE_IS_NOT_APPLE_ALIAS;
	}

	/* ——————————————————————————————————————————————————————————— */

	// extract the metadata stored in the bookmark, and convert it to a CF's string type
	const CFStringRef alias_string = CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ DEFAULT_ALLOCATOR,
		/* key		 */ kCFURLPathKey, // tell the function that the bookmark contains a file system path
		/* bookmark	 */ bookmark_data
	);
	CFRelease(bookmark_data);

	if (alias_string == NULL) {
		// if we couldn't convert the bookmark to a string, there's no point trying to convert it into a C-string
		debug(ERROR, "'%s': failed to convert bookmark into CFString", alias_path);
		// however, we do still know that the file is an apple alias, so return true
		//	`is_valid_alias` will remain false, though, since we can't read the target path to check
		return FILE_IS_APPLE_ALIAS;
	}

	/* ——————————————————————————————————————————————————————————— */

	// one reason `CFStringGetFileSystemRepresentation` can fail, is because the provided buffer is
	//	too small to hold the string that's supposed to be assigned to it
	// ∴ find out how long the target length is, to see if that's the reason for failure, if there is an error
	const CFIndex target_path_len = CFStringGetMaximumSizeOfFileSystemRepresentation(alias_string);

	// convert the CF string into a C-string, and store it in `target_buffer`
	const bool conversion_success = (bool)CFStringGetFileSystemRepresentation(
		/* string	 */ alias_string,
		/* buffer	 */ target_buffer,
		/* maxBufLen */ sizeof(path_t)
	);

	// if that's successful, then everything worked correctly
	if (conversion_success) {
		// finally, check whether the target file actually exists
		*is_valid_alias = FILE_EXISTS(target_buffer);
		// whether it does or it doesn't, clean up and return success
		goto return_1;
	}

	/* ——————————————————————————————————————————————————————————— */

	// check if the target path was too long to fit in the buffer
	if (target_path_len <= (CFIndex)sizeof(path_t))
		goto return_1; // if that wasn't the issue, then just clean up and return

	// allocate enough memory for the path
	// +1 for the nullbyte
	char *temp_t_path = emalloc(target_path_len + 1); /* [alloc:temp-apple-path] - freed locally */

	// try assigning the path again, now with the larger buffer
	if (!CFStringGetFileSystemRepresentation(alias_string, temp_t_path, target_path_len))
		goto return_2;

	// if it succeeded, firstly check whether the file it points to is a valid file
	*is_valid_alias = FILE_EXISTS(temp_t_path);

	// then convert the C-string into a CF string
	const CFStringRef cf_t_path = CFStringCreateWithCString(
		/* alloc	*/ DEFAULT_ALLOCATOR,
		/* cStr		*/ temp_t_path,
		/* encoding	*/ kCFStringEncodingUTF8
	);

	if (cf_t_path == NULL)
		goto return_3;

	// now that we know whether the file exists or not,
	//	truncate the path string so it'll fit in into `path_t`
	const CFStringRef trunc_t_path = CFStringCreateWithSubstring(
		/* alloc	*/ DEFAULT_ALLOCATOR,
		/* str		*/ cf_t_path,
		/* range	*/ (CFRange){ .location = 0, .length = sizeof(path_t) }
	);

	// make sure that nothing went wrong with the truncation
	if (trunc_t_path == NULL)
		goto return_4;

	// finally, if everything worked out, re-assign the truncated path to the target buffer
	(void)CFStringGetFileSystemRepresentation(
		/* string	 */ trunc_t_path,
		/* buffer	 */ target_buffer,
		/* maxBufLen */ sizeof(path_t)
	);

	/* ——————————————————————————————————————————————————————————— */

	return_4: CFRelease(trunc_t_path);
	return_3: CFRelease(cf_t_path);
	return_2: efree(temp_t_path); /* [free:temp-apple-path] - allocated locally */
	return_1: CFRelease(alias_string);

	*target_len = target_path_len;
	return FILE_IS_APPLE_ALIAS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool getLinkTargetPath(
	bool *const is_valid, bool *const is_apple, uint8_t *const err_no,
	char **const target_path, ssize_t *const target_len,
	const mode_t mode, const char *const abspath, const FileStat *const parent
) {
	*is_valid = false, *is_apple = false;

	/* ———————————————————————————————————————————————————————— */

	if (S_ISREG(mode)) {
		// if the file's a regular file, then check if it's an apple alias - if not, then return
		if (!resolveAppleAlias(*target_path, target_len, is_valid, abspath)) return false;
		*is_apple = true; // if we're here, we've successfully parsed the apple alias
		return true;
	}

	/* ———————————————————————————————————————————————————————— */

	assert(S_ISLNK(mode));
	errno = 0;

	// if the file is a symlink, then simply call `readlink` on it
	if (( *target_len = readlink(abspath, *target_path, sizeof(path_t)) ) == -1) {
		debug(WARNING, "errno set");
		*err_no = errno;
		return false;
	}

	/* ———————————————————————————————————————————————————————— */

	// empty link target
	if ((*target_path)[0] == '\0') {
		*is_valid = false;
		return true;
	}

	// if the path is already an absolute path, then we just have to confirm that it's valid
	if ((*target_path)[0] == '/') {
		*is_valid = FILE_EXISTS(*target_path);
		return true;
	}

	/* ———————————————————————————————————————————————————————— */

	// we now know that the path is a relative path

	const char *parent_path;
	namlen_t parent_len;

	// if the link file doesn't have a parent, then we have to figure it out manually
	if (parent == NULL) {
		const char *const basename = strrchr(abspath, '/');

		if (basename == NULL) {
			parent_path = "";
			parent_len = 0;
		} else {
			parent_path = abspath;
			parent_len = (namlen_t)(basename - abspath);
		}

	} else {
		parent_path = parent->path;
		parent_len = getPathLen(parent);
	}

	/* ———————————————————————————————————————————————————————— */

	// we need to have the absolute path to the link, so that we can access/parse links that aren't in $PWD
	//	so we need to recreate the link's path step by step

	// move the link path over by enough to fit its parent's path before it
	memmove(*target_path + parent_len + 1, *target_path, *target_len);
	// then copy its parent's path over
	memcpy(*target_path, parent_path, parent_len);
	// then fill in the one-byte gap with the path separator
	(*target_path)[parent_len] = '/';

	// finally, now that we have the absolute path to the target, check if it exists
	*is_valid = FILE_EXISTS(*target_path);

	// now move the `*target_path` pointer back to where the original path starts
	*target_path += parent_len + 1;

	/* ———————————————————————————————————————————————————————— */

	return true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline TargetInfo *getLink_internal(
	uint8_t *const err_no, bool *const is_apple,
	const mode_t mode, const flag_t flags, const FileStat *const parent, const char *const abspath
) {

	// we're looking for symlinks or apple links (which can only be regular files), so ignore everything else
	if (!(S_ISLNK(mode) || S_ISREG(mode))
		// also ignore dataless files - we don't want to try and read them if they're not dowloaded locally
		|| flags & SF_DATALESS
	) return NULL;

	/* ———————————————————————————————————————————————————————— */

	path_t abs_tg_path = {0};
	char * target_path = abs_tg_path;

	ssize_t target_len;
	bool is_valid;

	if (!getLinkTargetPath(
		&is_valid, is_apple, err_no,
		&target_path, &target_len,
		mode, abspath, parent
	)) return NULL;

	/* ———————————————————————————————————————————————————————— */

	// this memory is freed once the target is printed
	TargetInfo *const target = ecalloc(1, sizeof(TargetInfo)); /* [alloc:targinfo] - freed in `printFile` */

	strlcpy(target->abspath, abs_tg_path, sizeof(path_t));
	target->path_off = (namlen_t)(target_path - abs_tg_path);

	target->is_apple = is_apple;
	target->suffix = INVALID_LINK;

	if (!is_valid) return target;

	/* ———————————————————————————————————————————————————————— */

	struct stat targ_stat = {0};
	// when statting the file, use the absolute target path - we won't be able to guarantee the information otherwise
	if (lstat(abs_tg_path, &targ_stat) == -1) return target;

	target->mount	= getMountPoint(abs_tg_path, S_ISDIR(targ_stat.st_mode));
	target->suffix = getTypeSuffix(targ_stat.st_mode);
	target->colour = setFileColour(target->abspath, targ_stat.st_mode, target->mount, &targ_stat);

	return target;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

TargetInfo *getLink(FileStat *const pFS) {

	bool is_apple = false;
	const flag_t flags = pFS->s ? pFS->s->st_flags : 0;

	TargetInfo *const target = getLink_internal(
		&pFS->err_no, &is_apple,
		pFS->mode, flags, pFS->parent, pFS->abspath
	);

	/* ———————————————————————————————————————————————————————— */

	// if this link is an apple alias, then we have to update its absolute path
	//	otherwise we won't be able to recurse into it if we need to
	/// @todo make sure this doesn't interfere with any other processing that uses a file's `abspath`
	if (is_apple) {
		efree((void*)pFS->abspath); // free the old path so we don't have a memory leak
		getPureAbsPath(&pFS->abspath, &pFS->abs_len, target->abspath, strlen(target->abspath));
	}

	/* ———————————————————————————————————————————————————————— */

	return target;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_link(const FileStat *const pFS) {
	if (pFS->f == NULL || (pFS->f->target == NULL && !S_ISLNK(pFS->mode))) return;

	const TargetInfo *const target = pFS->f->target;

	/* ———————————————————————————————————————————————————————— */

	if (target == NULL) {
		const char
			*const arrow_ansi = getcol(INVALID_ARROW_COLOUR	),
			*const punct_ansi = getcol(LINK_ERR_PUNCT_COL	),
			*const error_ansi = getcol(LINK_ERR_MSG_COL		);

		printf("%s%s%s[ "  "%serror %hu%s:"  "%s %s %s]",
			arrow_ansi, EACCES_ARROW		 , punct_ansi,
			error_ansi, pFS->err_no			 , punct_ansi,
			error_ansi, strerror(pFS->err_no), punct_ansi
		);

		setActive(LINK_ERR_PUNCT_COL);
		return;
	}

	/* ———————————————————————————————————————————————————————— */

	const char *const arrow = target->is_apple ? APPLE_ARROW : SYMLINK_ARROW;
	const char *const path  = target->abspath + target->path_off;

	// if this is an invalid link
	if (target->suffix == INVALID_LINK) {
		const char *const arrow_ansi = getcol(INVALID_ARROW_COLOUR);

		printf("%s%s", arrow_ansi, arrow);
		printEscdName(path, INVALID_LINK_COLOUR, false);

		return;
	}

	/* ———————————————————————————————————————————————————————— */

	const char *const basename = getBasename(path);

	// print the arrow - different based on whether it's an apple link or normal symlink
	printf("%s%s", getcol(VALID_ARROW_COLOUR), arrow);

	// if we found a basename, then print the dirname and basname sequentially
	if (basename != NULL) {
		// copy the path up to where the basename starts
		path_t dirname = {0};
		strncpy(dirname, path, (basename + 1) - path);

		printEscdName(dirname, LINK_PATH_COLOUR, false);
		printEscdName(basename + 1, file_colour_esc[target->colour], false);

	} else {
		// if we didn't find a basename, then the path is relative, and we should just print it all at once
		printEscdName(path, file_colour_esc[target->colour], false);
	}

	// if the path should have a suffix, then reset colours and print the suffix
	if (target->suffix != '\0') printf("%s%c", getcol(RESET_ALL), target->suffix);

	// print info about the target's mount device / mounted filesystems
	print_mount(target->mount);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
