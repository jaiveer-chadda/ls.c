/// @file options/options.c

#include <stdio.h>
#include <string.h>
#include "options.h"

/* —— Declare Constants ———————————————————————————————————————————————————————————————————————————————————————————— */

static bool
	I_DO_COLOUR,
	I_DO_HEADER			= false	,
	I_DO_DIVIDERS		= true	,
	I_DO_SHORT_FLAGS	= true	,
	I_DO_TINY_FLAGS		= false	,
	I_DO_DIM_HIDDEN		= true	,
	I_SORT_DIRS_FIRST	= true	;

static bool
	I_DO_SUFFIX		= true	,
	I_DO_LINK_TO	= true	,
	//
	I_DO_NLINK		= true	,
	I_DO_DEV_NO		= false	,
	I_DO_INODE		= false	,
	//
	I_DO_FLAGS		= false	,	I_DO_FLAG_STR = true,
	I_DO_MODE		= false	,	I_DO_MODE_STR = true,
	I_DO_SIZE		= false	,	I_DO_SIZE_STR = true,
	I_DO_UID		= false	,	I_DO_USR_NAME = true,
	I_DO_GID		= false	,	I_DO_GRP_NAME = true,
	I_DO_TIME		= false	,	I_DO_TIME_STR = true;

/* —— Set Constants ———————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool setColour(void) {
	return true;
}

/* ——————————————————————————————————————————————————————————————————— */

#define OPTION(str) (strcmp(argv[i	  ], str) == 0)
#define OPTARG(str) (strcmp(argv[i + 1], str) == 0)

#define ERROR_TAKES_ARG(option)	do { fprintf(stderr, "error: `%s` takes argument\n"	, option); usage(1); } while (0)
#define ERROR_INVALID(option)	do { fprintf(stderr, "unknown option: `%s`\n"		, option); usage(1); } while (0)

int setOptions(const int argc, const char *argv[]) {
	// if (argc < 2) return 0;
	bool colour_auto = true;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') return i;
		// puts(argv[i]);

		if (OPTION("--colour")) {
			colour_auto = false;
			if		(OPTARG("always")) { i++; I_DO_COLOUR = true ;}
			else if (OPTARG("never" )) { i++; I_DO_COLOUR = false;}
			else if (OPTARG("auto"  )) { i++; colour_auto = true ;}
			else ERROR_TAKES_ARG("--colour");

			continue;
		}
	}

	if (colour_auto) I_DO_COLOUR = setColour();

	I_DO_HEADER			= false	;
	I_DO_DIVIDERS		= true	;
	I_DO_SHORT_FLAGS	= true	;
	I_DO_TINY_FLAGS		= false	;
	I_DO_DIM_HIDDEN		= true	;
	I_SORT_DIRS_FIRST	= true	;

	/* ————————————————————————————————————————————————— */

	I_DO_SUFFIX		= true	;
	I_DO_LINK_TO	= true	;

	I_DO_NLINK		= true	;
	I_DO_DEV_NO		= false	;
	I_DO_INODE		= false	;

	I_DO_FLAGS		= false	;	I_DO_FLAG_STR = true;
	I_DO_MODE		= false	;	I_DO_MODE_STR = true;
	I_DO_SIZE		= false	;	I_DO_SIZE_STR = true;
	I_DO_UID		= false	;	I_DO_USR_NAME = true;
	I_DO_GID		= false	;	I_DO_GRP_NAME = true;
	I_DO_TIME		= false	;	I_DO_TIME_STR = true;

	return 0;
}

/* —— Define Getter Functions —————————————————————————————————————————————————————————————————————————————————————— */

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
//
bool do_nlink	(void) { return I_DO_NLINK	; }
bool do_dev_no	(void) { return I_DO_DEV_NO	; }
bool do_inode	(void) { return I_DO_INODE	; }
//
bool do_flags	(void) { return I_DO_FLAGS	; }		bool do_flag_str(void) { return I_DO_FLAG_STR; }
bool do_mode	(void) { return I_DO_MODE	; }		bool do_mode_str(void) { return I_DO_MODE_STR; }
bool do_size	(void) { return I_DO_SIZE	; }		bool do_size_str(void) { return I_DO_SIZE_STR; }
bool do_uid		(void) { return I_DO_UID	; }		bool do_usr_name(void) { return I_DO_USR_NAME; }
bool do_gid		(void) { return I_DO_GID	; }		bool do_grp_name(void) { return I_DO_GRP_NAME; }
bool do_time	(void) { return I_DO_TIME	; }		bool do_time_str(void) { return I_DO_TIME_STR; }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
