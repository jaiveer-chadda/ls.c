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

// `U_DO_COLOUR` doesn't need a default - it's the only option that'll be set no matter what
static bool U_DO_COLOUR, U_DO_TINY_FLAGS = false, U_DO_SHORT_FLAGS = true;
static SortByField U_SORT_BY = SB_DEFAULT;

#define X(name, ...) [name] = { __VA_ARGS__ },
static BinaryOption BINARY_OPTS[] = { BINARY_OPTIONS_TABLE };
#undef X

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

/* ——————————————————————————————————————————————————————————————————— */

// #define BINARY_OPT(flag, var) \
// 	if (OPTION_IS("--"	  # flag)) { (var) = true ; continue; } \
// 	if (OPTION_IS("--no-" # flag)) { (var) = false; continue; }

// #define FIELD_OPT(flag, var) \
// 	if (OPTION_IS_OF("--" # flag, "--do-" # flag))	{ (var) = true ; continue; } \
// 	if (OPTION_IS("--no-" # flag))					{ (var) = false; continue; }

#define ARR_LEN(array) (int)(sizeof(array) / sizeof(array[0]))
#define NOT_REACHED_END_OF_ARR(idx, array) idx < ARR_LEN(array) && array[idx] != NULL

#define BIN_OPT_VAL(option) BINARY_OPTS[BO_ ## option].value
#define MAKE_BIN_OPT_FUNC(option) bool option(void) { return BIN_OPT_VAL(option); }

/* ——————————————————————————————————————————————————————————————————— */

#define THROW_ERR(message, ...)								\
	do {													\
		fprintf(stderr, (ERROR message "\n"), __VA_ARGS__);	\
		usage(EXIT_FAILURE);								\
	} while (0)

#define ERR_INVALID_OPT() THROW_ERR("unknown option: `%s`", opt)
#define ERR_TAKES_ARG()	  THROW_ERR("`%s` takes an argument", opt)
#define ERR_BAD_ARG(args) THROW_ERR("invalid argument `%s` for `%s`. possible arguments are: %s", optarg, opt, (args))

/* ——————————————————————————————————————————————————————————————————— */

static inline void allOptsOn(void) {
	U_DO_TINY_FLAGS	 = false,
	U_DO_SHORT_FLAGS = false;

	for (int opt_i = 0; opt_i < BINOPT_COUNT; opt_i++) {
		BINARY_OPTS[opt_i].value = true;
	}
}

static inline void allFieldsOn(void) {
	for (int opt_i = 0; opt_i < BINOPT_COUNT; opt_i++) {
		if (BINARY_OPTS[opt_i].is_field) {
			BINARY_OPTS[opt_i].value = true;
		}
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int setOptions(const int argc, const char *argv[]) {
	if (strcmp(argv[0], "c" PROGRAM_NAME) == 0) BIN_OPT_VAL(DO_CLEAR) = true;

	bool colour_auto = true;

	int i;
	for (i = 1; i < argc; i++) {
		const char *opt		= argv[i];
		const char *optarg	= ARG_EXISTS ? argv[i + 1] : "";

		/* —— End Option Parsing ————————————————————————————————————————— */

		if (opt[0] != '-') break;
		if (OPTION_IS("--")) { i++; break; }

		/* —— --help ————————————————————————————————————————————————————— */

		if (OPTION_IS("--help") || OPTION_IS("-h")) usage(EXIT_SUCCESS);

		/* —— --sort-by —————————————————————————————————————————————————— */

		if (OPTION_IS("--no-sort")) {
			U_SORT_BY = SB_NONE;
			continue;
		}

		if (OPTION_IS("--sort") || OPTION_IS("--sort-by") || OPTION_IS("--rsort")) {
			if (OPTION_IS("--rsort")) BIN_OPT_VAL(DO_REVERSE_SORT) = !BIN_OPT_VAL(DO_REVERSE_SORT);

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

			else if	(HAS_ARG) ERR_BAD_ARG(
				"\n - name (default)"	  "\n - size"  "\n - time"
				"\n - uid"   "\n - gid"   "\n - inode" "\n - devno"
				"\n - links" "\n - flags" "\n - mode"  "\n - none"
			);
			else ERR_TAKES_ARG();

			i++;
			continue;
		}

		/* —— --colour ——————————————————————————————————————————————————— */

		if (OPTION_IS("--no-colour") || OPTION_IS("--no-color")) {
			colour_auto = false, U_DO_COLOUR = false;
			continue;
		}

		if (OPTION_IS("--colour") || OPTION_IS("--color")) {
			colour_auto = false;
			if (OPTARG_IS("always")) { U_DO_COLOUR = true ; i++; continue; }
			if (OPTARG_IS("never" )) { U_DO_COLOUR = false; i++; continue; }
			if (OPTARG_IS("auto"  )) { colour_auto = true ; i++; continue; }
			if (HAS_ARG) ERR_BAD_ARG("always, never, auto");
			// if no argument is given, then, like `ls`, assume `--colour` means `--colour always`
			U_DO_COLOUR = true; continue;
		}

		/* —— --flags ———————————————————————————————————————————————————— */

		if (OPTION_IS("--flags")) {
			if (OPTARG_IS("long" )) { U_DO_SHORT_FLAGS = false, U_DO_TINY_FLAGS = false; i++; continue; }
			if (OPTARG_IS("short")) { U_DO_SHORT_FLAGS = true , U_DO_TINY_FLAGS = false; i++; continue; }
			if (OPTARG_IS("tiny" )) { U_DO_SHORT_FLAGS = false, U_DO_TINY_FLAGS = true ; i++; continue; }
			if (HAS_ARG) ERR_BAD_ARG("long, short, tiny");
			// if there's no arg, then match the rest of the other field options, and turn the `flags` field on
			BIN_OPT_VAL(do_flags) = true; continue;
		}

		/* —— Binary Options ————————————————————————————————————————————— */

		for (int opt_i = 0; opt_i < BINOPT_COUNT; opt_i++) {
			BinaryOption *bin_opt = &BINARY_OPTS[opt_i];

			for (int flag_i = 0; NOT_REACHED_END_OF_ARR(flag_i, bin_opt->long_flags); flag_i++) {
				char long_flag[MAX_OPT_FLAG_LEN + 5];
				sprintf(long_flag, "--%s", bin_opt->long_flags[flag_i]);

				printf("%s", long_flag); fflush(stdout);

				if (OPTION_IS(long_flag)) {
					bin_opt->value = true;
					goto end_of_loop;
				}
			}
		}

		/* —— All Fields ————————————————————————————————————————————————— */

		if (OPTION_IS("--all-fields"))	{ allFieldsOn();			  continue; }
		if (OPTION_IS("--all"))			{ allFieldsOn(); allOptsOn(); continue; }

		/* —— Invalid Options ———————————————————————————————————————————— */

		// any input that hasn't been matched above should be treated as an invalid option
		ERR_INVALID_OPT();

		/* —— `goto` Target —————————————————————————————————————————————— */

		end_of_loop:
			continue;
	}

	/* —— Handle Colour & Return ————————————————————————————————————— */

	// if `--colour` wasn't set, or if `--colour auto` was given, then determine whether colour should be used
	if (colour_auto) U_DO_COLOUR = doColourAuto();

	// returns how many options were parsed, and therefore where the names of the files/directories start
	return i;
}

/* —— Define Getter Functions —————————————————————————————————————————————————————————————————————————————————————— */

SortByField SORT_BY	(void) { return U_SORT_BY		; }
bool DO_COLOUR		(void) { return U_DO_COLOUR		; }
bool DO_TINY_FLAGS	(void) { return U_DO_TINY_FLAGS	; }
bool DO_SHORT_FLAGS	(void) { return U_DO_SHORT_FLAGS; }

/* ————————————————————————————————————————————————————————— */

MAKE_BIN_OPT_FUNC(DO_CLEAR)
MAKE_BIN_OPT_FUNC(DO_HEADER)
MAKE_BIN_OPT_FUNC(DO_DIVIDERS)
MAKE_BIN_OPT_FUNC(DO_MOUNT_DEV)
MAKE_BIN_OPT_FUNC(DO_DIM_HIDDEN)
MAKE_BIN_OPT_FUNC(SORT_DIRS_FIRST)
MAKE_BIN_OPT_FUNC(DO_REVERSE_SORT)

/* ————————————————————————————————————————————————————————— */

MAKE_BIN_OPT_FUNC(do_suffix	 )
MAKE_BIN_OPT_FUNC(do_link_to )

MAKE_BIN_OPT_FUNC(do_nlink	 )
MAKE_BIN_OPT_FUNC(do_dev_no	 )
MAKE_BIN_OPT_FUNC(do_inode	 )

MAKE_BIN_OPT_FUNC(do_flags	 )	MAKE_BIN_OPT_FUNC(do_flag_str)
MAKE_BIN_OPT_FUNC(do_mode	 )	MAKE_BIN_OPT_FUNC(do_mode_str)
MAKE_BIN_OPT_FUNC(do_size	 )	MAKE_BIN_OPT_FUNC(do_size_str)
MAKE_BIN_OPT_FUNC(do_uid	 )	MAKE_BIN_OPT_FUNC(do_usr_name)
MAKE_BIN_OPT_FUNC(do_gid	 )	MAKE_BIN_OPT_FUNC(do_grp_name)
MAKE_BIN_OPT_FUNC(do_time	 )	MAKE_BIN_OPT_FUNC(do_time_str)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
