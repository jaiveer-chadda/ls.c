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

#define DO_DIM(name, flags)	\
	((DO_DIM_HIDDEN()) &&		\
		((flags & UF_HIDDEN) || (name[0] == '.' && strcmp(name, CURRENT_DIR) != 0)))

#define GET_NAME(name)	(strcmp(name, CURRENT_DIR) == 0 ? adjusted_path : name)
#define GET_DIM_HL()	((DO_DIM(name, *flags) || do_divider) ? DIM : "")
#define GET_HARDLN_UL()	(*is_hln ? HARDLN_UNDERLINE : "")

#define DO_OCT_ESC(chr) (0 <= chr && chr <= 7)
#define DO_HEX_ESC(chr) ((7 < chr && chr <= 31) || chr == 127)

#define TRY_DIVIDER()					\
	(DO_DIVIDERS()						\
		&& !does_have_escape			\
		&& (strlen(file_colour) == 0	\
			|| *colour == FC_REGULAR	\
			|| *colour == FC_DIRECT		\
		)								\
	)

typedef unsigned char u_char;
typedef unsigned int  u_int;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool getEscSequence(char *esc_seq, const char orig_char) {
	u_char chr = (u_char)orig_char;
	switch (chr) {
		case '\\'	: strcpy(esc_seq, "\\\\");	return true;
		case '\a'	: strcpy(esc_seq, "\\a");	return true;
		case '\b'	: strcpy(esc_seq, "\\b");	return true;
		case '\t'	: strcpy(esc_seq, "\\t");	return true;
		case '\n'	: strcpy(esc_seq, "\\n");	return true;
		case '\v'	: strcpy(esc_seq, "\\v");	return true;
		case '\f'	: strcpy(esc_seq, "\\f");	return true;
		case '\r'	: strcpy(esc_seq, "\\r");	return true;
		case '\x1b'	: strcpy(esc_seq, "\\e");	return true;
	}

	if DO_OCT_ESC(chr) { sprintf(esc_seq, "\\%u", (u_int)chr); return true; }
	if DO_HEX_ESC(chr) { sprintf(esc_seq, "\\x%02X",	 chr); return true; }

	return false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Checks whether an ANSI escape sequence will set the background colour.
 *
 * This function only works for sequences using `\\e[4Nm`, `\\e[10Nm` or `\\e[48;[25];...m` background escape codes.
 *
 * It shouldn't have any false negatives, but it will have false positives on inputs like:
 *  `\\e[38;5;105m` or `\\e[38;2;250;40;125m`
 *
 * @param colour[in] The ANSI escape sequence to check.
 * @return true if `colour` will set the background colour, false otherwise.
 */
static inline bool doesSetBackground(const char *colour) {
	for (int i = 0; i < (int) strlen(colour); i++) {
		if ((colour[i	 ] == ';' || colour[i	 ] == '[' ) && (// only look at substrings starting with `;` or '['
			(colour[i + 1] == '4' &&							// look for a `4`
			(colour[i + 2] >= '0' && colour[i + 2] <= '9' ) &&	// with another digit after it
			(colour[i + 3] == ';' || colour[i + 3] == 'm')) ||	// and then end the substring
			// OR
			(colour[i + 1] == '1' &&							// look for		`1`
			(colour[i + 2] == '0' &&							// followed by	`0` (i.e. a `10`)
			(colour[i + 3] >= '0' && colour[i + 3] <= '9')) &&	// followed by a digit
			(colour[i + 4] == ';' || colour[i + 4] == 'm'))		// then and the substring
		)) return true;
	}
	return false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printName(const name_t name, const FileColour *colour, const bool *is_hln, const flag_t *flags, type_t *suffix) {
	const char *file_colour = file_colour_esc[*colour];
	const char *raw_name = GET_NAME(name);

	const bool colour_sets_bg = doesSetBackground(file_colour);
	bool does_have_escape = false;
	name_t escaped_name;

	int read_idx = 0, write_idx = 0;

	while (raw_name[read_idx] != '\0') {
		const char chr = raw_name[read_idx++];
		char esc_seq[48];

		if (!getEscSequence(esc_seq, chr)) {
			escaped_name[write_idx++] = chr;
			continue;
		}

		if (DO_COLOUR()) {
			char temp[48];
			// if the file colour sets the bg, then make the esc seq also uses a bg highlight, and vice versa
			sprintf(temp, "%s%s%s" "%s%s" "%s",
				CSI ";1;", colour_sets_bg ? "4" : "3", ESC_CHAR_COLOUR END,
				esc_seq, RESET,
				file_colour
			);
			strcpy(esc_seq, temp);
		}

		does_have_escape = true;
		const int esc_len = strlen(esc_seq);

		strcpy(escaped_name + write_idx, esc_seq);
		write_idx += esc_len;
	}

	escaped_name[write_idx] = '\0';

	bool do_divider = false;
	char div_char[4] = "";

	const char *DIVIDER_OPTIONS[] = { "─", "—", "–", "-", "_", "•" };
	const int NUM_OPTIONS = (int)(sizeof(DIVIDER_OPTIONS) / sizeof(DIVIDER_OPTIONS[0]));

	if (TRY_DIVIDER()) {
		for (int i = 0; i < NUM_OPTIONS; i++) {
			const char *test_char = DIVIDER_OPTIONS[i];
			char test_divider[4 * 5];

			sprintf(test_divider, "%s%s%s%s%s", test_char, test_char, test_char, test_char, test_char);

			if (strstr(name, test_divider) != NULL) {
				do_divider = true;
				strcpy(div_char, test_char);

				if (*colour == FC_DIRECT) *suffix = '\0';
				break;
			}
		}
	}

	if (DO_COLOUR()) {
		printf("%s" "%s%s" "%s%s" "%s" "%s",
			PRE_NAME_PAD,
			GET_HARDLN_UL(), GET_DIM_HL(),
			file_colour, strcmp(name, CURRENT_DIR) == 0 ? UNDER : "",
			escaped_name,
			(do_divider ? "" : RESET)
		);

	} else {
		printf("%s" "%s", PRE_NAME_PAD, escaped_name);
	}

	if (do_divider) {
		struct winsize window;

		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window) == 0) {
			printf("%s", RMAM);
			for (int i = 0; i < window.ws_col - 2; i++) printf("%s", div_char);
			printf("%s" "%s", (DO_COLOUR() ? RESET : ""), SMAM);
		}
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
