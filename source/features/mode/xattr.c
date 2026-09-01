/// @file features/mode/xattr.c

#include <sys/xattr.h>
#include "mode.h"

bool checkXattr(const path_t path) {
	return listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0;
}
