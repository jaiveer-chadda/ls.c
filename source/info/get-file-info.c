/// @file info/get-file-info.c

#include <stdio.h>
#include <stdlib.h>
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
	((do_link_to() && lstat_did_fail && stat_did_fail) || \
	(!do_link_to() && lstat_did_fail))

#define IS_REALPATH_DIR() 													\
	(S_ISDIR(info.st_mode) /* add to the dirs array if it's a directory, */	\
		/* or if its a symlink, and the file it points to is a directory */	\
		|| (do_link_to() && S_ISLNK(info.st_mode) && file.ln_suf == DIR_SUFFIX))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool getTargetInfo(FileInfo *pFile, struct stat *pInfo, const path_t path) {
	// file isn't a link - keep the `lstat` info
	// we still have to try `stat` on it tho, cos if `lstat` failed, we need to know whether it failed
	//  bc the file is a link to a non-existant file, or if we don't have permissions to `stat` the file
	if (!S_ISLNK(pInfo->st_mode)) pFile->ln_suf = NOT_LINK;

	// file is a link - run `stat`
	struct stat *pLinkInfo = malloc(sizeof(struct stat));
	// whether the path was valid or not, or was even a link at all, we need to get the info of the origin file.
	//  we therefore run `lstat` to get the information of the link, assign it to pLinkInfo, then extract the info
	const bool stat_did_fail = stat(path, pLinkInfo) == -1;

	// extract the necessary info from the target file
	if (pFile->ln_suf == '\0') pFile->ln_suf = getTypeSuffix(pLinkInfo->st_mode);
	free(pLinkInfo);

	if (DO_COLOUR()) setFileColour(&(pFile->file_col), pInfo->st_mode, pInfo->st_flags);
	getLink(pFile->link_to, path);

	if (stat_did_fail) pFile->ln_suf = INVALID_LINK;

	return stat_did_fail;
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

	if (do_mode_str())   checkACL(&(pFile->has_acl	), path);
	if (do_mode_str()) checkXattr(&(pFile->has_xattr), path);

	if (DO_COLOUR()) setFileColour(&(pFile->file_col), pInfo->st_mode, pInfo->st_flags);
	if (!S_ISDIR(pInfo->st_mode)  && pInfo->st_nlink > 1) pFile->do_link_hl = true;
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

		// always run the `lstat` syscall, because we need to know the type of the original file
		const bool lstat_did_fail = lstat(path, &info) == -1;

		// `stat` will follow symlinks, and will only return info about the target file, rather than the link itself
		//  if the `do_link_to` option is set, then we need to run `lstat` to get info about the link
		const bool stat_did_fail = getTargetInfo(&file, &info, path);

		// if none of the stat calls that ran, worked, then we don't have any extra information
		//  so extract just the info that we can get from `dirent`, and parse things from there
		if (ALL_STATS_FAILED()) getInfoFromDirent(&file, &info, entry);

		/* ——————————————————————————————————————————————————————————————————— */

		parseStatObject(&file, &info, path);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of its respective array
		if (IS_REALPATH_DIR())	dirs [(*dir_count )++] = file;
		else					files[(*file_count)++] = file;
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(dir_obj);
}
