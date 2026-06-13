/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/stat-model.h"
#include "flags/flags.h"
#include "path/path.h"

#include "main.h"
#include "time/time.h"
#include "mode/mode.h"

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	if (argc <= 1 || strlen(argv[1]) == 0) {
		strcpy(target_dir, ".\0");
	} else {
		strncpy(target_dir, argv[1], strlen(argv[1]));
		target_dir[strlen(argv[1])] = '\0';
	}

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "%s: Unable to read directory `%s`\n", argv[0], target_dir);
		return EXIT_FAILURE;
	}

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	(void) printAbsolutePath(target_dir);
	PRINT_HEADER;

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	FileInfo all_files[MAX_FILES_IN_DIR];

	struct dirent *entry;
	struct stat info;

	int count = 0;

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	while ((entry = readdir(directory)) != NULL && count <= MAX_FILES_IN_DIR) {
		if DO_IGNORE_FILE(entry) continue;

		FileInfo file = {0};

		strcpy(file.name, entry->d_name);
		snprintf(file.path, MAX_PATH_LEN, "%s/%s", target_dir, file.name);

		if (stat(file.path, &info) == -1) continue;

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
		parseFlags(file.flag_str, info.st_flags);

		/* ——————————————————————————————————————————————————————————————————————— */

		PRINT_FILE_INFO(file);
		all_files[count++] = file;
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
