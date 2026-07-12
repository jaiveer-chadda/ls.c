/// @file options/options.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "options.h"

#ifndef t
#define t 1 /* this doesn't do anything - it's just here to stop a rly annoying bug that my error checker has */
#define f 0
#endif

/* —— Declare Constants & Set Defaults ————————————————————————————————————————————————————————————————————————————— */

static SortByField U_SORT_BY  = SB_DEFAULT;
static bool U_DO_REVERSE_SORT = false;


static bool
	U_DO_COLOUR, // `U_DO_COLOUR` is the only one that doesn't need a default - it'll be set no matter what
	U_DO_CLEAR			= false	,
	U_DO_HEADER			= false	,
	U_DO_DIVIDERS		= true	,
	U_DO_MOUNT_DEV		= true	,
	U_DO_DIM_HIDDEN		= true	,
	U_DO_TINY_FLAGS		= false	,
	U_DO_SHORT_FLAGS	= true	,
	U_SORT_DIRS_FIRST	= true	;

static bool
	U_DO_SUFFIX		= true	,
	U_DO_LINK_TO	= true	,

	U_DO_NLINK		= true	,
	U_DO_DEV_NO		= false	,
	U_DO_INODE		= false	,

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

#define   ERROR_TAKES_ARG() do { fprintf(stderr, ERROR "`%s` takes argument\n" , opt); usage(EXIT_FAILURE); } while (0)
#define ERROR_INVALID_OPT() do { fprintf(stderr, ERROR "unknown option: `%s`\n", opt); usage(EXIT_FAILURE); } while (0)

#define ERROR_BAD_ARG(args)						\
	do {										\
		fprintf(stderr, ERROR					\
			"invalid argument `%s` for `%s`. "	\
			"possible arguments are: %s\n",		\
			optarg, opt, (args)					\
		);										\
		usage(1);								\
	} while (0)

/* ——————————————————————————————————————————————————————————————————— */

static inline void allOptsOn(void) {
	U_DO_HEADER			= true	,
	U_DO_DIVIDERS		= true	,
	U_DO_MOUNT_DEV		= true	,
	U_DO_DIM_HIDDEN		= true	,
	U_DO_TINY_FLAGS		= false	,
	U_DO_SHORT_FLAGS	= false	,
	U_SORT_DIRS_FIRST	= true	;
}

static inline void allFieldsOn(void) {
	U_DO_SUFFIX		= true,
	U_DO_LINK_TO	= true,

	U_DO_NLINK		= true,
	U_DO_DEV_NO		= true,
	U_DO_INODE		= true,

	U_DO_FLAGS		= true, U_DO_FLAG_STR = true,
	U_DO_MODE		= true, U_DO_MODE_STR = true,
	U_DO_SIZE		= true, U_DO_SIZE_STR = true,
	U_DO_UID		= true, U_DO_USR_NAME = true,
	U_DO_GID		= true, U_DO_GRP_NAME = true,
	U_DO_TIME		= true, U_DO_TIME_STR = true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int setOptions(const int argc, const char *argv[]) {
	if (strcmp(argv[0], "c" PROGRAM_NAME) == 0) U_DO_CLEAR = true;

	bool colour_auto = true;

	int i;
	for (i = 1; i < argc; i++) {

		const char *opt		= argv[i];
		const char *optarg	= ARG_EXISTS ? argv[i + 1] : "";

		/* —— End Option Parsing ————————————————————————————————————————— */

		if (opt[0] != '-') break;
		if (OPTION_IS("--")) { i++; break; }

		/* —— --help ————————————————————————————————————————————————————— */

		if (OPTION_IS_OF("--help", "-h")) usage(EXIT_SUCCESS);

		/* —— --sort-by —————————————————————————————————————————————————— */

		if (OPTION_IS("--reverse")) { U_DO_REVERSE_SORT = !U_DO_REVERSE_SORT; continue; }

		if (OPTION_IS_OF("--sort", "--sort-by") || OPTION_IS("--rsort")) {
			if (OPTION_IS("--rsort")) U_DO_REVERSE_SORT = !U_DO_REVERSE_SORT;

			if		(OPTARG_IS("none" )) U_SORT_BY = SB_NONE  ;
			else if	(OPTARG_IS("name" )) U_SORT_BY = SB_NAME  ;
			else if	(OPTARG_IS("size" )) U_SORT_BY = SB_SIZE  ;
			else if	(OPTARG_IS("time" )) U_SORT_BY = SB_TIME  ;
			else if	(OPTARG_IS("inode")) U_SORT_BY = SB_INODE ;
			else if	(OPTARG_IS("devno")) U_SORT_BY = SB_DEVNO ;
			else if	(OPTARG_IS("uid"  )) U_SORT_BY = SB_UID	  ;
			else if	(OPTARG_IS("gid"  )) U_SORT_BY = SB_GID	  ;
			else if	(OPTARG_IS("links")) U_SORT_BY = SB_NLINK ;
			else if	(OPTARG_IS("flags")) U_SORT_BY = SB_FLAGS ;
			else if	(OPTARG_IS("mode" )) U_SORT_BY = SB_MODE  ;

			else if	(HAS_ARG) ERROR_BAD_ARG(
				"\n - name (default)"     "\n - size"  "\n - time"
				"\n - uid"   "\n - gid"   "\n - inode" "\n - devno"
				"\n - links" "\n - flags" "\n - mode"  "\n - none"
			);
			else ERROR_TAKES_ARG();

			i++;
			continue;
		}

		/* —— --colour ——————————————————————————————————————————————————— */

		if (OPTION_IS_OF("--colour", "--color")) {
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

		/* —— Binary Options ————————————————————————————————————————————— */

		BINARY_OPT(clear			, U_DO_CLEAR		);
		BINARY_OPT(headers			, U_DO_HEADER		);
		BINARY_OPT(dividers			, U_DO_DIVIDERS		);
		BINARY_OPT(mount-dev		, U_DO_MOUNT_DEV	);
		BINARY_OPT(dim-hidden		, U_DO_DIM_HIDDEN	);
		BINARY_OPT(sort-dirs-first	, U_SORT_DIRS_FIRST	);

		/* —— Field Setting/Unsetting ——————————————————————————————————— */

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

		/* —— All Fields ————————————————————————————————————————————————— */

		if (OPTION_IS("--all-fields"))	{ allFieldsOn();			  continue; }
		if (OPTION_IS("--all"))			{ allFieldsOn(); allOptsOn(); continue; }

		/* ——————————————————————————————————————————————————————————————— */

		ERROR_INVALID_OPT();
	}

	/* ——————————————————————————————————————————————————————————————— */

	// if `--colour` wasn't set, or if `--colour auto` was given, then determine whether colour should be used
	if (colour_auto) U_DO_COLOUR = doColourAuto();

	// returns how many options were parsed, and therefore where the names of the files/directories start
	return i;
}

/* —— Define Getter Functions —————————————————————————————————————————————————————————————————————————————————————— */

SortByField SORT_BY (void) { return U_SORT_BY			; }
bool DO_REVERSE_SORT(void) { return U_DO_REVERSE_SORT	; }

bool DO_CLEAR		(void) { return U_DO_CLEAR			; }
bool DO_COLOUR		(void) { return U_DO_COLOUR			; }
bool DO_HEADER		(void) { return U_DO_HEADER			; }
bool DO_DIVIDERS	(void) { return U_DO_DIVIDERS		; }
bool DO_MOUNT_DEV	(void) { return U_DO_MOUNT_DEV		; }
bool DO_DIM_HIDDEN	(void) { return U_DO_DIM_HIDDEN		; }
bool DO_TINY_FLAGS	(void) { return U_DO_TINY_FLAGS		; }
bool DO_SHORT_FLAGS	(void) { return U_DO_SHORT_FLAGS	; }
bool SORT_DIRS_FIRST(void) { return U_SORT_DIRS_FIRST	; }

/* ————————————————————————————————————————————————————————— */

bool do_suffix	(void) { return U_DO_SUFFIX	; }
bool do_link_to	(void) { return U_DO_LINK_TO; }

bool do_nlink	(void) { return U_DO_NLINK	; }
bool do_dev_no	(void) { return U_DO_DEV_NO	; }
bool do_inode	(void) { return U_DO_INODE	; }

bool do_flags	(void) { return U_DO_FLAGS	; }		bool do_flag_str(void) { return U_DO_FLAG_STR; }
bool do_mode	(void) { return U_DO_MODE	; }		bool do_mode_str(void) { return U_DO_MODE_STR; }
bool do_size	(void) { return U_DO_SIZE	; }		bool do_size_str(void) { return U_DO_SIZE_STR; }
bool do_uid		(void) { return U_DO_UID	; }		bool do_usr_name(void) { return U_DO_USR_NAME; }
bool do_gid		(void) { return U_DO_GID	; }		bool do_grp_name(void) { return U_DO_GRP_NAME; }
bool do_time	(void) { return U_DO_TIME	; }		bool do_time_str(void) { return U_DO_TIME_STR; }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
