/// @file debugging/assert.c

#include <stdio.h>	// fprintf()
#include <stdlib.h>	// abort()

#if __STDC_VERSION__ < 202300L
#	include <stdbool.h> // bool, true
#endif

#include "_defs.h" // REL_PATH()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool d__assert(
	const int expr, const char *const expr_str, const char *const message_,
	const int line, const char *const filepath, const char *const funcname
) {
	if (expr) return true;

	const char *const message = message_ ? message_	: "";
	const char *const msg_col = message_ ? BRED		: "";

	fprintf(stderr,
		NRED	"assertion failed: "
		"%s"	"%s\n"		// [msg_col], message
		BMAG	"\t%s\n"	// expr_str
		BBLUE	"%s"		// funcname
		RESET	"() @ "
		GREEN	"%s "		// filepath
		NBLUE	"(%d)\n"	// line
		RESET,

		msg_col, message,
		expr_str,
		funcname,
		REL_PATH(filepath),
		line
	);

	abort();
	__builtin_unreachable();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore bmag
