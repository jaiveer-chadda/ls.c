/// @file output/escape-name.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "../info/info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

#include "output.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_NAME(name)	(strcmp((name), DOTDIR) == 0 ? G_DOTDIR_PATH : (name))

#define DO_OCT_ESC(chr) (0 <= (chr) && (chr) <= 7)
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127)

typedef unsigned char u_char;
typedef unsigned int  u_int;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static bool escapeCharacter(char *esc_seq, const char orig_char) {
	const u_char chr = (u_char)orig_char;
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
		default		: break;
	}

	if DO_OCT_ESC(chr) { sprintf(esc_seq, "\\%u", (u_int)chr); return true; }
	if DO_HEX_ESC(chr) { sprintf(esc_seq, "\\x%02X",	 chr); return true; }

	return false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define   CHAR(n) (colour[i + (n)])
#define IS_DIG(n) (CHAR(n) >= '0' && CHAR(n) <= '9')
#define IS_END(n) (CHAR(n) == ';' || i + (n) == len)

/**
 * @brief Checks whether an ANSI escape sequence, when used, sets the background colour.
 *
 * This function only works for sequences using `\\e[4Nm`, `\\e[10Nm` or `\\e[48;[25];...m` background escape codes.
 *
 * It shouldn't have any false negatives, but it will have false positives on inputs like:
 *  `\\e[38;5;105m` or `\\e[38;2;250;40;125m`
 *
 * @param colour[in] The ANSI escape sequence to check, without the leading `\\e` or trailing `m`.
 * @return true if `colour` will set the background colour, false otherwise.
 */
static bool doesSetBackground(const char *colour) {
	const int start_at = colour[0] == ';' ? 1 : 0;
	const int len = (int)strlen(colour);

	for (int i = start_at; i < len; i++) {
		if (i == start_at || CHAR(0) == ';') {
			if (CHAR(1) == '4'					 && IS_DIG(2) && IS_END(3)) return true;
			if (CHAR(1) == '1' && CHAR(2) == '0' && IS_DIG(3) && IS_END(4)) return true;
		}
	}
	return false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool escapeName(char *escaped_name, const name_t orig_name, const char *colour_escape) {
	const char *raw_name = GET_NAME(orig_name);
	const bool colour_sets_bg = doesSetBackground(colour_escape);
	bool did_do_escape = false;

	int read_idx = 0, write_idx = 0;

	while (raw_name[read_idx] != '\0') {
		const char chr = raw_name[read_idx++];
		char esc_seq[48];

		if (!escapeCharacter(esc_seq, chr)) {
			escaped_name[write_idx++] = chr;
			continue;
		}

		if (DO_COLOUR()) {
			char temp[48];
			// if the file colour sets the bg, then make the esc seq also uses a bg highlight, and vice versa
			sprintf(temp, "%s%s%s" "%s%s" "%s%s%s",
				CSI ";1;", colour_sets_bg ? "4" : "3", ESC_CHAR_COLOUR END,
				esc_seq, RESET,
				CSI, colour_escape, END
			);
			strcpy(esc_seq, temp);
		}

		did_do_escape = true;
		const int esc_len = (int)strlen(esc_seq);

		strcpy(escaped_name + write_idx, esc_seq);
		write_idx += esc_len;
	}

	escaped_name[write_idx] = '\0';
	return did_do_escape;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
