/// @file options/options.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "options.h"

#ifndef t
#define t 1 /* this doesn't do anything - it's just here to stop a rly annoying bug that my error checker has */
#endif

/* —— Declare Constants & Set Defaults ————————————————————————————————————————————————————————————————————————————— */

static bool
	U_DO_COLOUR, // `U_DO_COLOUR` is the only one that doesn't need a default - it'll be set no matter what
	U_DO_CLEAR			= false	,
	U_DO_HEADER			= false	,
	U_DO_DIVIDERS		= true	,
	U_DO_SHORT_FLAGS	= true	,
	U_DO_TINY_FLAGS		= false	,
	U_DO_DIM_HIDDEN		= true	,
	U_SORT_DIRS_FIRST	= true	;

static bool
	U_DO_SUFFIX		= true	,
	U_DO_LINK_TO	= true	,
	//
	U_DO_NLINK		= true	,
	U_DO_DEV_NO		= false	,
	U_DO_INODE		= false	,
	//
	U_DO_FLAGS		= false	,	U_DO_FLAG_STR = true,
	U_DO_MODE		= false	,	U_DO_MODE_STR = true,
	U_DO_SIZE		= false	,	U_DO_SIZE_STR = true,
	U_DO_UID		= false	,	U_DO_USR_NAME = true,
	U_DO_GID		= false	,	U_DO_GRP_NAME = true,
	U_DO_TIME		= false	,	U_DO_TIME_STR = true;

/* —— Set Colour ——————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool doColourAuto(void) {
	if (!isatty(STDOUT_FILENO)) return false;

	const char *NO_COLOR = getenv("NO_COLOR");
	if (!(NO_COLOR == NULL || strlen(NO_COLOR) == 0)) return false;

	const char *COLORTERM = getenv("COLORTERM");
	if (COLORTERM == NULL || !(
		strcmp(COLORTERM, "truecolor") == 0 ||
		strcmp(COLORTERM, "24bit"	 ) == 0
	)) return false;

	return true;
}

/* —— Set Options —————————————————————————————————————————————————————————————————————————————————————————————————— */

#define ARG_EXISTS	((i + 1 < argc) && (argv[i + 1][0] != '-'))
#define HAS_ARG		(strcmp(optarg, "") != 0)

#define OPTION_IS(str) (strcmp(opt	 , (str)) == 0)
#define OPTARG_IS(str) (strcmp(optarg, (str)) == 0)

#define OPTION_IS_OF(str1, str2) (OPTION_IS((str1)) || OPTION_IS((str2)))

/* ——————————————————————————————————————————————————————————————————— */

#define BINARY_OPT(flag, var) \
	if (OPTION_IS("--"	  #flag)) { (var) = true ; continue; } \
	if (OPTION_IS("--no-" #flag)) { (var) = false; continue; }

#define FIELD_OPT(flag, var) \
	if (OPTION_IS_OF("--" #flag, "--do-" #flag)) { (var) = true ; continue; } \
	if (OPTION_IS("--no-" #flag))				 { (var) = false; continue; }

/* ——————————————————————————————————————————————————————————————————— */

//#define ERROR_TAKES_ARG(option) do { fprintf(stderr, "error: `%s` takes argument\n", (option)); usage(1); } while (0)
#define ERROR_INVALID_OPT(option) do { fprintf(stderr, "unknown option: `%s`\n"		 , (option)); usage(1); } while (0)

#define ERROR_BAD_ARG(args)						\
	do {										\
		fprintf(stderr,							\
			"invalid argument `%s` for `%s`. "	\
			"possible arguments are %s\n",		\
			optarg, opt, (args)					\
		);										\
		usage(1);								\
	} while (0)

/* ——————————————————————————————————————————————————————————————————— */

int setOptions(const int argc, const char *argv[]) {
	bool colour_auto = true;
	int i;

	for (i = 1; i < argc; i++) {

		const char *opt		= argv[i];
		const char *optarg	= ARG_EXISTS ? argv[i + 1] : "";

		/* —— end option parsing ————————————————————————————————————————— */

		if (opt[0] != '-') break;
		if (OPTION_IS("--")) { i++; break; }

		/* —— --colour ——————————————————————————————————————————————————— */

		if (OPTION_IS("--colour") || OPTION_IS("--color")) {
			colour_auto = false;
			if (OPTARG_IS("always")) { U_DO_COLOUR = true ; i++; continue; }
			if (OPTARG_IS("never" )) { U_DO_COLOUR = false; i++; continue; }
			if (OPTARG_IS("auto"  )) { colour_auto = true ; i++; continue; }
			if (HAS_ARG) ERROR_BAD_ARG("always, never, auto");
			// if no argument is given, then, like `ls`, assume `--colour` means `--colour always`
			U_DO_COLOUR = true; continue;
		}

		if (OPTION_IS_OF("--no-colour", "--no-color")) { colour_auto = false, U_DO_COLOUR = false; continue; }

		/* —— --flags ———————————————————————————————————————————————————— */

		if (OPTION_IS("--flags")) {
			if (OPTARG_IS("long" )) { U_DO_SHORT_FLAGS = false, U_DO_TINY_FLAGS = false; i++; continue; }
			if (OPTARG_IS("short")) { U_DO_SHORT_FLAGS = true , U_DO_TINY_FLAGS = false; i++; continue; }
			if (OPTARG_IS("tiny" )) { U_DO_SHORT_FLAGS = false, U_DO_TINY_FLAGS = true ; i++; continue; }
			if (HAS_ARG) ERROR_BAD_ARG("long, short, tiny");
			// if there's no arg, then match the rest of the other field options, and turn the `flags` field on
			U_DO_FLAGS = true; continue;
		}

		/* —— binary options ————————————————————————————————————————————— */

		BINARY_OPT(clear			, U_DO_CLEAR		);
		BINARY_OPT(headers			, U_DO_HEADER		);
		BINARY_OPT(dividers			, U_DO_DIVIDERS		);
		BINARY_OPT(dim-hidden		, U_DO_DIM_HIDDEN	);
		BINARY_OPT(sort-dirs-first	, U_SORT_DIRS_FIRST	);

		/* —— field setting/unsetting ——————————————————————————————————— */

		FIELD_OPT(suffix, U_DO_SUFFIX	);
		FIELD_OPT(link	, U_DO_LINK_TO	);

		FIELD_OPT(nlink	, U_DO_NLINK	);
		FIELD_OPT(dev-no, U_DO_DEV_NO	);
		FIELD_OPT(inode	, U_DO_INODE	);

		FIELD_OPT(flags	, U_DO_FLAGS	);	FIELD_OPT(flag-str, U_DO_FLAG_STR);
		FIELD_OPT(mode	, U_DO_MODE		);	FIELD_OPT(mode-str, U_DO_MODE_STR);
		FIELD_OPT(size	, U_DO_SIZE		);	FIELD_OPT(size-str, U_DO_SIZE_STR);
		FIELD_OPT(uid	, U_DO_UID		);	FIELD_OPT(usr-name, U_DO_USR_NAME);
		FIELD_OPT(gid	, U_DO_GID		);	FIELD_OPT(grp-name, U_DO_GRP_NAME);
		FIELD_OPT(time	, U_DO_TIME		);	FIELD_OPT(time-str, U_DO_TIME_STR);

		/* ——————————————————————————————————————————————————————————————— */

		ERROR_INVALID_OPT(opt);
	}

	/* ——————————————————————————————————————————————————————————————— */

	// if `--colour auto` was given, or if `--colour` wasn't set, then determine whether colour should be used
	if (colour_auto) U_DO_COLOUR = doColourAuto();

	return i;
}

/* —— Define Getter Functions —————————————————————————————————————————————————————————————————————————————————————— */

bool DO_CLEAR		(void) { return U_DO_CLEAR			; }
bool DO_COLOUR		(void) { return U_DO_COLOUR			; }
bool DO_HEADER		(void) { return U_DO_HEADER			; }
bool DO_DIVIDERS	(void) { return U_DO_DIVIDERS		; }
bool DO_SHORT_FLAGS	(void) { return U_DO_SHORT_FLAGS	; }
bool DO_TINY_FLAGS	(void) { return U_DO_TINY_FLAGS		; }
bool DO_DIM_HIDDEN	(void) { return U_DO_DIM_HIDDEN		; }
bool SORT_DIRS_FIRST(void) { return U_SORT_DIRS_FIRST	; }

/* ————————————————————————————————————————————————————————— */

bool do_suffix	(void) { return U_DO_SUFFIX	; }
bool do_link_to	(void) { return U_DO_LINK_TO; }
//
bool do_nlink	(void) { return U_DO_NLINK	; }
bool do_dev_no	(void) { return U_DO_DEV_NO	; }
bool do_inode	(void) { return U_DO_INODE	; }
//
bool do_flags	(void) { return U_DO_FLAGS	; }		bool do_flag_str(void) { return U_DO_FLAG_STR; }
bool do_mode	(void) { return U_DO_MODE	; }		bool do_mode_str(void) { return U_DO_MODE_STR; }
bool do_size	(void) { return U_DO_SIZE	; }		bool do_size_str(void) { return U_DO_SIZE_STR; }
bool do_uid		(void) { return U_DO_UID	; }		bool do_usr_name(void) { return U_DO_USR_NAME; }
bool do_gid		(void) { return U_DO_GID	; }		bool do_grp_name(void) { return U_DO_GRP_NAME; }
bool do_time	(void) { return U_DO_TIME	; }		bool do_time_str(void) { return U_DO_TIME_STR; }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
