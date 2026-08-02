/// @file info/get-file-info.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "info.h"

#include "utils/malloc.h"
#include "options/options.h"
#include "graphics/graphics.h"

#include "features/ugid/ugid.h"
#include "features/size/size.h"
#include "features/time/time.h"
#include "features/mode/mode.h"
#include "features/path/path.h"
#include "features/flags/flags.h"
#include "features/links/symlink.h"
#include "features/mount/mount-point.h"
#include "features/links/apple-alias.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_IGNORE_FILE(entry) (strcmp((entry)->d_name, ".") == 0 || strcmp((entry)->d_name, "..") == 0)
#define  IS_VALID_PATH(path)  (access((path), F_OK) == 0)

/// Add to the dirs array if it's a directory, or if it's a link, and the file it points to is a directory.
#define IS_REALPATH_DIR() (S_ISDIR(info.st_mode) || file.ln_suf == DIR_SUFFIX)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// called by `getFileInfo()`
static inline void parseStatObject(FileInfo *pFile, const struct stat *pInfo, const path_t path) {
	// move all the raw stat info that we need over to `file`
	pFile->nlink	= pInfo->st_nlink;
	pFile->dev_no	= pInfo->st_dev;
	pFile->rdev		= pInfo->st_rdev;
	pFile->inode	= pInfo->st_ino;
	pFile->flags	= pInfo->st_flags;
	pFile->mode		= pInfo->st_mode;
	pFile->size		= pInfo->st_size;
	pFile->uid		= pInfo->st_uid;
	pFile->gid		= pInfo->st_gid;
	pFile->time		= pInfo->st_mtimespec.tv_sec;

	// work out whether ths file is a mount point or not
	pFile->is_mount = isMountPoint(pInfo->st_dev, path);

	// parse the raw stat information into more human-readable formats.
	if (do_suffix  ()) pFile->suffix = getTypeSuffix(pInfo->st_mode);
	if (do_flag_str()) parseFlags(pFile->flag_str, pInfo->st_flags);
	if (do_size_str())	parseSize(pFile->size_str, &pFile->size_unit, &pFile->size, pInfo->st_rdev);
	if (do_mode_str())	  getMode(pFile->mode_str, pInfo->st_mode);
	if (do_usr_name())	  getUser(pFile->usr_name, pInfo->st_uid);
	if (do_grp_name())	 getGroup(pFile->grp_name, pInfo->st_gid);
	if (do_time_str())	parseTime(pFile->time_str, pInfo->st_mtimespec.tv_sec, &pFile->time_col);

	if (do_mode_str())	 checkACL(&pFile->has_acl, path);
	if (do_mode_str()) checkXattr(&pFile->has_xattr, path);

	if (DO_COLOUR()) setFileColour(&pFile->file_col, pFile->name, pInfo->st_mode, pInfo->st_flags, pFile->is_mount);
	if (!S_ISDIR(pInfo->st_mode) && pInfo->st_nlink > 1) pFile->do_link_hl = true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Extract a file's information from a `dirent` object.
 *
 * This function will only be called if both `stat` and `lstat` fail.
 * It gives the barebones amount of information that can be taken from what `dirent` gives us.
 *
 * Called by `getFileInfo()`.
 *
 * @param pFile[out] @param pInfo[out] @param entry[in]
 */
static inline void getInfoFromDirent(FileInfo *pFile, struct stat *pInfo, const struct dirent *entry) {
	*pInfo = (struct stat){0};
	*pFile = (FileInfo){0};

	strcpy(pFile->name, entry->d_name);

	pInfo->st_mode	= DTTOIF(entry->d_type);
	pInfo->st_ino	= entry->d_ino;
	pFile->ln_suf	= entry->d_type == DT_LNK ? INVALID_LINK : NOT_LINK;
	pFile->is_valid	= false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// called by `getFileInfo()`
static inline bool getTargetInfo(FileInfo *pFile, const path_t path) {
	bool stat_did_fail = false;

	// file is a link - run `stat()` to get some of the info from the target file
	struct stat target_info = {0};
	stat_did_fail = stat(path, &target_info) == -1;

	// extract the necessary info from the target file
	// i.e. only the info that is relevant to when it's printed after the -> arrow
	pFile->link_to	= getLink(path);
	pFile->ln_suf	= getTypeSuffix(target_info.st_mode);
	pFile->is_mount	= isMountPoint(target_info.st_dev, path);
	setFileColour(&pFile->link_col, pFile->link_to, target_info.st_mode, target_info.st_flags, pFile->is_mount);

	if (stat_did_fail) pFile->ln_suf = INVALID_LINK;
	return stat_did_fail;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// called by `getAllFileInfo()`
static inline void getFileInfo(
	const struct dirent *entry,
	FileInfo dirs[], FileInfo files[],
	int *dir_count, int *file_count, const char *dotdir_path
) {
	// initialise the struct so we can assign to it later
	FileInfo file = { .is_valid = true };

	// get the raw filename stored in `entry`
	strcpy(file.name, entry->d_name);

	// concatenate the target dir together with the filename to get the absolute path to the file
	path_t path;
	sprintf(path, "%s/%s", dotdir_path, file.name);

	/* ——————————————————————————————————————————————————————————————————— */

	// always run the `lstat()` syscall, because we need to know the type of the original file
	struct stat info;

	const bool lstat_did_fail = lstat(path, &info) == -1;
	bool stat_did_fail = true;

	// if the file is a link, get the information of its target
	if (S_ISLNK(info.st_mode)) {
		stat_did_fail = getTargetInfo(&file, path);

	} else if (S_ISREG(info.st_mode) && info.st_size > 0) {
		char *orig_target_path = emalloc(sizeof(path_t));

		bool is_valid_alias = false;
		const bool is_apple_alias = resolveAppleAlias(orig_target_path, &is_valid_alias, path);

		if (is_apple_alias) {
			stat_did_fail = getTargetInfo(&file, orig_target_path);
			abbrPath(file.link_to, orig_target_path);
		} else {
			file.ln_suf = NOT_LINK;
		}

	} else { // if it isn't a link, then keep the `lstat` info, and mark the file as such
		file.ln_suf = NOT_LINK;
	}

	// if none of the stat calls worked, then we don't have any extra information
	//  so extract just the info that we can get from `dirent`, and parse things from there
	if (stat_did_fail && lstat_did_fail) getInfoFromDirent(&file, &info, entry);

	/* ——————————————————————————————————————————————————————————————————— */

	parseStatObject(&file, &info, path);

	// add the `FileInfo` object to the end of its respective array
	if (IS_REALPATH_DIR())	dirs [(*dir_count )++] = file;
	else					files[(*file_count)++] = file;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// ReSharper disable once CppParameterNamesMismatch
void getAllFileInfo(
	FileInfo dirs[], FileInfo files[], int *dir_count, int *file_count, DIR *dir_obj, const char *dotdir_path)
{
	*dir_count	= 0, /// How many directories have been read & processed.
	*file_count	= 0; /// How many non-directory files have been read & processed.

	struct dirent dotdir_obj = {0};		// create a synthetic dirent for the `.` directory
	strcpy(dotdir_obj.d_name, DOTDIR);	// explicitly set the dotdir's filename
	dotdir_obj.d_type = DT_DIR;			// hardcode the filetype to directory (for the `ALL_STATS_FAILED` fallback)

	// run `getFileInfo` explicitly for `.`
	getFileInfo(&dotdir_obj, dirs, files, dir_count, file_count, dotdir_path);

	struct dirent *entry;
	// now process the rest of the directory
	while ((entry = readdir(dir_obj)) != NULL && *dir_count + *file_count <= MAX_FILES_IN_DIR) {
		// don't process the `..` directory.
		if (DO_IGNORE_FILE(entry)) continue;
		// from the file entry, get the required information, and store it in the `dirs` or `files` arrays
		getFileInfo(entry, dirs, files, dir_count, file_count, dotdir_path);
	}

	// the directory info isn't needed anymore, so it can be closed
	closedir(dir_obj);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
