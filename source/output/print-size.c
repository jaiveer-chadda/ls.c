/// @file output/print-size.c

#include <stdio.h>
#include <string.h>

#include "../form/formatting.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IF_COLOUR(yes, no) (DO_COLOUR() ? (yes) : (no))
#define DO_IGNORE_UNIT(unit) ((unit) == UNIT_BYTE || (unit) == UNIT_ZERO || (unit) == UNIT_MAJ_MIN)

static inline void getUnitColour(char *unit_colour, const char *unit) {
	if (DO_IGNORE_UNIT(*unit)) return;
	switch (*unit) {
		case UNIT_KILO: sprintf(unit_colour, "%s%s%s", CSI, size_colour_esc[SC_UK], END); return;
		case UNIT_MEGA: sprintf(unit_colour, "%s%s%s", CSI, size_colour_esc[SC_UM], END); return;
		case UNIT_GIGA: sprintf(unit_colour, "%s%s%s", CSI, size_colour_esc[SC_UG], END); return;
		default		  : sprintf(unit_colour, "%s%s%s", CSI, size_colour_esc[SC_UT], END); return;
	}
}

static inline void getValueColour(char *value_colour, const char *unit) {
	switch (*unit) {
		case UNIT_ZERO: sprintf(value_colour, "%s%s%s", CSI, PUNCT				, END); return;
		case UNIT_BYTE: sprintf(value_colour, "%s%s%s", CSI, size_colour_esc[SC_BB]	, END); return;
		case UNIT_KILO: sprintf(value_colour, "%s%s%s", CSI, size_colour_esc[SC_BK]	, END); return;
		case UNIT_MEGA: sprintf(value_colour, "%s%s%s", CSI, size_colour_esc[SC_BM]	, END); return;
		case UNIT_GIGA: sprintf(value_colour, "%s%s%s", CSI, size_colour_esc[SC_BG]	, END); return;
		default		  : sprintf(value_colour, "%s%s%s", CSI, size_colour_esc[SC_BT]	, END); return;
	}
}

static inline void getMajMinString(char *majmin_str, const sizestr size_str) {
	char minor_size[strlen(size_str) - 2];
	int i = 0;

	// copy everyting in `size_str` to `majmin_str`, until the first comma
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

		IF_COLOUR(ANSI(MAJ_COL), ""),
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
	const int spaces	= ((field_len - 1) - str_len) + (DO_IGNORE_UNIT(*unit) ? 1 : 0);

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
		IF_COLOUR(value_colour, ""),
		IF_COLOUR(S_ISDIR(*mode) ? ANSI(DIM) : "", ""),
		*unit == UNIT_MAJ_MIN ? majmin_str : size_str,
		DO_COLOUR() ? unit_colour : ""
	);

	if (!DO_IGNORE_UNIT(*unit)) putchar(*unit);
	printf("%s" FIELD_PAD, IF_COLOUR(RESET, ""));

}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
