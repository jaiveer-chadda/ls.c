/// @file output/print-ugid.c

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include "../model/stat-model.h"
#include "../form/formatting.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_USR_NAME_COLOUR()						\
	usr_uid == *file_uid ? USR_YOU_COL : (			\
		*file_uid == 0 ? USR_ROOT_COL : USR_OTH_COL	\
	)

/* —————————————————————————————————————————————————————————————— */

void printUsrName(const uid_t *file_uid, const ugidstr file_usr_name, const bool *is_valid) {
	if (!do_usr_name) return;

	const int len = (int)field_lengths.usr_name;

	if (!*is_valid) {
		printf("%s" "%-*s" "%s", USR_INV_COL, len, INV_FILE_USRNAME, RESET FIELD_PAD);
		return;
	}

	/// The UID of the user running this process.
	const uid_t usr_uid = getuid();

	char fmt_str[16] = "%s";
	strcat(fmt_str, fmt_strs_long.usr_name);
	strcat(fmt_str, RESET FIELD_PAD);

	printf(fmt_str, GET_USR_NAME_COLOUR(), len, file_usr_name);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_GRP_NAME_COLOUR()						\
	in_usr_grp ? GRP_YOU_COL : (					\
		in_root_grp ? GRP_ROOT_COL : GRP_OTH_COL	\
	)

/* —————————————————————————————————————————————————————————————— */

static inline bool is_user_in_group(
	const ugidstr usr_name, const gid_t usr_main_gid,
	const ugidstr grp_name, const gid_t file_gid
) {
	if (usr_main_gid == file_gid) return true;

	const struct group *grp = getgrnam(grp_name);
	if (grp == NULL) return false;

	for (int i = 0; grp->gr_mem[i] != NULL; i++) {
		if (strcmp(grp->gr_mem[i], usr_name) == 0) return true;
	}
	return false;
}

/* —————————————————————————————————————————————————————————————— */

void printGrpName(const gid_t *file_gid, const ugidstr file_grp_name, const bool *is_valid) {
	if (!do_grp_name) return;

	const int len = (int)field_lengths.grp_name;

	if (!*is_valid) {
		printf("%s" "%-*s" "%s", GRP_INV_COL, len, INV_FILE_GRPNAME, RESET FIELD_PAD);
		return;
	}

	const struct passwd *pw = getpwuid(getuid());

	/// The username of the user running this process.
	const char *usr_name = pw->pw_name;

	const bool 
		in_usr_grp  = is_user_in_group(usr_name, pw->pw_gid, file_grp_name, *file_gid),
		in_root_grp = *file_gid == 0;

	printf("%s" "%-*s" "%s",
		GET_GRP_NAME_COLOUR(),
		len, file_grp_name,
		RESET FIELD_PAD
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
