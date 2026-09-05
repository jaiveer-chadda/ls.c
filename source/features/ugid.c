/// @file features/ugid/ugid.c

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "model/types.h"
#include "form/formatting.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *getUser(const uid_t uid) {
	const struct passwd *pw = getpwuid(uid);
	if (pw == NULL) return (char*)NULL;

	const size_t strsize = strlen(pw->pw_name) + 1;
	setLen(FI_usr_name, strsize - 1);

	return memcpy(malloc(strsize), pw->pw_name, strsize);
}

char *getGroup(const gid_t gid) {
	const struct group *grp = getgrgid(gid);
	if (grp == NULL) return (char*)NULL;

	const size_t strsize = strlen(grp->gr_name) + 1;
	setLen(FI_grp_name, strsize - 1);

	return memcpy(emalloc(strsize), grp->gr_name, strsize);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_usr_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->usr_name != NULL;
	printf(fields[FI_usr_name].fmt_p, getLen(FI_usr_name), valid ? pFS->f->usr_name : INV_FILE_USRNAME, FIELD_PAD);
}

void print_grp_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->grp_name != NULL;
	printf(fields[FI_grp_name].fmt_p, getLen(FI_grp_name), valid ? pFS->f->grp_name : INV_FILE_GRPNAME, FIELD_PAD);
}

/* ———————————————————————————————————————————————————————— */

#define print_ugid(ugid)								\
	void print_##ugid(const FileStat *const pFS) {		\
		const bool valid = pFS->s != NULL;				\
		printf(											\
			valid ? fields[FI_##ugid].fmt_p : "%*c%s",	\
			getLen(FI_##ugid),							\
			valid ? pFS->s->st_##ugid : '?',			\
			FIELD_PAD									\
		);												\
	}

print_ugid(uid)
print_ugid(gid)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
