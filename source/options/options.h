/// @file options/options.h

void initFormatting(void);

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

#include "../model/stat-model.h"

extern const bool
	DO_COLOUR,
	DO_HEADER,
	DO_DIVIDERS,
	DO_SHORT_FLAGS,
	DO_TINY_FLAGS,
	DO_DIM_HIDDEN,
	SORT_DIRS_FIRST;

extern const bool
	do_suffix,
	do_link_to,

	do_nlink,
	do_dev_no,
	do_inode,

	do_flags,	do_flag_str,
	do_mode,	do_mode_str,
	do_size,	do_size_str,
	do_uid,		do_usr_name,
	do_gid,		do_grp_name,
	do_time,	do_time_str;

#endif /* !OPTIONS_INITIALIASED */
