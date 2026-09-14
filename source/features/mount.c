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
	mt_info->owneruid = mt_stat.f_owner;

	strncpy(mt_info->typename, mt_stat.f_fstypename	, sizeof(mttyp_t));
	strncpy(mt_info->fromname, mt_stat.f_mntfromname, sizeof(path_t	));

	return mt_info;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_mount(const MountInfo *const mount) {
	if (mount == NULL) return;
	setActive(RESET_ALL);

	const char *const punct_ansi	= getcol(PUNCT);
	const char *const mt_from_ansi	= getcol(MT_FROM_COLOUR);
	const char *const mt_type_ansi	= getcol(MT_TYPE_COLOUR);

	const char *const username		= DO_MOUNT_OWNER() ? getUser(mount->owneruid) : NULL;
	const char *const username_ansi	= DO_MOUNT_OWNER() ? getcol(get_usr_colour(mount->owneruid)) : NULL;

	// `[source (type)]`
	printf(" %s[%s%s"" %s(%s%s%s)]%s",
		punct_ansi, mt_from_ansi, mount->fromname,
		punct_ansi, mt_type_ansi, mount->typename,
		punct_ansi, DO_MOUNT_OWNER() ? "" : RESET
	);

	// `[owner]`
	if (DO_MOUNT_OWNER()) {
		printf(" [%s%s%s]%s", username_ansi, username, punct_ansi, RESET);
		efree((void*)username);
	}

	setActive(RESET_ALL);
	efree((void*)mount);
}
