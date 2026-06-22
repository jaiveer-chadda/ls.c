/// @file options/options.c

#include <string.h>
#include "options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static bool
	I_DO_COLOUR,
	I_DO_HEADER,
	I_DO_DIVIDERS,
	I_DO_SHORT_FLAGS,
	I_DO_TINY_FLAGS,
	I_DO_DIM_HIDDEN,
	I_SORT_DIRS_FIRST;

static bool
	I_DO_SUFFIX	,
	I_DO_LINK_TO,

	I_DO_NLINK	,
	I_DO_DEV_NO	,
	I_DO_INODE	,

	I_DO_FLAGS	,	I_DO_FLAG_STR	,
	I_DO_MODE	,	I_DO_MODE_STR	,
	I_DO_SIZE	,	I_DO_SIZE_STR	,
	I_DO_UID	,	I_DO_USR_NAME	,
	I_DO_GID	,	I_DO_GRP_NAME	,
	I_DO_TIME	,	I_DO_TIME_STR	;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool DO_COLOUR		(void) { return I_DO_COLOUR			; }
bool DO_HEADER		(void) { return I_DO_HEADER			; }
bool DO_DIVIDERS	(void) { return I_DO_DIVIDERS		; }
bool DO_SHORT_FLAGS	(void) { return I_DO_SHORT_FLAGS	; }
bool DO_TINY_FLAGS	(void) { return I_DO_TINY_FLAGS		; }
bool DO_DIM_HIDDEN	(void) { return I_DO_DIM_HIDDEN		; }
bool SORT_DIRS_FIRST(void) { return I_SORT_DIRS_FIRST	; }

/* ————————————————————————————————————————————————————————— */

bool do_suffix	(void) { return I_DO_SUFFIX	; }
bool do_link_to	(void) { return I_DO_LINK_TO; }

bool do_nlink	(void) { return I_DO_NLINK	; }
bool do_dev_no	(void) { return I_DO_DEV_NO	; }
bool do_inode	(void) { return I_DO_INODE	; }

bool do_flags	(void) { return I_DO_FLAGS	; }		bool do_flag_str(void) { return I_DO_FLAG_STR	; }
bool do_mode	(void) { return I_DO_MODE	; }		bool do_mode_str(void) { return I_DO_MODE_STR	; }
bool do_size	(void) { return I_DO_SIZE	; }		bool do_size_str(void) { return I_DO_SIZE_STR	; }
bool do_uid		(void) { return I_DO_UID	; }		bool do_usr_name(void) { return I_DO_USR_NAME	; }
bool do_gid		(void) { return I_DO_GID	; }		bool do_grp_name(void) { return I_DO_GRP_NAME	; }
bool do_time	(void) { return I_DO_TIME	; }		bool do_time_str(void) { return I_DO_TIME_STR	; }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void set_options(void) {

	I_DO_COLOUR			= true;
	I_DO_HEADER			= false;
	I_DO_DIVIDERS		= true;
	I_DO_SHORT_FLAGS	= true;
	I_DO_TINY_FLAGS		= false;
	I_DO_DIM_HIDDEN		= true;
	I_SORT_DIRS_FIRST	= true;

	/* ————————————————————————————————————————————————— */

	I_DO_SUFFIX		= true;
	I_DO_LINK_TO	= true;

	I_DO_NLINK		= true;
	I_DO_DEV_NO		= false;
	I_DO_INODE		= false;

	I_DO_FLAGS		= false;	I_DO_FLAG_STR = true;
	I_DO_MODE		= false;	I_DO_MODE_STR = true;
	I_DO_SIZE		= false;	I_DO_SIZE_STR = true;
	I_DO_UID		= false;	I_DO_USR_NAME = true;
	I_DO_GID		= false;	I_DO_GRP_NAME = true;
	I_DO_TIME		= false;	I_DO_TIME_STR = true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
