/// @file info/get-file-info.c

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "info.h"

#include "../features/ugid/ugid.h"
#include "../features/size/size.h"
#include "../features/time/time.h"
#include "../features/mode/mode.h"
#include "../features/flags/flags.h"
#include "../features/links/symlink.h"

#include "../options/options.h"
#include "../graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_IGNORE_FILE(entry) (strcmp(entry->d_name, ".." ) == 0)
#define  IS_VALID_PATH(path)  (access(path, F_OK) == 0)

// i know this can be simplified, but it's easier for me to read it this way
#define ALL_STATS_FAILED() \
	((do_link_to() && stat_did_fail && lstat_did_fail) || \
	(!do_link_to() && stat_did_fail))

#define IS_REALPATH_DIR() 													\
	(S_ISDIR(info.st_mode) /* add to the dirs array if it's a directory, */	\
		/* or if its a symlink, and the file it points to is a directory */	\
		|| (do_link_to() && S_ISLNK(info.st_mode) && file.ln_suf == DIR_SUFFIX))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool getLinkInfo(FileInfo *pFile, struct stat *pInfo, const path_t path) {
	// when this function starts, we don't know whether the file being listed is a link or not, cos `stat` has tried to
	//  resolve all symlinks.

	// so first we have to figure out whether the path we were given is valid
	//  note that the only case in which the path isn't valid is if the original file was a broken symlink
	const bool path_is_valid = IS_VALID_PATH(path);

	// find and assign the target's suffix to the struct
	//  if the path is invalid, then we know we have an invalid link
	if (!path_is_valid) pFile->ln_suf = INVALID_LINK;
	// however, if the path _is_ valid, then we need to keep some of the info about the target file that we got from
	//  `stat`, like the type, path, highlighting, etc., so that we can show it in the listing, after the arrow
	else {
		pFile->ln_suf = getTypeSuffix(pInfo->st_mode);
	}

	// whether the path was valid or not, or was even a link at all, we need to get the info of the origin file
	// to do that, we run the `lstat` syscall to get the information of the link, and then assign it to pInfo
	const bool lstat_did_fail = (lstat(path, pInfo) == -1);

	// if, once we get the original file, it wasn't a symlink, then remove the target's suffix
	if (!S_ISLNK(pInfo->st_mode)) pFile->ln_suf = NOT_LINK;

	return lstat_did_fail;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

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

static inline void parseStatObject(FileInfo *pFile, const struct stat *pInfo, const path_t path) {
	// move all the raw stat info that we need over to `file`
	pFile->nlink	= pInfo->st_nlink;
	pFile->dev_no	= pInfo->st_dev;
	pFile->inode	= pInfo->st_ino;
	pFile->flags	= pInfo->st_flags;
	pFile->mode		= pInfo->st_mode;
	pFile->size		= pInfo->st_size;
	pFile->uid		= pInfo->st_uid;
	pFile->gid		= pInfo->st_gid;
	pFile->time		= pInfo->st_mtimespec.tv_sec;

	// parse the raw stat information into more human-readable formats.
	if (do_suffix()) pFile->suffix = getTypeSuffix(pInfo->st_mode);
	if (do_flag_str()) parseFlags(pFile->flag_str, pInfo->st_flags);
	if (do_size_str())  parseSize(pFile->size_str, &(pFile->size_unit), pInfo->st_size, pInfo->st_rdev);
	if (do_mode_str())	  getMode(pFile->mode_str, pInfo->st_mode);
	if (do_usr_name())	  getUser(pFile->usr_name, pInfo->st_uid);
	if (do_grp_name())	 getGroup(pFile->grp_name, pInfo->st_gid);
	if (do_time_str())  parseTime(pFile->time_str, pInfo->st_mtimespec.tv_sec, &(pFile->time_col));

	if (do_mode_str())   checkACL(&(pFile->has_acl), path);
	if (do_mode_str()) checkXattr(&(pFile->has_xattr), path);
	if (do_link_to()  &&  S_ISLNK(pInfo->st_mode)) getLink(pFile->link_to, path);

	if (DO_COLOUR()) setFileColour(&(pFile->file_col), pInfo->st_mode, pInfo->st_flags);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getAllFileInfo(
	FileInfo dirs[], FileInfo files[],
	int *dir_count, int *file_count,
	DIR *dir_obj, const char *target_dir
) {
	*dir_count = 0, *file_count = 0;
	struct dirent *entry;

	// while there are still files to read, and while we haven't reached the maximum file limit
	while ((entry = readdir(dir_obj)) != NULL && (*dir_count + *file_count) <= MAX_FILES_IN_DIR) {
		if (DO_IGNORE_FILE(entry)) continue;

		/* ——————————————————————————————————————————————————————————————————— */

		// initialise the struct so we can assign to it later
		FileInfo file = { .is_valid = true };
		struct stat info;
		path_t path;

		// get the raw filename stored in `entry`
		strcpy(file.name, entry->d_name);

		// concatenate the target dir together with the filename to get the absolute path to the file
		sprintf(path, "%s/%s", target_dir, file.name);

		/* ——————————————————————————————————————————————————————————————————— */

		// always run the `stat` syscall, because we need to know the type of the file being pointed to.
		// if it fails, it means 1 of two things:
		//	1. it's a symlink, and the target is broken/doesn't exist
		//	2. there are some permission issues
		const bool stat_did_fail = (stat(path, &info) == -1);
		bool lstat_did_fail = false;

		// `stat` will follow symlinks, and will only return info about the target file, rather than the link itself
		//  if the `do_link_to` option is set, then we need to run `lstat` to get info about the link
		if (do_link_to()) lstat_did_fail = getLinkInfo(&file, &info, path);

		// if none of the stat calls that ran, worked, then we don't have any extra information
		//  so extract just the info that we can get from `dirent`, and parse things from there
		if (ALL_STATS_FAILED()) getInfoFromDirent(&file, &info, entry);

		/* ——————————————————————————————————————————————————————————————————— */

		parseStatObject(&file, &info, path);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of its respective array
		if (IS_REALPATH_DIR())	dirs [(*dir_count )++] = file;
		else				files[(*file_count)++] = file;
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(dir_obj);
}
