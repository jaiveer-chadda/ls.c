/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "main.h"
#include "mode.h"
#include "time.h"

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	if (argc < 2) strncpy(target_dir, ".", 2);
	else snprintf(target_dir, MAX_NAME_LEN, "%s", argv[1]);

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "%s: Unable to read directory `%s`\n", argv[0], target_dir);
		return EXIT_FAILURE;
	}

	struct dirent *entry;
	struct stat info;

	char target_path[MAX_PATH_LEN];

	char mode_str[MAX_MODE_LEN];
	char time_str[MAX_TIME_LEN];

	printf("%-*s nlink\tsize\tuid\tgid\t%-10s  %-20s  name\n", MAX_MODE_LEN, "mode", "flags", "mtime");

	while ((entry = readdir(directory)) != NULL) {
		if DO_IGNORE_FILE(entry) continue;

		snprintf(target_path, MAX_PATH_LEN, "%s/%s", target_dir, entry->d_name);
		if (stat(target_path, &info) == -1) continue;

		getMode(info, mode_str);
		parseTime(info.st_mtimespec.tv_sec, time_str);

		printf("%-*s "	, MAX_MODE_LEN, mode_str	); // Mode of file
		printf("%d\t\t"	, info.st_nlink				); // Number of hard links
		printf("%lld\t"	, info.st_size				); // file size, in bytes
		printf("%d\t"	, info.st_uid				); // User ID of the file
		printf("%d\t"	, info.st_gid				); // Group ID of the file
		printf("%-10d  ", info.st_flags				); // user defined flags for file
		printf("%-20s  ", time_str					); // time of last data modification
		printf("%s"		, entry->d_name				); // entry name (up to MAXPATHLEN bytes)
		printf("%c"		, get_type_suffix(info.st_mode)); // the filetype indicator

		printf("\n");
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun 26  01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]{1,3}\B/gi
