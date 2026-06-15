/// @file info/get-info.c

#include <stdio.h>
#include <string.h>

#include "info.h"

#include "../ugid/ugid.h"
#include "../size/size.h"
#include "../time/time.h"
#include "../mode/mode.h"
#include "../flags/flags.h"
#include "../links/symlink.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )

#define IS_SYMLINK(file_info) \
	((file_info.st_mode & TYPE_MASK) == S_IFLNK)

#define IS_DIRECTORY(file_info) \
	((file_info.st_mode & TYPE_MASK) == S_IFDIR)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getAllFileInfo(
	FileInfo *dirs, FileInfo *files,
	int *dir_count, int *file_count,
	DIR *directory, const char *target_dir
) {
	*dir_count = 0, *file_count = 0;

	bool stat_did_fail, lstat_did_fail;
	struct dirent *entry;
	struct stat info;
	path_t path;

	// while there are still files to read, and while we haven't reached the maximum file limit
	while ((entry = readdir(directory)) != NULL && (*dir_count + *file_count) <= MAX_FILES_IN_DIR) {
		if DO_IGNORE_FILE(entry) continue;

		// initialise the struct so we can assign to it later
		FileInfo file = {0};

		// get the raw filename stored in `entry`
		strcpy(file.name, entry->d_name);

		// concatenate the target dir together with the filename to get the absolute path to the file
		snprintf(path, MAX_PATH_LEN, "%s/%s", target_dir, file.name);

		/* ——————————————————————————————————————————————————————————————————— */

		// always run the `stat` syscall, because we need to know the type of the file being pointed to.
		// if it fails, it means 1 of two things:
		//	1. it's a symlink, and the target is broken/doesn't exist
		//	2. there are some permission issues
		stat_did_fail = stat(path, &info) == -1;

		// then, if we need to get the link's info ...
		if (do_link_to) {
			// find and assign the target's suffix to the struct
			file.ln_suf = getTypeSuffix(info.st_mode);

			// and then run the `lstat` syscall to get the link's information
			lstat_did_fail = lstat(path, &info) == -1;

			// if anything failed, or if the file isn't a symlink, then remove the target's suffix
			if (!IS_SYMLINK(info) || stat_did_fail || lstat_did_fail) file.ln_suf = '\0';

			// if neither of the stat calls worked, then we don't have any information - so skip this file
			if (stat_did_fail && lstat_did_fail) continue;

		} else {
			if (stat_did_fail) continue;
		}

		/* ——————————————————————————————————————————————————————————————————— */

		// move all the stat info that we're copying over to `file`
		if (do_suffix	) file.suffix	= getTypeSuffix(info.st_mode);
		if (do_nlink	) file.nlink	= info.st_nlink;
		if (do_dev_no	) file.dev_no	= info.st_dev;
		if (do_inode	) file.inode	= info.st_ino;
		if (do_flags	) file.flags	= info.st_flags;
		if (do_mode		) file.mode		= info.st_mode;
		if (do_size		) file.size		= info.st_size;
		if (do_uid		) file.uid		= info.st_uid;
		if (do_gid		) file.gid		= info.st_gid;

		// parse the raw stat information into more human-readable formats.
		if (do_flag_str	) parseFlags(	file.flag_str, info.st_flags);
		if (do_size_str	) parseSize(	file.size_str, info.st_size, info.st_rdev);
		if (do_mode_str	) getMode(		file.mode_str, info.st_mode);
		if (do_usr_name	) getUser(		file.usr_name, info.st_uid);
		if (do_grp_name	) getGroup(		file.grp_name, info.st_gid);
		if (do_time_str	) parseTime(	file.time_str, info.st_mtimespec.tv_sec);
		if (do_link_to && IS_SYMLINK(info)) getLink(file.link_to, path);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of its respective array
		if (IS_DIRECTORY(info) || (do_link_to && IS_SYMLINK(info) && file.ln_suf == '/')) {
			dirs[(*dir_count)++] = file;
		} else {
			files[(*file_count)++] = file;
		}
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(directory);
}
