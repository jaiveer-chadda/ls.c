/// @file output/print-name.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "../info/info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

#include "output.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#define MIN_DIVIDER_LEN 5

#define DO_DIM(name, flags) \
		(DO_DIM_HIDDEN() &&	\
		(((flags) & UF_HIDDEN) || ((name)[0] == '.' && strcmp((name), DOTDIR) != 0))	\
	)

/// Only turn a filename into a divider if:
///  - the DO_DIVIDERS setting is on, and 
///  - the file doesn't contain an escape character
///  - its a regular file, directory, or a dataless file
#define CHECK_FOR_DIVIDER()				\
	(DO_DIVIDERS()						\
		&& !does_have_escape			\
		&& (strlen(file_colour) == 0	\
			|| *colour == FC_REGULAR	\
			|| *colour == FC_DIRECT		\
			|| *colour == FC_DATALESS	\
		)								\
	)

#define GET_WINDOW_SIZE(winsize_struct) (ioctl(STDOUT_FILENO, TIOCGWINSZ, &(winsize_struct)) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void findDivider(bool *do_divider, char *div_char, const char *name) {
	/// Which characters to check for, to see if a file is a divider file, listed in order of priority.
	const char *DIVIDER_OPTIONS[] = { "─", "—", "–", "-", "_", "•" };
	const int NUM_OPTIONS = (int)(sizeof(DIVIDER_OPTIONS) / sizeof(DIVIDER_OPTIONS[0]));

	for (int i = 0; i < NUM_OPTIONS; i++) {
		const char *test_char = DIVIDER_OPTIONS[i];
		// `4` being the maximum length of a single multibyte character like `─` or `•`
		char test_divider[4 * MIN_DIVIDER_LEN];

		// create a dummy string containing 5 of the divider characters
		sprintf(test_divider, "%s%s%s%s%s", test_char, test_char, test_char, test_char, test_char);

		// then check whether that dummy string is in the filename
		if (strstr(name, test_divider) != NULL) {
			*do_divider = true;
			strcpy(div_char, test_char);
			break;
		}
	}
}

/* —————————————————————————————————————————————————————————————————————————————————————————— */

static inline void printDivider(const char *div_char) {
	struct winsize window;

	// instead of having to figure out how many chars have already been written on this line:
	//  - turn off word wrapping (`tput rmam`)
	//	  - (so that any characters printed beyond the end of the screen aren't shown)
	//  - then print as many divider characters are there are columns (screen width)
	//  - finally, turn word wrapping back on (`tput smam`)
	if (GET_WINDOW_SIZE(window)) {
		printf("%s", RMAM);

		const int COLUMNS = window.ws_col;
		for (int _ = 0; _ < COLUMNS; _++) printf("%s", div_char);

		printf("%s%s", (DO_COLOUR() ? RESET : NO_COLOUR), SMAM);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printName(const name_t name, const FileColour *colour, const bool *is_hln, const flag_t *flags, suff_t *suffix) {
	char *file_colour = malloc(32);

	sprintf(file_colour, "%s%s%s" "%s",
		DO_DIM(name, *flags)	  ? DIM				 ";" : NO_COLOUR,
		strcmp(name, DOTDIR) == 0 ? UNDER			 ";" : NO_COLOUR,
		*is_hln					  ? HARDLN_UNDERLINE ";" : NO_COLOUR,

		(char*)(file_colour_esc[*colour])
	);

	/* ————————————————————————————————————————————————————————————————— */

	path_t escaped_name;
	bool does_have_escape = escapeName(escaped_name, name, file_colour);

	/* ————————————————————————————————————————————————————————————————— */

	bool do_divider = false;
	char div_char[4] = "";

	if (CHECK_FOR_DIVIDER()) findDivider(&do_divider, div_char, name);

	// make sure that directories which have been turned into dividers don't show their suffixes
	if (do_divider && *colour == FC_DIRECT) *suffix = '\0';

	/* ————————————————————————————————————————————————————————————————— */

	if (DO_COLOUR()) {
		printf("%s" "%s%s%s" "%s" "%s",
			PRE_NAME_PAD,
			CSI, file_colour, END,
			escaped_name,
			// if the file's a divider, then there's no need to reset the colour
			(do_divider ? NO_COLOUR : RESET)
		);

	} else {
		printf("%s" "%s", PRE_NAME_PAD, escaped_name);
	}

	free(file_colour);

	/* ————————————————————————————————————————————————————————————————— */

	if (do_divider) printDivider(div_char);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
