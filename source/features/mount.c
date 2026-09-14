/// @file features/mount/mount.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>

#include "malloc.h"
#include "model/stat-model.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const MountInfo *getMountPoint(const char *const path) {
	// resolve the target path to a clean absolute path
	path_t abs_path;
	if (realpath(path, abs_path) == NULL) return NULL;

	// get filesystem stats for the path
	struct statfs mt_stat;
	if (statfs(abs_path, &mt_stat) != 0) return NULL;

	// compare the requested absolute path to the filesystem's mount location
	// if the mount location _is_ the path, then the file's a mount point
	if (strcmp(abs_path, mt_stat.f_mntonname) != 0) return NULL;

	MountInfo *const mt_info = emalloc(sizeof(MountInfo));

	*mt_info = (MountInfo){0};

	return mt_info;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printMountDevice(const name_t filename) {
	// get the absolute path to the filename
	path_t abs_path;
	if (realpath(filename, abs_path) == NULL) return;

	// get filesystem stats for the path
	struct statfs dev_info;
	if (statfs(abs_path, &dev_info) != 0) return;

	// /// FIXME:
	// // recreating `eza`s format: `[source (filesystem)]`
	// printf(" %s%s" "%s%s" " %s%s" "%s%s" "%s%s" "%s%s" "%s",
	// 	ANSI(MTPT_COL_PUNC_1), "[",
	// 	ANSI(MTPT_COL_FROM	), dev_info.f_mntfromname,
	// 	ANSI(MTPT_COL_PUNC_2), "(",
	// 	ANSI(MTPT_COL_TYPE	), dev_info.f_fstypename,
	// 	ANSI(MTPT_COL_PUNC_2), ")",
	// 	ANSI(MTPT_COL_PUNC_1), "]",
	// 	RESET
	// );
}
