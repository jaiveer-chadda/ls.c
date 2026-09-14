/// @file features/mount/mount.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>

#include "malloc.h"
#include "options/options.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const MountInfo *getMountPoint(const char *const path, const bool is_dir) {
	// this prevents us accidentally calling `realpath` on a dir, which would
	if (!is_dir) return NULL;

	// resolve the target path to a clean absolute path
	path_t abs_path;
	if (realpath(path, abs_path) == NULL) return NULL;

	// get filesystem stats for the path
	struct statfs mt_stat;
	if (statfs(abs_path, &mt_stat) != 0) return NULL;

	// compare the requested absolute path to the filesystem's mount location
	// if the mount location _is_ the path, then the file's a mount point
	if (strcmp(abs_path, mt_stat.f_mntonname) != 0) return NULL;

	MountInfo *const mt_info = ecalloc(1, sizeof(MountInfo));

	mt_info->flags = mt_stat.f_flags;
	strncpy(mt_info->typename, mt_stat.f_fstypename	, sizeof(mttyp_t));
	strncpy(mt_info->fromname, mt_stat.f_mntfromname, sizeof(path_t	));

	return mt_info;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_mount(const MountInfo *const mount) {
	if (mount == NULL) return;

	// `[source (type)]`
	printf(" %s[%s%s"" %s(%s%s""%s)]%s",
		PUNCT_ANSI, MT_FROM_ANSI, mount->fromname,
		PUNCT_ANSI, MT_TYPE_ANSI, mount->typename,
		PUNCT_ANSI, RESET
	);

	setActive(RESET_ALL);

	efree((void*)mount);
}
