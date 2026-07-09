/// @file features/mount/mount-point.c

#include "mount-point.h"

dev_t getParentDevNo(void) {
	struct stat parent_info;
	if (stat(parent_dir_path, &parent_info) == -1) return -1;

	return parent_info.st_dev;
}
