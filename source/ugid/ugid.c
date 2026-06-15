/// @file ugid/ugid.c

#include <string.h>
#include <pwd.h>
#include <grp.h>

void getUser(char *usr_str, uid_t uid) {
	struct passwd *pw = getpwuid(uid);
	if (pw == NULL) { strcpy(usr_str, "-"); return; }

	strcpy(usr_str, pw->pw_name);
}

void getGroup(char *grp_str, gid_t gid) {
	struct group *grp = getgrgid(gid);
	if (grp == NULL) { strcpy(grp_str, "-"); return; }

	strcpy(grp_str, grp->gr_name);
}
