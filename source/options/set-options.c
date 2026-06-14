/// @file options/set-options.c

#include <string.h>

#include "options.h"

const bool DO_HEADER		= true;
const bool DO_SHORT_FLAGS	= true;

const bool
	do_name		= true,
	do_suffix	= true,

	do_nlink	= true,
	do_dev_no	= false,
	do_inode	= false,

	do_flags	= false,	do_flag_str	= true,
	do_mode		= false,	do_mode_str	= true,
	do_size		= true,		do_size_str	= false,
	do_uid		= false,	do_usr_name	= true,
	do_gid		= false,	do_grp_name	= true,
	do_time		= false,	do_time_str	= true;

Lengths field_lengths;

void initLengths(void) {
	if (DO_HEADER) {
		// these will be precomputed when compiler optimisation is set to `-O2` or `-O3`
		field_lengths = (Lengths){
			.name	= strlen(NAME_TITLE),

			.nlink	= strlen(NLINK_TITLE),
			.dev_no	= strlen(DEV_NO_TITLE),	.inode	  =	strlen(INODE_TITLE),

			.flags	= strlen(FLAGS_TITLE),	.flag_str =	strlen(FLAG_STR_TITLE),
			.mode	= strlen(MODE_TITLE),	.mode_str =	strlen(MODE_STR_TITLE),
			.size	= strlen(SIZE_TITLE),	.size_str =	strlen(SIZE_STR_TITLE),
			.uid	= strlen(UID_TITLE),	.usr_name =	strlen(USR_NAME_TITLE),
			.gid	= strlen(GID_TITLE),	.grp_name =	strlen(GRP_NAME_TITLE),
			.time	= strlen(TIME_TITLE),	.time_str =	strlen(TIME_STR_TITLE),
		};
	}
}
