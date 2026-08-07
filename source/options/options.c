/// @file options/options.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "options.h"
#include "utils/malloc.h"
#include "utils/string.h"

#ifndef t
#define t 1 /* this doesn't do anything - it's just here to stop a rly annoying bug that my error checker has */
#define f 0
#endif

/* —— Initialise Options ——————————————————————————————————————————————————————————————————————————————————————————— */

// `U_DO_COLOUR` doesn't need a default - it's the only option that'll be set no matter what
static bool U_DO_COLOUR, U_DO_TINY_FLAGS = false, U_DO_SHORT_FLAGS = true;
static SortByField U_SORT_BY = SB_DEFAULT;

#define X(name, ...) [name] = { __VA_ARGS__ },
static BinaryOption BINARY_OPTS[] = { BINARY_OPTIONS_TABLE };
#undef X

/* —— doColourAuto() ——————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool doColourAuto(void) {
	if (!isatty(STDOUT_FILENO)) return false;

	const char *NO_COLOR = getenv("NO_COLOR");
	if (!(NO_COLOR == NULL || strlen(NO_COLOR) == 0)) return false;

	const char *COLORTERM = getenv("COLORTERM");
	if (COLORTERM == NULL || (
		strcmp(COLORTERM, "truecolor") != 0 &&
		strcmp(COLORTERM, "24bit"	 ) != 0
	)) return false;

	return true;
}

/* —— Generic Macros ——————————————————————————————————————————————————————————————————————————————————————————————— */

#define ARG_EXISTS	((i + 1 < argc) && (argv[i + 1][0] != '-'))
#define HAS_ARG		(strcmp(optarg, "") != 0)

#define CONTINUE goto label_continue

#define CONSUME_ARG i++
#define UN_CONSUME_ARG i--

/* —— Option/Optarg Macros ——————————————————————————————————————————— */

#define OPTARG_IS(str) (strcmp(optarg, (str)) == 0)
#define IS_OPTION(str) (strcmp(opt, (str)) == 0)

#define OPT_1(a)			IS_OPTION(a)
#define OPT_2(a, b)			IS_OPTION(a) || IS_OPTION(b)
#define OPT_3(a, b, c)		IS_OPTION(a) || IS_OPTION(b) || IS_OPTION(c)
#define OPT_4(a, b, c, d)	IS_OPTION(a) || IS_OPTION(b) || IS_OPTION(c) || IS_OPTION(d)

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME

#define OPTION_IS(...) GET_MACRO(__VA_ARGS__, OPT_3, OPT_2, OPT_1)(__VA_ARGS__)

/* —— Binary Option Macros ——————————————————————————————————————————— */

#define ARR_LEN(array) (int)(sizeof(array) / sizeof(array[0]))
#define NOT_REACHED_END_OF_ARR(idx, array) idx < ARR_LEN(array) && array[idx] != NULL

#define VALUE_OF(option) BINARY_OPTS[BO_ ## option].value
#define MAKE_BIN_OPT_FUNC(option) bool option(void) { return VALUE_OF(option); }

#define CHECK_LONG_FLAG(prefix, bool_val)						\
	do {														\
		sprintf(flag_buf, prefix "%s", base_flag);				\
		if (OPTION_IS(flag_buf)) {								\
			if ((equal_arg != NULL) && HAS_ARG) ERR_NO_ARGS();	\
			bin_opt->value = bool_val;							\
			CONTINUE;											\
		}														\
	} while (0)

/* —— Error Macros ——————————————————————————————————————————————————— */

#define THROW_ERR(message, ...)								\
	do {													\
		fprintf(stderr, (ERROR message "\n"), __VA_ARGS__);	\
		usage(EXIT_FAILURE);								\
	} while (0)

#define ERR_INVALID_OPT() THROW_ERR("unknown option: `%s`", opt)
#define ERR_TAKES_ARG()	  THROW_ERR("`%s` takes an argument", opt)
#define ERR_EMPTY_ARG()	  THROW_ERR("argument for `%s` is empty", opt)
#define ERR_NO_ARGS()	  THROW_ERR("`%s` doesn't take an argument", opt)
#define ERR_BAD_ARG(args) THROW_ERR("invalid argument `%s` for `%s`. possible arguments are: %s", optarg, opt, (args))

/* —— all...On() ————————————————————————————————————————————————————— */

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

/* ── ── setOptions() ── ─────────────────────────────────────────────────────────────────────────────────────────── */

int setOptions(const int argc, const char *argv[]) {
	if (strends(argv[0], "c" PROGRAM_NAME)) VALUE_OF(DO_CLEAR) = true;

	bool colour_auto = true;

	int i;
	for (i = 1; i < argc; i++) {
		char *opt	 = (char *)argv[i];
		char *optarg = ARG_EXISTS ? (char *)argv[i + 1] : "";

		/* —— End Option Parsing ————————————————————————————————————————— */

		if (opt[0] != '-' && opt[0] != '+') break;
		if (OPTION_IS("--")) { CONSUME_ARG; break; }

		/* —— Check for `--option=value` ————————————————————————————————— */

		const char *equal_arg = strchr(opt, '=');
		bool did_malloc = false;

		if (equal_arg != NULL) {
			optarg = (char *)(equal_arg + 1);
			UN_CONSUME_ARG;
			if (strlen(optarg) == 0) ERR_EMPTY_ARG();

			const int option_len = equal_arg - opt;
			char *adj_opt = emalloc(option_len + 1);
			did_malloc = true;

			strncpy(adj_opt, opt, option_len);
			adj_opt[option_len] = '\0';

			opt = adj_opt;
		}

		/* —— --help ————————————————————————————————————————————————————— */

		if (OPTION_IS("--help", "-h")) usage(EXIT_SUCCESS);

		/* —— --sort-by —————————————————————————————————————————————————— */

		if (OPTION_IS("--no-sort")) {
			U_SORT_BY = SB_NONE;
			CONTINUE;
		}

		if (OPTION_IS("--sort", "--sort-by", "--rsort")) {
			if (OPTION_IS("--rsort")) VALUE_OF(DO_REVERSE_SORT) = !VALUE_OF(DO_REVERSE_SORT);

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

			CONSUME_ARG;
			CONTINUE;
		}

		/* —— --colour ——————————————————————————————————————————————————— */

		if (OPTION_IS("--no-colour", "--no-color")) {
			colour_auto = false, U_DO_COLOUR = false;
			CONTINUE;
		}

		if (OPTION_IS("--colour", "--color")) {
			colour_auto = false;
			if (OPTARG_IS("always")) { U_DO_COLOUR = true ; CONSUME_ARG; CONTINUE; }
			if (OPTARG_IS("never" )) { U_DO_COLOUR = false; CONSUME_ARG; CONTINUE; }
			if (OPTARG_IS("auto"  )) { colour_auto = true ; CONSUME_ARG; CONTINUE; }
			if (HAS_ARG) ERR_BAD_ARG("always, never, auto");

			// if no argument is given, then, like `ls`, assume `--colour` means `--colour always`
			U_DO_COLOUR = true;
			CONTINUE;
		}

		/* —— --flags ———————————————————————————————————————————————————— */

		if (OPTION_IS("--flags")) {
			if (OPTARG_IS("long" )) { U_DO_SHORT_FLAGS = false, U_DO_TINY_FLAGS = false; CONSUME_ARG; CONTINUE; }
			if (OPTARG_IS("short")) { U_DO_SHORT_FLAGS = true , U_DO_TINY_FLAGS = false; CONSUME_ARG; CONTINUE; }
			if (OPTARG_IS("tiny" )) { U_DO_SHORT_FLAGS = false, U_DO_TINY_FLAGS = true ; CONSUME_ARG; CONTINUE; }
			if (HAS_ARG) ERR_BAD_ARG("long, short, tiny");
			// if there's no arg, then match the rest of the other field options, and turn the `flags` field on
			VALUE_OF(do_flags) = true; CONTINUE;
		}

		/* —— All Fields ————————————————————————————————————————————————— */

		if (OPTION_IS("--all-fields"))	{ allFieldsOn();			  CONTINUE; }
		if (OPTION_IS("--all"))			{ allFieldsOn(); allOptsOn(); CONTINUE; }

		/* —— Binary Options ————————————————————————————————————————————— */

		for (int opt_i = 0; opt_i < BINOPT_COUNT; opt_i++) {
			BinaryOption *bin_opt = &BINARY_OPTS[opt_i];

			for (int flag_i = 0; NOT_REACHED_END_OF_ARR(flag_i, bin_opt->long_flags); flag_i++) {
				const char *base_flag = bin_opt->long_flags[flag_i];
				test_flag_t flag_buf;

				CHECK_LONG_FLAG("--"   , true ); // check standard `--...` flag
				CHECK_LONG_FLAG("--do-", true ); // check `--do-...` flag
				CHECK_LONG_FLAG("--no-", false); // check `--no-...` flag
			}
		}

		/* —— Invalid Options ———————————————————————————————————————————— */

		// any input that hasn't been matched above should be treated as an invalid option
		ERR_INVALID_OPT();

		/* —— `goto label_continue` Target ——————————————————————————————— */

		label_continue:
			if (did_malloc) free(opt);
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
