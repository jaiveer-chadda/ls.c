/// @file features/mount/mount-point.h

#include "../../model/stat-model.h"

bool isMountPoint(const dev_t dev_no, const path_t path);
void printMountDevice(const name_t filename);
