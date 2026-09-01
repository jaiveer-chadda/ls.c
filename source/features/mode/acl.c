/// @file features/mode/acl.c

#include <sys/acl.h>
#include "mode.h"

bool checkACL(const path_t path) {
	acl_t const p_acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	acl_free(p_acl);

	return p_acl != NULL;
}
