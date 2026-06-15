/**
 * @mainpage
 * @file main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/stat-model.h"
#include "flags/flags.h"
#include "path/path.h"

#include "main.h"
#include "time/time.h"
#include "mode/mode.h"
#include "ugid/ugid.h"
#include "size/size.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define INTERFIELD_PADDING "  "

#define PARSE_LEN(field) \
	if (do_##field) { \
		sprintf(elem_as_str, fmt_strs_short.field, file.field);\
		len = strlen(elem_as_str); \
		if (len > field_lengths.field) field_lengths.field = len; \
	}

#define ADD_FIELD(field) \
	if (do_##field) { \
		strcpy(fmt_str, fmt_strs_long.field); \
		strcat(fmt_str, INTERFIELD_PADDING); \
		printf(fmt_str, (int)field_lengths.field, file.field); \
	}

#define ADD_HEADER(field) \
	if (do_##field)	{ \
		if (strcmp(field##_TITLE, "Size") == 0) \
			printf("%*s"  INTERFIELD_PADDING, (int)field_lengths.field, field##_TITLE); \
		else \
			printf("%-*s" INTERFIELD_PADDING, (int)field_lengths.field, field##_TITLE); \
	}

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline DIR* getDirectory(char *target_dir, const int argc, const char *argv[]);
static inline void getAllInfo(FileInfo *all_files, int *count, DIR *directory, const char *target_dir);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	DIR *directory = getDirectory(target_dir, argc, argv);
	if (directory == NULL) return EXIT_FAILURE;

	initTime();

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	FileInfo all_files[MAX_FILES_IN_DIR];
	int count = 0;

	getAllInfo(all_files, &count, directory, target_dir);

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	// casting to void, since we don't rly care whether the path is printed - it's honestly just a bonus.
	(void) printAbsolutePath(target_dir);

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	initLengths();

	size_t len;
	char elem_as_str[64];
	
	// run through all the files' fields and calculate their maximum lengths
	for (int i = 0; i < count; i++) {
		FileInfo file = all_files[i];
		PARSE_LEN(nlink);
		PARSE_LEN(inode);	PARSE_LEN(dev_no);
		PARSE_LEN(flags);	PARSE_LEN(flag_str);
		// mode & mode string have constant lengths
		PARSE_LEN(size);	PARSE_LEN(size_str);
		PARSE_LEN(uid);		PARSE_LEN(usr_name);
		PARSE_LEN(gid);		PARSE_LEN(grp_name);
		PARSE_LEN(time);	PARSE_LEN(time_str);
	}

	/* ——————————————————————————————————————————————————————————————————————— */

	if (DO_HEADER) {
		ADD_HEADER(inode);	ADD_HEADER(dev_no);
		ADD_HEADER(mode);	ADD_HEADER(mode_str);
		ADD_HEADER(nlink);
		ADD_HEADER(size);	ADD_HEADER(size_str);
		ADD_HEADER(uid);	ADD_HEADER(usr_name);
		ADD_HEADER(gid);	ADD_HEADER(grp_name);
		ADD_HEADER(flags);	ADD_HEADER(flag_str);
		ADD_HEADER(time);	ADD_HEADER(time_str);

		if (do_name) printf("%s", name_TITLE);
		printf("\n");
	}

	/* ——————————————————————————————————————————————————————————————————————— */

	char fmt_str[8];

	for (int i = 0; i < count; i++) {
		FileInfo file = all_files[i];

		ADD_FIELD(inode);	ADD_FIELD(dev_no);
		ADD_FIELD(mode);	ADD_FIELD(mode_str);
		ADD_FIELD(nlink);
		ADD_FIELD(size);	ADD_FIELD(size_str);
		ADD_FIELD(uid);		ADD_FIELD(usr_name);
		ADD_FIELD(gid);		ADD_FIELD(grp_name);
		ADD_FIELD(flags);	ADD_FIELD(flag_str);
		ADD_FIELD(time);	ADD_FIELD(time_str);

		if (do_name)	printf(fmt_strs_long.name	, file.name);
		if (do_suffix)	printf(fmt_strs_long.suffix	, file.suffix);
		printf("\n");
	}

	return EXIT_SUCCESS;
}

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline DIR* getDirectory(char *target_dir, const int argc, const char *argv[]) {
	// if there's no input, or the input is empty, then the target directory is `.`
	if (argc <= 1 || strlen(argv[1]) == 0) {
		strcpy(target_dir, "."); 
	// otherwise, copy the user's input verbatim into `target_dir`
	} else {
		strncpy(target_dir, argv[1], MAX_NAME_LEN - 1);
		target_dir[MAX_NAME_LEN - 1] = '\0';
	}

	DIR *directory = opendir(target_dir);
	// if we couldn't open the directory (usually if it doesn't exist), then exit with an error
	if (directory == NULL) perror("opendir");

	return directory;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getAllInfo(FileInfo *all_files, int *count, DIR *directory, const char *target_dir) {
	struct dirent *entry;
	struct stat info;
	path_t path;

	// while there are still files to read, and while we haven't reached the maximum file limit
	while ((entry = readdir(directory)) != NULL && *count <= MAX_FILES_IN_DIR) {
		if DO_IGNORE_FILE(entry) continue;

		// initialise the struct so we can assign to it later
		FileInfo file = {0};

		// get the raw filename stored in `entry`
		strcpy(file.name, entry->d_name);

		// concatenate the target dir together with the filename to get the absolute path to the file
		snprintf(path, MAX_PATH_LEN, "%s/%s", target_dir, file.name);

		// run the `stat` syscall, and assign it to `info`
		//  if there's an error (returns -1), the skip the file.
		if (stat(path, &info) == -1) continue;

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
		if (do_link_to	) getLink(		file.link_to , path);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of the array
		all_files[(*count)++] = file;
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(directory);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun 26  01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]{1,3}\B/gi
