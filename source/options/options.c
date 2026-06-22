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

#define ARG_EXISTS	((i + 1 < argc) && (argv[i + 1][0] == '-'))
#define HAS_ARG		(strcmp(optarg, "") != 0)

#define OPTION_IS(str) (strcmp(opt	 , str) == 0)
#define OPTARG_IS(str) (strcmp(optarg, str) == 0)

#define ERROR_TAKES_ARG(option)	   do { fprintf(stderr, "error: `%s` takes argument\n", option); usage(1); } while (0)
#define ERROR_INVALID_OPT(option)  do { fprintf(stderr, "unknown option: `%s`\n"	  , option); usage(1); } while (0)

#define ERROR_BAD_ARG(option, arg, args)		\
	do {										\
		fprintf(stderr,							\
			"invlid argument `%s` for `%s`. "	\
			"possible arguments are %s\n",		\
			arg, option, args					\
		);										\
		usage(1);								\
	} while (0)

#define ARG_ERROR(option, valid_args) \
	if (HAS_ARG) ERROR_BAD_ARG(option, optarg, valid_args); \
	else ERROR_TAKES_ARG(option)

#define BINARY_OPT(flag, var) \
	if (OPTION_IS("--"	  #flag)) { var = true ; continue; } \
	if (OPTION_IS("--no-" #flag)) { var = false; continue; }

#define FIELD_OPT(flag, var) \
	if (OPTION_IS("--do-" #flag) || OPTION_IS("--" #flag))	{ var = true ; continue; } \
	if (OPTION_IS("--no-" #flag))							{ var = false; continue; }

/* ——————————————————————————————————————————————————————————————————— */

int setOptions(const int argc, const char *argv[]) {
	bool colour_auto = true;

	for (int i = 1; i < argc; i++) {

		const char *opt		= argv[i];
		const char *optarg	= ARG_EXISTS ? "" : argv[i + 1];

		/* —— end option parsing ————————————————————————————————————————— */

		if (OPTION_IS("--") || opt[0] != '-') return i;

		/* —— --colour ——————————————————————————————————————————————————— */

		if (OPTION_IS("--colour")) {
			colour_auto = false;
			if (OPTARG_IS("always")) { i++; I_DO_COLOUR = true ; continue; }
			if (OPTARG_IS("never" )) { i++; I_DO_COLOUR = false; continue; }
			if (OPTARG_IS("auto"  )) { i++; colour_auto = true ; continue; }
			ARG_ERROR("--colour", "always, never, auto");
		}

		if (OPTION_IS("--no-colour")) { I_DO_COLOUR = false; continue; }

		/* —— --flags ———————————————————————————————————————————————————— */

		if (OPTION_IS("--flags") || OPTION_IS("--flag-style")) {
			if (OPTARG_IS("full" )) { i++; I_DO_SHORT_FLAGS = false; I_DO_TINY_FLAGS = false; continue; }
			if (OPTARG_IS("short")) { i++; I_DO_SHORT_FLAGS = true ; I_DO_TINY_FLAGS = false; continue; }
			if (OPTARG_IS("tiny" )) { i++; I_DO_SHORT_FLAGS = false; I_DO_TINY_FLAGS = true ; continue; }
			ARG_ERROR("--flags", "full, short, tiny");
		}

		/* —— binary options ————————————————————————————————————————————— */

		BINARY_OPT(headers			, I_DO_HEADER		);
		BINARY_OPT(dividers			, I_DO_DIVIDERS		);
		BINARY_OPT(dim-hidden		, I_DO_DIM_HIDDEN	);
		BINARY_OPT(sort-dirs-first	, I_SORT_DIRS_FIRST	);

		/* —— field setting/unsetting ——————————————————————————————————— */

		FIELD_OPT(suffix	, I_DO_SUFFIX	);
		FIELD_OPT(link-to	, I_DO_LINK_TO	);

		FIELD_OPT(nlink		, I_DO_NLINK	);
		FIELD_OPT(dev-no	, I_DO_DEV_NO	);
		FIELD_OPT(inode		, I_DO_INODE	);

		FIELD_OPT(flags		, I_DO_FLAGS	);	FIELD_OPT(flag-str, I_DO_FLAG_STR);
		FIELD_OPT(mode		, I_DO_MODE		);	FIELD_OPT(mode-str, I_DO_MODE_STR);
		FIELD_OPT(size		, I_DO_SIZE		);	FIELD_OPT(size-str, I_DO_SIZE_STR);
		FIELD_OPT(uid		, I_DO_UID		);	FIELD_OPT(usr-name, I_DO_USR_NAME);
		FIELD_OPT(gid		, I_DO_GID		);	FIELD_OPT(grp-name, I_DO_GRP_NAME);
		FIELD_OPT(time		, I_DO_TIME		);	FIELD_OPT(time-str, I_DO_TIME_STR);
	}

	/* ——————————————————————————————————————————————————————————————— */

	if (colour_auto) I_DO_COLOUR = setColour();

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
