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

/// Just a small wrapper function which caches the uid of the user running this program.
uid_t get_user_uid(void) {
	static uid_t user_uid;
	static bool did_init = false;

	if (!did_init) {
		user_uid = getuid();
		did_init = true;
	}
	return user_uid;
}

/* ——————————————————————————————————————————————————————————————— */

const struct passwd *get_user_pw(void) {
	// note: if `getpwuid` fails, each subsequent call will try again
	static const struct passwd *user_pw = NULL;
	return user_pw ? user_pw : ( user_pw = getpwuid(get_user_uid()) );
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *getUser(const uid_t uid, const bool do_set_len) {
	const struct passwd *pw = getpwuid(uid);
	if (pw == NULL) return (char*)NULL;

	const size_t strsize = strlen(pw->pw_name) + 1;
	if (do_set_len) setLen(FI_usr_name, strsize - 1);

	return memcpy(emalloc(strsize), pw->pw_name, strsize);	/* [alloc:username] - freed in `print_ug_name` */
	/**/													/* [alloc:mount-username] - freed in `print_mount` */
}

char *getGroup(const gid_t gid) {
	const struct group *grp = getgrgid(gid);
	if (grp == NULL) return (char*)NULL;

	const size_t strsize = strlen(grp->gr_name) + 1;
	setLen(FI_grp_name, strsize - 1);

	return memcpy(emalloc(strsize), grp->gr_name, strsize); /* [alloc:groupname] - freed in `print_ug_name` */
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define ROOT_GRP_GID ((gid_t)0)
#define ROOT_USR_UID ((uid_t)0)

/// @todo add a caching system for each of the users / groups
///		cos if we know a user is in a group, we don't need to check again

// the `getgrnam` function ends up misaligning the memory, which throws a runtime warning,
//	but it shouldn't be an issue on macOS
__attribute__((no_sanitize("alignment")))
static inline bool is_user_in_group(
	const ugidstr usr_name, const gid_t usr_main_gid,
	const ugidstr grp_name, const gid_t file_gid
) {
	if (usr_main_gid == file_gid) return true;

	const struct group *const grp = getgrnam(grp_name);
	if (grp == NULL) return false;

	for (int i = 0; grp->gr_mem[i] != NULL; i++) {
		if (strcmp(grp->gr_mem[i], usr_name) == 0) return true;
	}
	return false;
}

/* ———————————————————————————————————————————————————————— */

#define get_uid_colour get_usr_colour
Colour get_usr_colour(const uid_t uid) {
	if (uid == ROOT_USR_UID  ) return USR_ROOT_COL;
	if (uid == get_user_uid()) return USR_YOU_COL ;
	return USR_OTH_COL;
}

#define get_gid_colour get_grp_colour
static inline Colour get_grp_colour(const FileStat *const pFS) {
	if (pFS->s == NULL) return PUNCT;

	const struct passwd *const pw = get_user_pw();

	const bool in_root_grp = pFS->s->st_gid == ROOT_GRP_GID;
	const bool in_user_grp = is_user_in_group(
		pw->pw_name		, pw->pw_gid,
		pFS->f->grp_name, pFS->s->st_gid
	);

	// note: if running as the root user, the program will consider `root` to be _you_
	if (in_user_grp) return GRP_YOU_COL	;
	if (in_root_grp) return GRP_ROOT_COL;
	/**/			 return GRP_OTH_COL	;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define print_ug_name(usgr, col_arg)										\
	void print_##usgr##_name(const FileStat *const pFS) {					\
		const bool valid = pFS->f != NULL && pFS->f->usgr##_name != NULL;	\
		printf("%s%-*s%ls",													\
			getcol(pFS->s == NULL ? PUNCT : get_##usgr##_colour(col_arg)),	\
			getLen(FI_##usgr##_name),										\
			valid ? pFS->f->usgr##_name : "-",								\
			FIELD_PAD														\
		);																	\
		if (valid) efree((void*)pFS->f->usgr##_name);						\
	}

/* ———————————————————————————————————————————————————————— */

#define print_ugid(ugid, col_arg)						\
	void print_##ugid(const FileStat *const pFS) {		\
		const bool valid = pFS->s != NULL;				\
		printf(											\
			valid ? "%s%*d%ls" : "%s%*c%ls",			\
			getcol(pFS->s == NULL ? PUNCT :				\
				get_##ugid##_colour(col_arg)),			\
			getLen(FI_##ugid),							\
			valid ? pFS->s->st_##ugid : '-',			\
			FIELD_PAD									\
		);												\
	}

/* ———————————————————————————————————————————————————————— */

print_ug_name(usr, pFS->s->st_uid)
print_ug_name(grp, pFS)

print_ugid(uid, pFS->s->st_uid)
print_ugid(gid, pFS)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore usgr
