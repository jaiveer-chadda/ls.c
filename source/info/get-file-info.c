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

#define DO_IGNORE_FILE(entry) strcmp(entry->d_name, ".." ) == 0
#define  IS_VALID_LINK(path) (access(path, F_OK) == 0)

#define   IS_SYMLINK() ((info.st_mode & TYPE_MASK) == S_IFLNK || entry->d_type == DT_LNK)
#define IS_DIRECTORY() ((info.st_mode & TYPE_MASK) == S_IFDIR || entry->d_type == DT_DIR)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Get the All File Info object
 * 
 * @param dirs[out]
 * @param files[out]
 * @param dir_count[out]
 * @param file_count[out]
 * @param dir_obj[in,[out]]
 * @param target_dir[in]
 */
inline void getAllFileInfo(
	FileInfo dirs[], FileInfo files[],
	int *dir_count, int *file_count,
	DIR *dir_obj, const char *target_dir
) {
	*dir_count = 0, *file_count = 0;
	struct dirent *entry;

	// while there are still files to read, and while we haven't reached the maximum file limit
	while ((entry = readdir(dir_obj)) != NULL && (*dir_count + *file_count) <= MAX_FILES_IN_DIR) {
		if (DO_IGNORE_FILE(entry)) continue;

		// initialise the struct so we can assign to it later
		FileInfo file = { .is_valid = true };

		// get the raw filename stored in `entry`
		strcpy(file.name, entry->d_name);

		// concatenate the target dir together with the filename to get the absolute path to the file
		path_t path;
		sprintf(path, "%s/%s", target_dir, file.name);

		/* ——————————————————————————————————————————————————————————————————— */

		// always run the `stat` syscall, because we need to know the type of the file being pointed to.
		// if it fails, it means 1 of two things:
		//	1. it's a symlink, and the target is broken/doesn't exist
		//	2. there are some permission issues
		struct stat info;
		bool  stat_did_fail = stat(path, &info) == -1;
		bool lstat_did_fail = false;

		// then, if we need to get the link's info ...
		if (do_link_to) {
			// find and assign the target's suffix to the struct
			file.ln_suf = IS_VALID_LINK(path) ? getTypeSuffix(info.st_mode) : INVALID_LINK;

			// and then run the `lstat` syscall to get the link's information
			lstat_did_fail = lstat(path, &info) == -1;

			// if the file isn't a symlink then remove the target's suffix
			if (!IS_SYMLINK()) file.ln_suf = NOT_LINK;
		}

		// if none of the stat calls that ran, worked, then we don't have any extra information
		//  so extract just the info that we can get from `dirent`, and parse things from there
		if ((!do_link_to && stat_did_fail) || (do_link_to && stat_did_fail && lstat_did_fail)) {
			info = (struct stat){0};
			file = (FileInfo){0};

			strcpy(file.name, entry->d_name);
			info.st_mode	= DTTOIF(entry->d_type);
			info.st_ino		= entry->d_ino;
			file.ln_suf		= IS_SYMLINK() ? INVALID_LINK : NOT_LINK;
			file.is_valid	= false;
		}

		/* ——————————————————————————————————————————————————————————————————— */

		// move all the stat info that we're copying over to `file`
		file.nlink	= info.st_nlink;
		file.dev_no	= info.st_dev;
		file.inode	= info.st_ino;
		file.flags	= info.st_flags;
		file.mode	= info.st_mode;
		file.size	= info.st_size;
		file.uid	= info.st_uid;
		file.gid	= info.st_gid;
		file.time	= info.st_mtimespec.tv_sec;

		// parse the raw stat information into more human-readable formats.
		if (do_suffix	) file.suffix = getTypeSuffix(info.st_mode);
		if (do_flag_str	) parseFlags(file.flag_str, info.st_flags);
		if (do_size_str	)  parseSize(file.size_str, &(file.size_unit), info.st_size, info.st_rdev);
		if (do_mode_str	)	 getMode(file.mode_str, info.st_mode);
		if (do_usr_name	)	 getUser(file.usr_name, info.st_uid);
		if (do_grp_name	)	getGroup(file.grp_name, info.st_gid);
		if (do_time_str	)  parseTime(file.time_str, info.st_mtimespec.tv_sec, &(file.time_col));
		if (do_link_to && IS_SYMLINK()) getLink(file.link_to, path);

		if (DO_COLOUR) setFileColour(&(file.file_col), info.st_mode, info.st_flags);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of its respective array
		if (IS_DIRECTORY()  // add to the dirs array if it's a directory,
			// or if its a symlink, and the file it points to is a directory
			|| (do_link_to && IS_SYMLINK() && file.ln_suf == DIR_SUFFIX)
		) {
			dirs[(*dir_count)++] = file;
		} else {
			files[(*file_count)++] = file;
		}
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(dir_obj);
}
