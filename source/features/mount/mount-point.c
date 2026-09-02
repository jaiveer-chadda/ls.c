/// @file features/mount/mount-point.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <sys/mount.h>

#include "mount-point.h"
#include "graphics/graphics.h"

static inline dev_t getDevNo(const path_t path) {
	struct stat file_info;
	if (stat(path, &file_info) == -1) return -1;

	return file_info.st_dev;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// ReSharper disable once CppParameterNamesMismatch
bool isMountPoint(const dev_t file_dev_no, const path_t path) {
	// resolve the target path to a clean absolute path
	path_t abs_path;
	if (realpath(path, abs_path) == NULL) return false;

	// get filesystem stats for the path
	struct statfs dev_info;
	if (statfs(abs_path, &dev_info) != 0) return false;

	// compare the requested absolute path to the filesystem's mount location
	// if the mount location _is_ the path, then the file's a mount point
	if (strcmp(abs_path, dev_info.f_mntonname) == 0) return true;

	/* —————————————————————————————————————————————— */
	// otherwise, check whether the file has a different device number to its parent

	char *path_copy = strdup(abs_path);
	if (path_copy == NULL) return false;

	const char *parent_name = dirname(path_copy);
	free(path_copy);

	return getDevNo(parent_name) != file_dev_no;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printMountDevice(const name_t filename) {
	// get the absolute path to the filename
	path_t abs_path;
	if (realpath(filename, abs_path) == NULL) return;

	// get filesystem stats for the path
	struct statfs dev_info;
	if (statfs(abs_path, &dev_info) != 0) return;

	// recreating `eza`s format: `[source (filesystem)]`
	printf(" %s%s" "%s%s" " %s%s" "%s%s" "%s%s" "%s%s" "%s",
		ANSI(MTPT_COL_PUNC_1), "[",
		ANSI(MTPT_COL_FROM	), dev_info.f_mntfromname,
		ANSI(MTPT_COL_PUNC_2), "(",
		ANSI(MTPT_COL_TYPE	), dev_info.f_fstypename,
		ANSI(MTPT_COL_PUNC_2), ")",
		ANSI(MTPT_COL_PUNC_1), "]",
		RESET
	);
}
