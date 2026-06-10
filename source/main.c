/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "main.h"

char* getType(const struct dirent *entry) {
	switch (entry->d_type) {
		case DT_UNKNOWN	: return "unknown"			;
		case DT_FIFO	: return "named pipe"		;
		case DT_CHR		: return "character device"	;
		case DT_DIR		: return "directory"		;
		case DT_BLK		: return "block device"		;
		case DT_REG		: return "regular file"		;
		case DT_LNK		: return "symbolic link"	;
		case DT_SOCK	: return "socket"			;
		case DT_WHT		: return "whiteout"			;
		default			: return ""					;
	}
}

void getMode(const struct stat info, char mode_str[PERMS_LEN]) {
	const int oct_mode	= info.st_mode;
	const int oct_perms	= oct_mode & PERM_MASK;

	char type_char;
	GET_TYPE_CHAR(oct_mode, type_char);

	snprintf(mode_str, PERMS_LEN, "%c %04o", type_char, oct_perms);
}

int main(const int argc, const char *argv[]) {
	char target_dir[MAXNAMLEN];

	if (argc < 2) strncpy(target_dir, ".", 2);
	else snprintf(target_dir, MAXNAMLEN, "%s", argv[1]);

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "Unable to read directory `%s`\n", target_dir);
		return EXIT_FAILURE;
	}

	struct dirent *entry;
	struct stat info;
	char target_path[MAXPATHLEN];
	char mode_str[PERMS_LEN];

	printf("%-*snlink\tsize\tuid\tgid\tflags\tmtime\t\ttype\t\tname\n", PERMS_LEN, "mode");

	while ((entry = readdir(directory)) != NULL) {
		if DO_IGNORE_FILE(entry) continue;

		snprintf(target_path, MAXPATHLEN, "%s/%s", target_dir, entry->d_name);
		stat(target_path, &info);

		getMode(info, mode_str);

		printf("%-*s\t"	, PERMS_LEN, mode_str		); // Mode of file
		printf("%d\t"	, info.st_nlink				); // Number of hard links
		printf("%lld\t"	, info.st_size				); // file size, in bytes
		printf("%d\t"	, info.st_uid				); // User ID of the file
		printf("%d\t"	, info.st_gid				); // Group ID of the file
		printf("%d\t"	, info.st_flags				); // user defined flags for file
		printf("%ld\t"	, info.st_mtimespec.tv_sec	); // time of last data modification
		printf("%s\t"	, getType(entry)			); // file type
		printf("%s\t"	, entry->d_name				); // entry name (up to MAXPATHLEN bytes)

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
