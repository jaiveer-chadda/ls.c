/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <dirent.h>
#include <sys/stat.h>

#include "main.h"
#include "mode.h"
#include "time.h"
#include "model/stat-model.h"

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PRINT_HEADER \
	printf("%-12s nlink\tsize\tuid\tgid\t%-10s  %-20s  name\n", "mode", "flags", "mtime")

#define PRINT_FILE_INFO(file) \
	printf("%-12s "	, file.mode_str	); /* Mode of file			*/ \
	printf("%d\t\t"	, file.nlink	); /* Number of hard links	*/ \
	printf("%lld\t"	, file.size		); /* file size, in bytes	*/ \
	printf("%d\t"	, file.uid		); /* User ID of the file	*/ \
	printf("%d\t"	, file.gid		); /* Group ID of the file	*/ \
	printf("%-10d  ", file.flags	); /* user defined flags	*/ \
	printf("%-20s  ", file.time_str	); /* time last modified	*/ \
	printf("%s"		, file.name		); /* entry name			*/ \
	printf("%c"		, file.suffix	); /* filetype indicator	*/ \
	printf("\n")

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	if (argc < 2) strcpy(target_dir, ".");
	else strncpy(target_dir, argv[1], strlen(argv[1]));

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "%s: Unable to read directory `%s`\n", argv[0], target_dir);
		return EXIT_FAILURE;
	}

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	FileInfo all_files[MAX_FILES_IN_DIR];

	struct dirent *entry;
	struct stat info;

	int count = 0;
	int retcode;

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	PRINT_HEADER;

	while (
		(entry = readdir(directory)) != NULL &&
		count++ <= MAX_FILES_IN_DIR
	) {
		if DO_IGNORE_FILE(entry) continue;

		FileInfo file = {0};

		strcpy(file.name, entry->d_name);
		snprintf(file.path, MAX_PATH_LEN, "%s/%s", target_dir, file.name);

		retcode = stat(file.path, &info);
		if (retcode == -1) continue;

		/* ——————————————————————————————————————————————————————————————————————— */

		file.nlink	= info.st_nlink,
		file.size	= info.st_size,
		file.uid	= info.st_uid,
		file.gid	= info.st_gid,
		file.flags	= info.st_flags,
		file.mode	= info.st_mode,
		file.suffix	= getTypeSuffix(info.st_mode);

		getMode(info, file.mode_str);
		parseTime(info.st_mtimespec.tv_sec, file.time_str);

		/* ——————————————————————————————————————————————————————————————————————— */

		all_files[count - 1] = file;
		PRINT_FILE_INFO(file);
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun 26  01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]{1,3}\B/gi
