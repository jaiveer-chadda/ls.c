/// @file features/mount/mount-point.c

#include "mount-point.h"

dev_t getRootDevNo(void) {
	struct stat root_info;
	if (stat("/", &root_info) == -1) return -1;

	return root_info.st_dev;
}
