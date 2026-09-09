/// @file features/ugid/ugid.c

#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

/* ———————————————————————————————————————————————————————— */

/// Just a small wrapper function to be able to cache the uid of the user running this program.
static inline uid_t get_user_uid(void) {
	static long user_uid = -1;

	if (user_uid == -1) user_uid = (long)getuid();
	return (uid_t)user_uid;
}

/* ———————————————————————————————————————————————————————— */

static inline Colour get_usr_colour(const FileStat *const pFS) {
	if (pFS->s->st_uid == get_user_uid()) return USR_YOU_COL;
	if (pFS->s->st_uid == ROOT_USR_UID  ) return USR_ROOT_COL;
	return USR_OTH_COL;
}

static inline Colour get_grp_colour(const FileStat *const pFS) {
	const struct passwd *const pw = getpwuid(get_user_uid());

	const bool in_user_grp = is_user_in_group(pw->pw_name, pw->pw_gid, pFS->f->grp_name, pFS->s->st_gid);
	const bool in_root_grp = pFS->s->st_gid == ROOT_GRP_GID;

	if (in_user_grp) return GRP_YOU_COL;
	if (in_root_grp) return GRP_ROOT_COL;
	return GRP_OTH_COL;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_usr_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->usr_name != NULL;
	if (!valid) {
		printf("%s%*s%ls", getcol(PUNCT), getLen(FI_usr_name), INV_FILE_USRNAME, FIELD_PAD);
		return;
	}

	const Colour col = get_usr_colour(pFS);
	printf("%s" "%-*s" "%ls", getcol(col), getLen(FI_usr_name), pFS->f->usr_name, FIELD_PAD);
}

/* ———————————————————————————————————————————————————————— */

void print_grp_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->grp_name != NULL;
	if (!valid) {
		printf("%s%*s%ls", getcol(PUNCT), getLen(FI_grp_name), INV_FILE_GRPNAME, FIELD_PAD);
		return;
	}

	Colour col = get_grp_colour(pFS);
	printf("%s" "%-*s" "%ls", getcol(col), getLen(FI_grp_name), pFS->f->grp_name, FIELD_PAD);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define get_uid_colour get_usr_colour
#define get_gid_colour get_grp_colour

#define print_ugid(ugid)								\
	void print_##ugid(const FileStat *const pFS) {		\
		const bool valid = pFS->s != NULL;				\
		printf(											\
			valid ? "%s%*d%ls" : "%s%*c%ls",			\
			getcol(get_##ugid##_colour(pFS)),			\
			getLen(FI_##ugid),							\
			valid ? pFS->s->st_##ugid : '-',			\
			FIELD_PAD									\
		);												\
	}

print_ugid(uid)
print_ugid(gid)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
