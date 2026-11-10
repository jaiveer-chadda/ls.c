/// @file features/links/links.c

#include <errno.h>
#include <fcntl.h> // AT_FDCWD, AT_SYMLINK_NOFOLLOW
#include <assert.h>
#include <unistd.h> // faccessat(), F_OK
#include <string.h> // strlcpy(), strrchr(), strlen(), memcpy(), memmove()

#include "malloc.h"
#include "debugging.h"
#include "options/options.h" // LINKS_TO_LINKS(), MAX_LINKS()
#include "features/features.h" // FILE_EXISTS()

/* ── Definitions & Declarations ─────────────────────────────────────────────────────────────────────────────────── */

bool resolveAppleAlias(
	path_t target_buffer, ssize_t *const target_len,
	bool *const is_valid_alias, const path_t alias_path
); // defined in features/links/apple.c

#define FILE_EXISTS(path) (faccessat(AT_FDCWD, (path), F_OK, AT_SYMLINK_NOFOLLOW) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getLinkTargetPath() ── ──────────────────────────────────────────────────────────────────────────────────── */

static inline bool getLinkTargetPath(
	bool *const is_valid, bool *const is_apple, error_t *const err_no,
	char **const target_path, ssize_t *const target_len,
	const mode_t mode, const char *const abspath, const FileStat *const parent
) {
	*is_valid = false, *is_apple = false;

	/* —— Handle Apple Aliases ———————————————————————————————— */

	if (S_ISREG(mode)) {
		// if the file's a regular file, then check if it's an apple alias - if not, then return
		if (!resolveAppleAlias(*target_path, target_len, is_valid, abspath)) return false;
		*is_apple = true; // if we're here, we've successfully parsed the apple alias
		return true;
	}

	/* —— Read Raw Symlink Target ————————————————————————————— */

	assert(S_ISLNK(mode));
	errno = 0;

	// if the file is a symlink, then simply call `readlink` on it
	if (( *target_len = readlink(abspath, *target_path, sizeof(path_t)) ) == -1) {
		*err_no = errno;
		return false;
	}

	/* —— Path Empty / Already Absolute ——————————————————————— */

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

	/* —— Find Parent Path ———————————————————————————————————— */

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

	/* —— Construct Absolute Path ————————————————————————————— */

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

	/* —— Return —————————————————————————————————————————————— */

	return true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getLink_internal() ── ───────────────────────────────────────────────────────────────────────────────────── */

static inline TargetInfo *getLink_internal(
	error_t *const err_no, bool *const is_apple,
	const mode_t mode, const flag_t flags, const FileStat *const parent, const char *const abspath, const uint8_t depth
) {

	/* —— Prune Non-Link Files ———————————————————————————————— */

	// we're looking for symlinks or apple links (which can only be regular files), so ignore everything else
	// also ignore dataless files - we don't want to try and read them if they're not dowloaded locally
	if (!(S_ISLNK(mode) || S_ISREG(mode)) || flags & SF_DATALESS) return NULL;

	/* —— Get Target's Absolute Path —————————————————————————— */

	path_t targ_abspath = {0};
	char *target_path = targ_abspath;

	ssize_t target_len;
	bool is_valid;

	if (!getLinkTargetPath(
		&is_valid, is_apple, err_no,
		&target_path, &target_len,
		mode, abspath, parent
	)) return NULL;

	/* —— Create Target Object & Validate ————————————————————— */

	// this memory is freed once the target is printed
	TargetInfo *const target = ecalloc(1, sizeof(TargetInfo)); /* [alloc:targinfo] - freed in `printFile` */

	strlcpy(target->abspath, targ_abspath, sizeof(path_t));
	target->path_off = (namlen_t)(target_path - targ_abspath);

	target->is_apple = *is_apple;
	target->suffix = INVALID_LINK;

	if (!is_valid) return target;

	/* —— `lstat` Target Path ————————————————————————————————— */

	struct stat targ_stat = {0};
	// when statting the file, use the absolute target path - we won't be able to guarantee the information otherwise
	if (lstat(targ_abspath, &targ_stat) == -1) return target;

	target->mount  = getMountPoint(targ_abspath, S_ISDIR(targ_stat.st_mode));
	target->suffix = getTypeSuffix(targ_stat.st_mode);
	target->colour = setFileColour(target->abspath, targ_stat.st_mode, target->mount, &targ_stat);

	/* —— Recurse ————————————————————————————————————————————— */

	if (LINKS_TO_LINKS()) {
		// `MAX_LINKS` is usually equivalent to `MAXSYMLINKS`
		if (depth < MAX_LINKS()) {
			bool r_is_apple = false;

			target->target = getLink_internal(
				&target->targ_err, &r_is_apple,
				targ_stat.st_mode, targ_stat.st_flags, /*parent*/ NULL, targ_abspath, depth + 1
			);
		} else {
			target->targ_err = (error_t)ELOOP;
		}
	}

	/* —— Return —————————————————————————————————————————————— */

	return target;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── getLink() ── ────────────────────────────────────────────────────────────────────────────────────────────── */

TargetInfo *getLink(FileStat *const pFS) {

	/* —— Get Main Link Object ———————————————————————————————— */

	bool is_apple = false;
	error_t targ_err = ( errno = 0 );
	const flag_t flags = pFS->s ? pFS->s->st_flags : 0;

	TargetInfo *const target = getLink_internal(
		&targ_err, &is_apple,
		pFS->mode, flags, pFS->parent, pFS->abspath, /*depth*/ 1
	);

	if (pFS->f != NULL) pFS->f->targ_err = targ_err;

	/* —— Set Abspath if Apple ———————————————————————————————— */

	// if this link is an apple alias, then we have to update its absolute path
	//	otherwise we won't be able to recurse into it if we need to
	/// @todo make sure this doesn't interfere with any other processing that uses a file's `abspath`
	if (is_apple) {
		efree((void*)pFS->abspath); // free the old path so we don't have a memory leak
		// the length of `target->abspath` is only needed once - here - so it's fine that we use `strlen` on it
		getPureAbsPath(&pFS->abspath, &pFS->abs_len, target->abspath, strlen(target->abspath));
	}

	/* —— Return —————————————————————————————————————————————— */

	return target;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
