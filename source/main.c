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

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	DIR *directory = getDirectory(target_dir, argc, argv);
	if (directory == NULL) return EXIT_FAILURE;

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	FileInfo all_files[MAX_FILES_IN_DIR];

	struct dirent *entry;
	struct stat info;

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
		snprintf(file.path, MAX_PATH_LEN, "%s/%s", target_dir, file.name);

		// run the `stat` syscall, and assign it to `info`
		//  if there's an error (returns -1), the skip the file.
		if (stat(file.path, &info) == -1) continue;

		/* ——————————————————————————————————————————————————————————————————— */

		// move all the stat info that we're copying over to `file`
		file.nlink	= info.st_nlink,
		file.size	= info.st_size,
		file.uid	= info.st_uid,
		file.gid	= info.st_gid,
		file.flags	= info.st_flags,
		file.mode	= info.st_mode,

		// get the character that'll be put at the end of the filename (`/`, `*`, `=`, etc.)
		file.suffix	= getTypeSuffix(info.st_mode);

		// parse the raw stat information into more human-readable formats.
		getMode(info, file.mode_str);
		parseTime(info.st_mtimespec.tv_sec, file.time_str);
		parseFlags(file.flag_str, info.st_flags);

		/* ——————————————————————————————————————————————————————————————————— */

		// add the FileInfo object to the end of the array
		all_files[count++] = file;
	}

	// the directory info isn't needed anymore, so it can be closed now
	closedir(directory);

	/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	// casting to void, since we don't rly care whether the path is printed - it's honestly just a bonus.
	(void) printAbsolutePath(target_dir);

	if (DO_HEADER) printf(

		"%-12s "	// mode
		"nlink "	// nlink
		"%12s  "	// size
		"uid\t"		// uid
		"gid\t"		// gid
		"%-12s  "	// flags
		"%-20s  "	// mtime
		"name\n",	// name

		"mode",
		"size",
		"flags",
		"mtime"
	);

	/* ——————————————————————————————————————————————————————————————————————— */

	// run through all the files and print them out in the `ls --long` format
	for (int i = 0; i < count; i++) {
		FileInfo file = all_files[i];

		printf(
			"%-12s "	// mode
			"%-5d "		// nlink
			"%12lld  "	// size
			"%d\t"		// uid
			"%d\t"		// gid
			"%-12s  "	// flags
			"%-20s  "	// mtime
			"%s"		// name
			"%c\n",

			file.mode_str, file.nlink, file.size, file.uid, file.gid, file.flag_str, file.time_str,
			file.name, file.suffix
		);
	}

	return EXIT_SUCCESS;
}

/* ——————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun 26  01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]{1,3}\B/gi
