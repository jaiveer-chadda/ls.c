/// @file graphics/print-size.c

#include <stdio.h>
#include <string.h>

#include "../graphics/graphics.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IF_COLOUR(print) DO_COLOUR ? print : ""

#define DO_IGNORE_UNIT(unit) (unit == '\0' || unit == '-' || unit == ',')

static inline void getUnitColour(char *unit_colour, const char unit) {
	if (DO_IGNORE_UNIT(unit)) return;
	switch (unit) {
		case 'k': strcpy(unit_colour, size_colour_esc[SC_Uk]); return;
		case 'M': strcpy(unit_colour, size_colour_esc[SC_Um]); return;
		case 'G': strcpy(unit_colour, size_colour_esc[SC_Ug]); return;
		default	: strcpy(unit_colour, size_colour_esc[SC_Ut]); return;
	}
}

static inline void getValueColour(char *value_colour, const char unit) {
	switch (unit) {
		case '-' : strcpy(value_colour, PUNCT)					; return;
		case '\0': strcpy(value_colour, size_colour_esc[SC_Bb])	; return;
		case 'k' : strcpy(value_colour, size_colour_esc[SC_Bk])	; return;
		case 'M' : strcpy(value_colour, size_colour_esc[SC_Bm])	; return;
		case 'G' : strcpy(value_colour, size_colour_esc[SC_Bg])	; return;
		default	 : strcpy(value_colour, size_colour_esc[SC_Bt])	; return;
	}
}

static inline void getMajMinString(char *majmin_str, const sizestr size_str) {
	char minor_size[strlen(size_str)-2];
	int i = 0;

	// copy all of `size_str` to `majmin_str` until the first comma
	while (i < __INT_MAX__) {
		if (size_str[i] == ',') break;
		minor_size[i] = size_str[i];
		i++;
	}

	sprintf(majmin_str,
		"%s"	// maj colour
		"%s"	// maj size
		"%s"	// comma (and min colour)
		"%s",	// min size

		IF_COLOUR(MAJ_COL),
		minor_size,
		IF_COLOUR(PUNCT "," MIN_COL),
		size_str + i + 1
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printSize(const sizestr size_str, const char unit) {
	if (!do_size_str) return;

	const int field_len	= (int)field_lengths.size_str;
	const int str_len	= (int)strlen(size_str);
	const int spaces	= (DO_IGNORE_UNIT(unit) ? 1 : 0) + ((field_len - 1) - str_len);

	char value_colour[16] = "", unit_colour[16] = "";
	char majmin_str[32] = "";

	if (unit == ',') getMajMinString(majmin_str, size_str);
	else getValueColour(value_colour, unit);

	getUnitColour(unit_colour, unit);

	printf(
		"%*s"	// spaces and their length
		"%s"	// value colour
		"%s"	// value
		"%s",	// unit colour

		spaces, "",
		IF_COLOUR(value_colour),
		unit == ',' ? majmin_str : size_str,
		IF_COLOUR(unit_colour)
	);

	if (!DO_IGNORE_UNIT(unit)) putchar(unit);
	printf("%s" FIELD_PAD, IF_COLOUR(RESET));

}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
