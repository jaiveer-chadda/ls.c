/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "main.h"
#include "mode.h"
#include "time.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PRINT_HEADER \
	printf("%-12s nlink\tsize\tuid\tgid\t%-10s  %-20s  name\n", "mode", "flags", "mtime")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	if (argc < 2) strncpy(target_dir, ".", 2);
	else snprintf(target_dir, MAX_NAME_LEN, "%s", argv[1]);

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "%s: Unable to read directory `%s`\n", argv[0], target_dir);
		return EXIT_FAILURE;
	}

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	struct dirent *entry;
	struct stat info;

	char target_path[MAX_PATH_LEN];
	FileInfo all_files[MAX_FILES_IN_DIR];
	int count = -1;	// starting at -1 so the first value in the loop is 0

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	PRINT_HEADER;

	while ( (entry = readdir(directory)) != NULL  &&  ++count <= MAX_FILES_IN_DIR ) {
		if DO_IGNORE_FILE(entry) continue;

		snprintf(target_path, MAX_PATH_LEN, "%s/%s", target_dir, entry->d_name);
		if (stat(target_path, &info) == -1) continue;

		FileInfo file_info = {
			.nlink	= info.st_nlink,
			.size	= info.st_size,
			.uid	= info.st_uid,
			.gid	= info.st_gid,
			.flags	= info.st_flags,
			.mode	= info.st_mode,
			.suffix	= get_type_suffix(info.st_mode),
		};

		strcpy(file_info.name, entry->d_name);
		getMode(info, file_info.mode_str);
		parseTime(info.st_mtimespec.tv_sec, file_info.mtime_str);

		all_files[count] = file_info;

		/* ——————————————————————————————————————————————————————————————————————— */

		printf("%-12s "	, file_info.mode_str	); // Mode of file
		printf("%d\t\t"	, file_info.nlink		); // Number of hard links
		printf("%lld\t"	, file_info.size		); // file size, in bytes
		printf("%d\t"	, file_info.uid			); // User ID of the file
		printf("%d\t"	, file_info.gid			); // Group ID of the file
		printf("%-10d  ", file_info.flags		); // user defined flags for file
		printf("%-20s  ", file_info.mtime_str	); // time of last data modification
		printf("%s"		, file_info.name		); // entry name (up to MAXPATHLEN bytes)
		printf("%c"		, file_info.suffix		); // the filetype indicator

		printf("\n");
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun 26  01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]{1,3}\B/gi
