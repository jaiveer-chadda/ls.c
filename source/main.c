/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "main.h"
#include "mode.h"

static inline char* getType(const struct dirent *entry) {
	switch (entry->d_type) {
		case DT_UNKNOWN	: return "unknown"		;
		case DT_FIFO	: return "named pipe"	;
		case DT_CHR		: return "char device"	;
		case DT_DIR		: return "directory"	;
		case DT_BLK		: return "block device"	;
		case DT_REG		: return "regular file"	;
		case DT_LNK		: return "symlink"		;
		case DT_SOCK	: return "socket"		;
		case DT_WHT		: return "whiteout"		;
		default			: return ""				;
	}
}

int main(const int argc, const char *argv[]) {
	const char *ARG_ZERO = argv[0];

	char target_dir[MAX_NAME_LEN];

	if (argc < 2) strncpy(target_dir, ".", 2);
	else snprintf(target_dir, MAX_NAME_LEN, "%s", argv[1]);

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "%s: Unable to read directory `%s`\n", ARG_ZERO, target_dir);
		return EXIT_FAILURE;
	}

	struct dirent *entry;
	struct stat info;
	char target_path[MAX_PATH_LEN];
	char mode_str[MAX_MODE_LEN];

	printf("%-*s nlink\tsize\tuid\tgid\t%-10s  mtime\tname\n", MAX_MODE_LEN, "mode", "flags");

	while ((entry = readdir(directory)) != NULL) {
		if DO_IGNORE_FILE(entry) continue;

		snprintf(target_path, MAX_PATH_LEN, "%s/%s", target_dir, entry->d_name);
		stat(target_path, &info);

		getMode(info, mode_str);

		printf("%-*s "	, MAX_MODE_LEN, mode_str	); // Mode of file
		printf("%d\t\t"	, info.st_nlink				); // Number of hard links
		printf("%lld\t"	, info.st_size				); // file size, in bytes
		printf("%d\t"	, info.st_uid				); // User ID of the file
		printf("%d\t"	, info.st_gid				); // Group ID of the file
		printf("%-10d  ", info.st_flags				); // user defined flags for file
		printf("%ld\t"	, info.st_mtimespec.tv_sec	); // time of last data modification
		printf("%s"		, entry->d_name				); // entry name (up to MAXPATHLEN bytes)
		printf("%c"		, get_type_suffix(info.st_mode)); // the filetype indicator

		printf("\n");
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun '26 01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]\B/gi
