/// @file features/mode/xattr.c

#include <sys/xattr.h>
#include "mode.h"

void checkXattr(bool *has_xattr, const path_t path) {
	*has_xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0;
}
