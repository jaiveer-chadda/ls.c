/// @file features/mode/acl.c

#include <sys/acl.h>
#include "mode.h"

void checkACL(bool *has_acl_perms, const path_t path) {
	const acl_t p_acl = acl_get_link_np(path, ACL_TYPE_EXTENDED); // NOLINT(*-misplaced-const)
	*has_acl_perms = (p_acl != NULL);

	acl_free(p_acl);
}
