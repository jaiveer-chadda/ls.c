/// @file output/print-size.c

#include <stdio.h>
#include <string.h>

#include "../form/formatting.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IF_COLOUR(yes, no) (DO_COLOUR() ? (yes) : (no))
#define DO_IGNORE_UNIT(unit) ((unit) == UNIT_BYTE || (unit) == UNIT_ZERO || (unit) == UNIT_MAJ_MIN)

#define SET_COLOUR(type, code) sprintf(type ## _colour, "%s%s%s", CSI, size_colour_esc[SC_ ## code], END)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getUnitColour(char *unit_colour, const char *unit) {
	if (DO_IGNORE_UNIT(*unit)) return;

	switch (*unit) {
		case UNIT_KILO: SET_COLOUR(unit, UK); return;
		case UNIT_MEGA: SET_COLOUR(unit, UM); return;
		case UNIT_GIGA: SET_COLOUR(unit, UG); return;
		default		  : SET_COLOUR(unit, UT);
	}
}

static void getValueColour(char *value_colour, const char *unit) {
	switch (*unit) {
		case UNIT_ZERO: sprintf(value_colour, "%s%s%s", CSI, PUNCT, END); return;
		case UNIT_BYTE: SET_COLOUR(value, BB); return;
		case UNIT_KILO: SET_COLOUR(value, BK); return;
		case UNIT_MEGA: SET_COLOUR(value, BM); return;
		case UNIT_GIGA: SET_COLOUR(value, BG); return;
		default		  : SET_COLOUR(value, BT);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getMajMinString(char *majmin_str, const sizestr size_str) {
	char minor_size[strlen(size_str) - 2];
	int i = 0;

	// copy everything in `size_str` to `majmin_str`, until the first comma
	while (i < __INT_MAX__) { // __INT_MAX__ is being used here as an upper bound, so it doesn't loop forever
		if (size_str[i] == UNIT_MAJ_MIN) break;
		minor_size[i] = size_str[i];
		i++;
	}

	sprintf(majmin_str,
		"%s"	// maj colour
		"%s"	// maj size
		"%s"	// comma (and min colour)
		"%s",	// min size

		IF_COLOUR(ANSI(MAJ_COL), NO_COLOUR),
		minor_size,
		IF_COLOUR(ANSI(PUNCT) "," ANSI(MIN_COL), ","),
		size_str + i + 1
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printSizeStr(const sizestr size_str, const char *unit, const mode_t *mode) {
	if (!do_size_str()) return;

	const int field_len	= (int)field_lengths.size_str;
	const int str_len	= (int)strlen(size_str);
	const int spaces	= field_len - 1 - str_len + (DO_IGNORE_UNIT(*unit) ? 1 : 0);

	char value_colour[16] = "", unit_colour[16] = "";
	char majmin_str[32] = "";

	if (*unit == UNIT_MAJ_MIN)	getMajMinString(majmin_str, size_str);
	else						getValueColour(value_colour, unit);

	getUnitColour(unit_colour, unit);

	printf(
		"%*s"	// spaces and their length
		"%s"	// value colour
		"%s"	// dim
		"%s"	// value
		"%s",	// unit colour

		spaces, "",
		IF_COLOUR(value_colour, NO_COLOUR),

		IF_COLOUR(S_ISDIR(*mode) ? ANSI(DIM) : NO_COLOUR, NO_COLOUR),
		*unit == UNIT_MAJ_MIN ? majmin_str : size_str,
		IF_COLOUR(unit_colour, NO_COLOUR)
	);

	if (!DO_IGNORE_UNIT(*unit)) putchar(*unit);
	printf("%s" FIELD_PAD, IF_COLOUR(RESET, NO_COLOUR));

}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
