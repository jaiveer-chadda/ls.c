/// @file form/init-formatting.c

#include <string.h>

#include "formatting.h"
#include "../options/options.h"

Lengths field_lengths;
FmtStrs fmt_strs_short, fmt_strs_long;

inline void initFormatting(void) {
	if (DO_HEADER()) {
		// these will be precomputed when compiler optimisation is set to `-O2` or `-O3`
		field_lengths = (Lengths){
			.nlink	= strlen(nlink_TITLE),
			.dev_no	= strlen(dev_no_TITLE),	.inode	  =	strlen(inode_TITLE),

			// `mode` and `mode_str` have constant sizes
			.mode	= OCT_MODE_LEN,			.mode_str =	MODE_STR_LEN - 1,
			.flags	= strlen(flags_TITLE),	.flag_str =	strlen(flag_str_TITLE),
			.size	= strlen(size_TITLE),	.size_str =	strlen(size_str_TITLE),
			.uid	= strlen(uid_TITLE),	.usr_name =	strlen(usr_name_TITLE),
			.gid	= strlen(gid_TITLE),	.grp_name =	strlen(grp_name_TITLE),
			.time	= strlen(time_TITLE),	.time_str =	strlen(time_str_TITLE),
		};
	}

	fmt_strs_short = (FmtStrs){
		.nlink	= "%d"	,
		.dev_no	= "%d"	, .inode	= "%llu",

		.flags	= "%x"	, .flag_str	= "%s",
		.mode	= "%o"	, .mode_str	= "%s",
		.size	= "%lld", .size_str	= "%s",
		.uid	= "%d"	, .usr_name	= "%s",
		.gid	= "%d"	, .grp_name	= "%s",
		.time	= "%ld"	, .time_str	= "%s",
	};

	fmt_strs_long = (FmtStrs){
		.nlink	= "%*d"		,
		.dev_no	= "%*d"		, .inode	= "%*llu",

		.flags	= "%*x"		, .flag_str	= "%-*s",
		.mode	= "%0*o"	, .mode_str	= "%-*s",
		.size	= "%*zd"	, .size_str	= "%*s",
		.uid	= "%*d"		, .usr_name	= "%-*s",
		.gid	= "%*d"		, .grp_name	= "%-*s",
		.time	= "%*ld"	, .time_str	= "%*s",
	};
}
