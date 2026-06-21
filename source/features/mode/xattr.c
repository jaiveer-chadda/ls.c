/// @file features/mode/xattr.c

#include <sys/xattr.h>
#include "../../model/stat-model.h"

#define NULL ((void *)0)

void checkXattr(bool *has_xattr, const path_t path) {
	*has_xattr = (listxattr(path, NULL, 0, 0) > 0);
}
