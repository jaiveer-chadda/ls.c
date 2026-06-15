/// @file options/set-options.c

#include <string.h>

#include "options.h"

const bool DO_HEADER		= true;
const bool DO_SHORT_FLAGS	= true;

const bool
	do_name		= true,
	do_suffix	= true,
	do_link_to	= true,

	do_nlink	= true,
	do_dev_no	= false,
	do_inode	= false,

	do_flags	= false,	do_flag_str	= true,
	do_mode		= false,	do_mode_str	= true,
	do_size		= false,	do_size_str	= true,
	do_uid		= false,	do_usr_name	= true,
	do_gid		= false,	do_grp_name	= true,
	do_time		= false,	do_time_str	= true;

Lengths field_lengths;
FmtStrs fmt_strs_short, fmt_strs_long;

void initLengths(void) {
	if (DO_HEADER) {
		// these will be precomputed when compiler optimisation is set to `-O2` or `-O3`
		field_lengths = (Lengths){
			.nlink	= strlen(nlink_TITLE),
			.dev_no	= strlen(dev_no_TITLE),	.inode	  =	strlen(inode_TITLE),

			.mode	= 6,					.mode_str =	11,
			.flags	= strlen(flags_TITLE),	.flag_str =	strlen(flag_str_TITLE),
			.size	= strlen(size_TITLE),	.size_str =	strlen(size_str_TITLE),
			.uid	= strlen(uid_TITLE),	.usr_name =	strlen(usr_name_TITLE),
			.gid	= strlen(gid_TITLE),	.grp_name =	strlen(grp_name_TITLE),
			.time	= strlen(time_TITLE),	.time_str =	strlen(time_str_TITLE),
		};
	}

	fmt_strs_short = (FmtStrs){
		.name	= "%s",
		.suffix	= "%c",
		.link_to= "%s",

		.nlink	= "%d"	,
		.dev_no	= "%d"	, .inode	= "%llu",

		.flags	= "%u"	, .flag_str	= "%s",
		.mode	= "%u"	, .mode_str	= "%s",
		.size	= "%lld", .size_str	= "%s",
		.uid	= "%d"	, .usr_name	= "%s",
		.gid	= "%d"	, .grp_name	= "%s",
		.time	= "%ld"	, .time_str	= "%s",
	};

	fmt_strs_long = (FmtStrs){
		.name	= "%s",
		.suffix	= "%c",
		.link_to= "%s",

		.nlink	= "%-*d"	,
		.dev_no	= "%*d"		, .inode	= "%*llu",

		.flags	= "%-*u"	, .flag_str	= "%-*s",
		.mode	= "%-*u"	, .mode_str	= "%-*s",
		.size	= "%*lld"	, .size_str	= "%*s",
		.uid	= "%-*d"	, .usr_name	= "%-*s",
		.gid	= "%-*d"	, .grp_name	= "%-*s",
		.time	= "%*ld"	, .time_str	= "%*s",
	};
}
