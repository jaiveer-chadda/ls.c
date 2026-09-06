/// @file options/options.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "options.h"
#include "model/global.h"
#include "utils/malloc.h"
#include "utils/strings.h"

#include "debugging.h"

#ifndef t
#define t 1 /* this doesn't do anything - it's just here to stop a rly annoying bug that my error checker has */
#define f 0
#endif

/* —— Initialise Options ——————————————————————————————————————————————————————————————————————————————————————————— */

// `U_DO_COLOUR` doesn't need a default - it's the only option that'll be set no matter what
static bool U_DO_COLOUR, U_DO_TINY_FLAGS = false, U_DO_SHORT_FLAGS = true;
static uint8_t U_DEPTH = 1;
static SortByField U_SORT_BY = SB_DEFAULT;

#define X(name, ...) [(BO_ ## name)] = (BinaryOption){ __VA_ARGS__ },
BinaryOption BINARY_OPTS[] = { BINARY_OPTIONS_TABLE };
#undef X

/* —— Generic Macros ——————————————————————————————————————————————————————————————————————————————————————————————— */

#define ARG_EXISTS	((i + 1 < argc) && (argv[i + 1][0] != '-'))
#define HAS_ARG		(optarg != NULL && optarg[0] != '\0')

#define CONTINUE goto label_continue

#define CONSUME_ARG i++
#define UN_CONSUME_ARG i--

/* —— Option/Optarg Macros ——————————————————————————————————————————— */

#define OPTARG_IS(str) (strcmp(optarg, (str)) == 0)
#define IS_OPTION(str) (strcmp(opt,	   (str)) == 0)

#define OPT_1(a)			IS_OPTION(a)
#define OPT_2(a, b)			IS_OPTION(a) || IS_OPTION(b)
#define OPT_3(a, b, c)		IS_OPTION(a) || IS_OPTION(b) || IS_OPTION(c)
#define OPT_4(a, b, c, d)	IS_OPTION(a) || IS_OPTION(b) || IS_OPTION(c) || IS_OPTION(d)

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define OPTION_IS(...) GET_MACRO(__VA_ARGS__, OPT_3, OPT_2, OPT_1)(__VA_ARGS__)

/* —— Binary Option Macros ——————————————————————————————————————————— */

#define ARR_LEN(array) ((int)(sizeof((array)) / sizeof((array)[0])))
#define NOT_REACHED_END_OF_ARR(idx, array) (((idx) < ARR_LEN((array))) && ((array)[(idx)] != NULL))

#define VALUE_OF(option) (BINARY_OPTS[(BO_ ## option)].value)

#define CHECK_LONG_FLAG(prefix, bool_val) do {				\
	sprintf(flag_buf, (prefix "%s"), base_flag);			\
	if (OPTION_IS(flag_buf)) {								\
		if ((equal_arg != NULL) && HAS_ARG) ERR_NO_ARGS();	\
		bin_opt->value = (bool_val);						\
		CONTINUE;											\
	}														\
} while (0)

/* —— Error Macros ——————————————————————————————————————————————————— */

#define THROW_ERR(fmt, ...)										\
	do {														\
		fprintf(stderr, ("%s: " fmt "\n"), argv0, __VA_ARGS__);	\
		usage(EXIT_FAILURE);									\
	} while (0)

#define ERR_INVALID_OPT() THROW_ERR("unknown option: `%s`", opt)
#define ERR_TAKES_ARG()	  THROW_ERR("`%s` takes an argument", opt)
#define ERR_EMPTY_ARG()	  THROW_ERR("argument for `%s` is empty", opt)
#define ERR_NO_ARGS()	  THROW_ERR("`%s` doesn't take an argument", opt)
#define ERR_BAD_ARG(args) THROW_ERR("invalid argument `%s` for `%s`. possible arguments are: %s", optarg, opt, (args))
#define ERR_DEPTH()		  THROW_ERR(				\
	"invalid argument `%s` for `%s`. "				\
	"argument must be an integer between 0 and %d.",\
	optarg, opt, RECURSION_LIMIT					\
)

/* —— all Opts/Fields On() ——————————————————————————————————————————— */

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
	if (argv0[0] == 'c') VALUE_OF(DO_CLEAR) = true;

	/// True if the colour should be determined automatically by the program.
	/// False if the user has specified either `--colour=always` or `--colour=never`.
	bool colour_auto = true;

	int i;
	for (i = 1; i < argc; i++) {

		/// The option to be parsed, including the leading `--`.
		const char *opt		= (char *)argv[i];
		/// The argument given to an option either as `--opt arg`, or `--opt=arg`. An empty string if no arg was passed.
		const char *optarg	= ARG_EXISTS ? (char *)argv[i + 1] : "";

		/* —— End Option Parsing ————————————————————————————————————————— */

		if (opt[0] != '-' && opt[0] != '+') break;
		if (OPTION_IS("--")) { CONSUME_ARG; break; }

		/* —— Check for `--option=value` ————————————————————————————————— */

		bool did_malloc = false;

		// find the the first equals sign in the string
		const char *const equal_arg = strchr(opt, '=');

		// if there wasn't an equals sign, then just continue as usual
		if (equal_arg != NULL) {
			// set the charater after the equals sign to be the new start of the argument
			optarg = equal_arg + 1;

			// since all options-checking statements below track whether they've been passed an argument (in order to
			//	accurately track where the filenames begin), we need to let them know that even though they see an
			//	argument, we shouldn't increment the flag counter - hence we decrement it here with `UN_CONSUME_ARG`
			UN_CONSUME_ARG;

			// catch inputs like `--option=` (without any arg after the equals)
			if (strlen(optarg) == 0) ERR_EMPTY_ARG();

			const int option_len = equal_arg - opt;

			// allocate memory for the new option
			char *const adj_opt = emalloc(option_len + 1);
			// and note down that we should free the memory later
			did_malloc = true;

			// finally, make sure that `opt` has the correct information, and is null-terminated
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
			// if the sort should be reversed, flip the boolean representing the sorting order
			if (OPTION_IS("--rsort")) {
				VALUE_OF(DO_REVERSE_SORT) = !VALUE_OF(DO_REVERSE_SORT);
			}

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

		// just providing an easier way to turn colour off
		if (OPTION_IS("--no-colour", "--no-color")) {
			colour_auto = false, U_DO_COLOUR = false;
			CONTINUE;
		}

		if (OPTION_IS("--colour", "--color")) {
			// if the option is `--colour`, assume that the user passed `always` or `never` as an argument,
			//	and set `colour_auto` to false
			colour_auto = false;
			if (OPTARG_IS("always")) { U_DO_COLOUR = true ; CONSUME_ARG; CONTINUE; }
			if (OPTARG_IS("never" )) { U_DO_COLOUR = false; CONSUME_ARG; CONTINUE; }
			if (OPTARG_IS("auto"  )) { colour_auto = true ; CONSUME_ARG; CONTINUE; }
			// ↑ only if they passed `auto`, should we set `colour_auto` back to true
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
			//	this is similar to `--colour`, except that it changes a binary field instead
			VALUE_OF(do_flags) = true; CONTINUE;
		}

		/* —— --depth ———————————————————————————————————————————————————— */

		if (OPTION_IS("--depth", "--level")) {
			char *p_strend; // pointer to the end of the argument string
			// convert the string to a `long`
			const long int_arg = strtol(optarg, &p_strend, BASE_10);

			if (int_arg <= RECURSION_LIMIT && int_arg >= 0 && // if its within the set limits
				p_strend > optarg && // and some characters were read
				p_strend[0] == '\0' // and all characters were read
			) {
				// then set it as the globally available depth (and convert it down to an unsigned char)
				U_DEPTH = (uint8_t)int_arg;
				CONSUME_ARG;
				CONTINUE;
			}

			if (HAS_ARG) ERR_DEPTH();
			else ERR_TAKES_ARG();
		}

		/* —— All Fields ————————————————————————————————————————————————— */

		if (OPTION_IS("--all-fields"))	{ allFieldsOn();			  CONTINUE; }
		if (OPTION_IS("--all"))			{ allFieldsOn(); allOptsOn(); CONTINUE; }

		/* —— Binary Options ————————————————————————————————————————————— */

		test_flag_t flag_buf;

		// iterate through the binary options and check them one at a time
		for (int opt_i = 0; opt_i < BINOPT_COUNT; opt_i++) {
			BinaryOption *const bin_opt = &BINARY_OPTS[opt_i];

			// then iterate through all the possible long flags for each bin opt, and check those
			for (int flag_i = 0; NOT_REACHED_END_OF_ARR(flag_i, bin_opt->long_flags); flag_i++) {
				const char *const base_flag = bin_opt->long_flags[flag_i];
				if (base_flag[0] == '\0') continue;

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
			if (did_malloc) efree((void*)opt);
			continue;
	}

	/* —— Post-Loop Logic & Return ——————————————————————————————————— */

	// if `--colour` wasn't set, or if `--colour=auto` was given, then determine whether colour should be used
	if (colour_auto) U_DO_COLOUR = doColourAuto();

	// returns how many options were parsed, and therefore where the names of the files/directories start
	return i;
}

/* —— Define Getter Functions —————————————————————————————————————————————————————————————————————————————————————— */

SortByField SORT_BY	(void) { return U_SORT_BY		; }
uint8_t O__DEPTH	(void) { return U_DEPTH			; }
bool DO_COLOUR		(void) { return U_DO_COLOUR		; }
bool DO_TINY_FLAGS	(void) { return U_DO_TINY_FLAGS	; }
bool DO_SHORT_FLAGS	(void) { return U_DO_SHORT_FLAGS; }

// create very basic getter functions for each of the binary options
#define X(name, ...) \
	inline bool name(void) { return VALUE_OF(name); }
BINARY_OPTIONS_TABLE
#undef X

/* ————————————————————————————————————————————————————————— */

inline bool do_time_t(TimeType type) {
	static bool (* const funcs[])(void) = {
		[A_TIME] = do_atime,
		[M_TIME] = do_mtime,
		[C_TIME] = do_ctime,
		[B_TIME] = do_btime,
	};

	return funcs[type]();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
