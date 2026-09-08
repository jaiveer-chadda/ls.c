/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_OCT_ESC(chr) ( 0 < (chr) && (chr) <= 7 ) /** 1 → 7 */
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127) /** 8 → 31, 127 */

/** 1 → 31, 92, 127 */
#define DO_ANY_ESC(chr) \
	(DO_OCT_ESC(chr) || DO_HEX_ESC(chr) || (chr) == '\\')

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define copy_and_return(fmt, src) \
	return sprintf(esc, ("%s\\" fmt), IFCOLOUR(last_was_esc ? "" : chr_ansi), (src));

/**
 * @brief Find the appropriate escape sequence for an inputted character.
 *
 * @param esc_seq[out] The escape sequence to represent the escaped character.
 * @param orig_char[in] The character to be escaped.
 * @return `true` if the inputted character was escaped, `false` otherwise.
 */
static inline uint8_t escapeCharacter(char *esc, const char chr, const char *const chr_ansi, const bool last_was_esc) {
	switch (chr) {
		case '\\' : copy_and_return("%c", '\\');
		case '\a' : copy_and_return("%c", 'a' );
		case '\b' : copy_and_return("%c", 'b' );
		case '\t' : copy_and_return("%c", 't' );
		case '\n' : copy_and_return("%c", 'n' );
		case '\v' : copy_and_return("%c", 'v' );
		case '\f' : copy_and_return("%c", 'f' );
		case '\r' : copy_and_return("%c", 'r' );
		case '\33': copy_and_return("%c", 'e' );
		default	  : break;
	}

	if DO_OCT_ESC(chr) copy_and_return("%hu"  , (uint8_t)chr);
	if DO_HEX_ESC(chr) copy_and_return("x%02X", (uint8_t)chr);

	// nothing to escape
	*esc = chr;
	return 1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/** Whether the last character parsed was an escaped character or not. */
#define LAST_WAS_ESC() ((inp_ptr != name) && DO_ANY_ESC(*(inp_ptr - 1)))

void printEscdName(const char *const name, const namlen_t name_len, const Colour colour) {
	const Colour active_col = getActive();
	const Colour esc_colour = colour.has_bg() ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;
	const char *const esc_ansi = colour.has_bg() ? ESC_CHAR_BG_ANSI : ESC_CHAR_FG_ANSI;

	uint8_t init_ansi_len, file_ansi_len;

	char *initcol_ptr = getcol_ns_len(colour, &init_ansi_len);
	char init_ansi[MAX_ANSI_SIZE];
	memcpy(init_ansi, initcol_ptr, init_ansi_len + 1);

	// make `getcol` think that it's printing after an escape sequence, and see what it returns
	setActive(esc_colour);
	const char *const file_ansi = getcol_ns_len(colour, &file_ansi_len);
	setActive(active_col);

	// allocate memory for the output, and setup the output pointer
	/// @todo implement dynamic allocation
	char *const output = emalloc(name_len + 1024);
	char *out_ptr = output;

	// if the file's colour is already active, or the first character in the name will have an escape anyways
	//	then add it to the start of the output sequence
	if (!(areEqual(colour, active_col) || DO_ANY_ESC(name[0]))) {
		memcpy(out_ptr, init_ansi, init_ansi_len + 1);
		out_ptr += init_ansi_len;
	}

	const char *inp_ptr;
	for (inp_ptr = name; *inp_ptr != '\0'; inp_ptr++) {
		// if the last char was escaped, but this one won't be, then re-activate the file's colour
		if (LAST_WAS_ESC() && !DO_ANY_ESC(*inp_ptr)) {
			memcpy(out_ptr, file_ansi, file_ansi_len);
			out_ptr += file_ansi_len;
		}
		out_ptr += escapeCharacter(out_ptr, *inp_ptr, esc_ansi, LAST_WAS_ESC());
	}

	*out_ptr = '\0';

	printf("%s%s", PRE_NAME_PAD, output);
	efree(output);

	setActive(LAST_WAS_ESC() ? esc_colour : colour);
	return;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
