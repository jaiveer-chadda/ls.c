/// @file features/mount/mount-point.h

#ifndef MOUNT_POINT_INITIALISED
#define MOUNT_POINT_INITIALISED

#include "model/types.h"

bool isMountPoint(const dev_t dev_no, const path_t path);
void printMountDevice(const name_t filename);

#endif /* !MOUNT_POINT_INITIALISED */
