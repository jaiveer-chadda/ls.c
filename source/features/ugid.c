/// @file features/ugid/ugid.c

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "malloc.h"
#include "model/types.h"
#include "form/formatting.h"

static long user_uid = -1;

/// Just a small wrapper function to be able to cache the uid of the user running this program.
static inline uid_t get_user_uid(void) {
	if (user_uid != -1) return (uid_t)user_uid;
	return (uid_t)( user_uid = (long)getuid() );
}

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

#define ROOT_GRP_GID ((uid_t)0)
#define ROOT_USR_UID ((uid_t)0)

__attribute__((no_sanitize("alignment")))
static inline bool is_user_in_group(
	const ugidstr usr_name, const gid_t usr_main_gid,
	const ugidstr grp_name, const gid_t file_gid
) {
	if (usr_main_gid == file_gid) return true;

	// the `getgrnam` function ends up misaligning the memory. this throws a runtime warning,
	//	but it shouldn't be an issue on macOS
	const struct group *const grp = getgrnam(grp_name);
	if (grp == NULL) return false;

	for (int i = 0; grp->gr_mem[i] != NULL; i++) {
		if (strcmp(grp->gr_mem[i], usr_name) == 0) return true;
	}
	return false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_usr_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->usr_name != NULL;
	if (!valid) {
		printf("%s%*s%ls", getcol(PUNCT), getLen(FI_usr_name), INV_FILE_USRNAME, FIELD_PAD);
		return;
	}

	const uid_t file_uid = pFS->s->st_uid;
	Colour col = USR_OTH_COL;

	if		(file_uid == get_user_uid()) col = USR_YOU_COL;
	else if	(file_uid == ROOT_USR_UID  ) col = USR_ROOT_COL;

	printf("%s" "%-*s" "%ls", getcol(col), getLen(FI_usr_name), pFS->f->usr_name, FIELD_PAD);
}

/* ———————————————————————————————————————————————————————— */

void print_grp_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->grp_name != NULL;
	if (!valid) {
		printf("%s%*s%ls", getcol(PUNCT), getLen(FI_grp_name), INV_FILE_GRPNAME, FIELD_PAD);
		return;
	}

	const struct passwd *const pw = getpwuid(get_user_uid());

	/// The username of the user running this process.
	const char *const usr_name = pw->pw_name;
	const bool in_user_grp = is_user_in_group(usr_name, pw->pw_gid, pFS->f->grp_name, pFS->s->st_gid);
	const bool in_root_grp = pFS->s->st_gid == ROOT_GRP_GID;

	Colour col = GRP_OTH_COL;

	if		(in_user_grp) col = GRP_YOU_COL;
	else if	(in_root_grp) col = GRP_ROOT_COL;

	printf("%s" "%-*s" "%ls", getcol(col), getLen(FI_grp_name), pFS->f->grp_name, FIELD_PAD);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define print_ugid(ugid)								\
	void print_##ugid(const FileStat *const pFS) {		\
		const bool valid = pFS->s != NULL;				\
		printf(											\
			valid ? fields[FI_##ugid].fmt_p : "%*c%ls",	\
			getLen(FI_##ugid),							\
			valid ? pFS->s->st_##ugid : '-',			\
			FIELD_PAD									\
		);												\
	}

print_ugid(uid)
print_ugid(gid)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
