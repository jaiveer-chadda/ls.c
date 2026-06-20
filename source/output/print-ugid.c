/// @file output/print-ugid.c

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include "../model/stat-model.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_USR_NAME_COLOUR() \
	usr_uid == *file_uid ? USR_YOU_COL : ( \
		strcmp(file_usr_name, "root") == 0 ? USR_ROOT_COL : USR_OTH_COL \
	)

void printUsrName(const uid_t *file_uid, const ugidstr file_usr_name) {
	if (!do_usr_name) return;

	/// The UID of the user running this process.
	const uid_t usr_uid = getuid();
	const int len = (int)field_lengths.usr_name;

	char fmt_str[16] = "%s";
	strcat(fmt_str, fmt_strs_long.usr_name);
	strcat(fmt_str, RESET FIELD_PAD);

	printf(fmt_str, GET_USR_NAME_COLOUR(), len, file_usr_name);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_GRP_NAME_COLOUR() \
	in_usr_grp ? GRP_YOU_COL : ( \
		in_root_grp ? GRP_ROOT_COL : GRP_OTH_COL \
	)

bool is_user_in_group(const ugidstr usr_name, const gid_t main_usr_gid, const ugidstr grp_name, const gid_t file_gid) {
	if (main_usr_gid == file_gid) return 1;

	struct group *grp = getgrnam(grp_name);
	if (grp == NULL) return 0;

	for (int i = 0; grp->gr_mem[i] != NULL; i++) {
		if (strcmp(grp->gr_mem[i], usr_name) == 0) return 1;
	}
	return 0;
}

void printGrpName(const gid_t *file_gid, const ugidstr file_grp_name) {
	if (!do_grp_name) { printf("%u", *file_gid); return; }

	const int len = (int)field_lengths.grp_name;
	const struct passwd *pw = getpwuid(getuid());

	/// The username of the user running this process.
	ugidstr usr_name;
	strcpy(usr_name, pw->pw_name);

	const bool in_usr_grp  = is_user_in_group(usr_name, pw->pw_gid, file_grp_name, *file_gid);
	const bool in_root_grp = strcmp(file_grp_name, "wheel") == 0;
	// const bool in_root_grp = is_user_in_group("root",   pw->pw_gid, file_grp_name, *file_gid);

	printf("%s%-*s" RESET FIELD_PAD,
		GET_GRP_NAME_COLOUR(),
		len, file_grp_name
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
