/// @file options/set-options.c

#include <string.h>
#include "options.h"

const bool
	DO_COLOUR		= true,
	DO_HEADER		= false,
	DO_DIVIDERS		= true,
	DO_SHORT_FLAGS	= true,
	DO_TINY_FLAGS	= false,
	DO_DIM_HIDDEN	= true,
	SORT_DIRS_FIRST	= true;

const bool
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
