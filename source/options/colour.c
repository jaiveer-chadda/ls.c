/// @file options/colour.c

#include <string.h>
#include <stdlib.h> // getenv()
#include <unistd.h> // isatty()

#include "utils/string.h" // strends()

#define IS_VALID_VAR(pchar) \
	((pchar) != NULL &&		\
	*(pchar) != '\0')

bool doColourAuto(void) {
	// if we're not outputting to the terminal, don't show any colour
	if (!isatty(STDOUT_FILENO)) return false;

	/* ——————————————————————————————————————————————— */

	// if `NO_COLOR` is set, and has some value, then again, don't show any colour
	const char *NO_COLOR = getenv("NO_COLOR");
	if (IS_VALID_VAR(NO_COLOR)) return false;

	/* ——————————————————————————————————————————————— */

	// to see if the terminal supports 24-bit colour output, firstly check `$COLORTERM`
	const char *COLORTERM = getenv("COLORTERM");

	if (IS_VALID_VAR(COLORTERM)) {
		if (strcmp(COLORTERM, "truecolor") == 0 ||
			strcmp(COLORTERM, "24bit"	 ) == 0 ||
			strcmp(COLORTERM, "256color" ) == 0
		) return true;

		// if `$COLORTERM` is set & valid, but it isn't any of the above values,
		//	we could assume that the term doesn't support 24-bit colour, but I don't think it hurts to check `$TERM`
	}

	/* ——————————————————————————————————————————————— */

	// if `$COLORTERM` isn't set, or is empty, then check the suffix of the `$TERM` var instead
	const char *TERM = getenv("TERM");

	if (IS_VALID_VAR(TERM)) {
		// if check whether 
		if (strends(TERM, "-direct"	 ) ||
			strends(TERM, "-256color")
		) return true;
	}

	return false;
}
