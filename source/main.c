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
#include "options/options.h"

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

char* get_fmt_str(const char *field) {
	// suffix == char == %c
	if (strcmp(field, "suffix") == 0) return "%c";

	// name, usr_name, grp_name, size_str, flag_str, mode_str, time_str 
	//  == char* == %s
	const char *str_to_cmp = field + (strlen(field) - 4);
	if ( strcmp(str_to_cmp, "name") == 0 ||
		 strcmp(str_to_cmp, "_str") == 0 ) return "%s";

	// dev_no, time, size, inode, nlink, flags, mode, uid, gid
	//  == [unsigned] (int | long [long]) ≈≈ %lld
	return "%lld";

	// so technically the types are:
	//	- dev_no				:			int
	//	- nlink,flags,mode,ugid	:  unsigned	int
	//	- time					:			long
	//	- size					:			long long
	//	- inode					:  unsigned	long long
	// but I can't be arsed to do a proper check for all of those,
	//  and since `%lld` should work for them all, this is just easier
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	DIR *directory = getDirectory(target_dir, argc, argv);
	if (directory == NULL) return EXIT_FAILURE;

	initTime();

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	FileInfo all_files[MAX_FILES_IN_DIR];

	struct dirent *entry;
	struct stat info;
	path_t path;

	int count = 0;

	/* ——————————————————————————————————————————————————————————————————————— */

	// while there are still files to read, and while we haven't reached the maximum file limit
	while ((entry = readdir(directory)) != NULL && count <= MAX_FILES_IN_DIR) {
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
		file.nlink	= info.st_nlink,
		file.size	= info.st_size,
		file.uid	= info.st_uid,
		file.gid	= info.st_gid,
		file.flags	= info.st_flags,
		file.mode	= info.st_mode,
		file.inode	= info.st_ino,

		// get the character that'll be put at the end of the filename (`/`, `*`, `=`, etc.)
		file.suffix	= getTypeSuffix(info.st_mode);

		// parse the raw stat information into more human-readable formats.
		getMode(file.mode_str, info.st_mode);
		parseTime(file.time_str, info.st_mtimespec.tv_sec);
		parseFlags(file.flag_str, info.st_flags);
		getUser(file.usr_name, file.uid);
		getGroup(file.grp_name, file.gid);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of the array
		all_files[count++] = file;
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(directory);

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	// casting to void, since we don't rly care whether the path is printed - it's honestly just a bonus.
	(void) printAbsolutePath(target_dir);

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	initLengths();

	size_t len;
	char fmt_str[5];
	char elem_as_str[64];

	#define PARSE_LEN(field) \
		if (do_##field) { \
			strcpy(fmt_str, get_fmt_str(#field)); \
			sprintf(elem_as_str, fmt_str, file.field);\
			len = strlen(elem_as_str); \
			if (len > field_lengths.field) field_lengths.field = len; \
		}

	// run through all the files' fields and calculate their maximum lengths
	for (int i = 0; i < count; i++) {
		FileInfo file = all_files[i];
		PARSE_LEN(mode_str);
		PARSE_LEN(nlink);
		PARSE_LEN(size);
		PARSE_LEN(uid);
		PARSE_LEN(usr_name);
		PARSE_LEN(gid);
		PARSE_LEN(grp_name);
		PARSE_LEN(flag_str);
		PARSE_LEN(time_str);
		PARSE_LEN(name);
		PARSE_LEN(suffix);
	}

	/* ——————————————————————————————————————————————————————————————————————— */

	if (DO_HEADER) {
		if (do_mode_str)	printf("%-*s  "	, (int)field_lengths.mode_str,	  MODE_STR_TITLE );
		if (do_nlink)		printf("%-*s  "	, (int)field_lengths.nlink,		  NLINK_TITLE	 );
		if (do_size)		printf("%-*s  "	, (int)field_lengths.size,		  SIZE_TITLE	 );
		if (do_uid)			printf("%-*s  "	, (int)field_lengths.uid,		  UID_TITLE		 );
		if (do_usr_name)	printf("%-*s  "	, (int)field_lengths.usr_name,	  USR_NAME_TITLE );
		if (do_gid)			printf("%-*s  "	, (int)field_lengths.gid,		  GID_TITLE		 );
		if (do_grp_name)	printf("%-*s  "	, (int)field_lengths.grp_name,	  GRP_NAME_TITLE );
		if (do_flag_str)	printf("%-*s  "	, (int)field_lengths.flag_str,	  FLAG_STR_TITLE );
		if (do_time_str)	printf("%-*s  "	, (int)field_lengths.time_str,	  TIME_STR_TITLE );
		if (do_name)		printf("%*s"	, (int)field_lengths.name,		  NAME_TITLE	 );

		printf("\n");
	}

	/* ——————————————————————————————————————————————————————————————————————— */

	for (int i = 0; i < count; i++) {
		FileInfo file = all_files[i];

		if (do_mode_str)	printf("%-*s" "  ", (int)field_lengths.mode_str	, file.mode_str	);
		if (do_nlink)		printf("%-*d" "  ", (int)field_lengths.nlink	, file.nlink	);
		if (do_size)		printf("%*lld""  ", (int)field_lengths.size		, file.size		);
		if (do_uid)			printf("%-*d" "  ", (int)field_lengths.uid		, file.uid		);
		if (do_usr_name)	printf("%-*s" "  ", (int)field_lengths.usr_name	, file.usr_name	);
		if (do_gid)			printf("%-*d" "  ", (int)field_lengths.gid		, file.gid		);
		if (do_grp_name)	printf("%-*s" "  ", (int)field_lengths.grp_name	, file.grp_name	);
		if (do_flag_str)	printf("%-*s" "  ", (int)field_lengths.flag_str	, file.flag_str	);
		if (do_time_str)	printf("%*s"  "  ", (int)field_lengths.time_str	, file.time_str	);
		if (do_name)		printf("%*s"	  , (int)field_lengths.name		, file.name		);
		if (do_suffix)		printf("%c"		  , file.suffix);

		printf("\n");
	}

	return EXIT_SUCCESS;
}

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun 26  01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]{1,3}\B/gi
