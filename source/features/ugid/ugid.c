/// @file features/ugid/ugid.c

#include <pwd.h>
#include <grp.h>
#include <string.h>

#include "malloc.h"
#include "model/types.h"

char *getUser(const uid_t uid) {
	const struct passwd *pw = getpwuid(uid);
	if (pw == NULL) return (char*)NULL;

	const size_t strsize = strlen(pw->pw_name) + 1;
	setLen(FI_usr_name, strsize);

	return memcpy(malloc(strsize), pw->pw_name, strsize);
}

char *getGroup(const gid_t gid) {
	const struct group *grp = getgrgid(gid);
	if (grp == NULL) return (char*)NULL;

	const size_t strsize = strlen(grp->gr_name) + 1;
	setLen(FI_grp_name, strsize);

	return memcpy(emalloc(strsize), grp->gr_name, strsize);
}
