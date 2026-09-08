/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_OCT_ESC(chr) ( 0 < (chr) && (chr) <= 7 )
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define copy_and_return(fmt, src) \
	return sprintf(esc, ("%s\\" fmt "%s"), IFCOLOUR(char_ansi), (src), IFCOLOUR(file_ansi))

/**
 * @brief Find the appropriate escape sequence for an inputted character.
 *
 * @param esc_seq[out] The escape sequence to represent the escaped character.
 * @param orig_char[in] The character to be escaped.
 * @return `true` if the inputted character was escaped, `false` otherwise.
 */
static inline uint8_t escapeCharacter(
	char *esc, const char inp,
	const char *const file_ansi,
	const char *const char_ansi
) {
	switch (inp) {
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

	if DO_OCT_ESC(inp) copy_and_return("%hu"  , (uint8_t)inp);
	if DO_HEX_ESC(inp) copy_and_return("x%02X", (uint8_t)inp);

	*esc = inp;
	return 1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printEscapedName(const char *const name, const namlen_t name_len, const Colour colour) {
	// if the colour has a background, use the background escape instead
	const char *const esc_ansi = colour.has_bg() ? ESC_CHAR_BG_ANSI	  : ESC_CHAR_FG_ANSI;
	const Colour	esc_colour = colour.has_bg() ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;

	const Colour save_colour = getActive();
	setActive(esc_colour);

	uint8_t file_ansi_len = 0;
	const char *const file_ansi = getcol_ns_len(colour, &file_ansi_len);
	setActive(save_colour);

	// the exact size is temporary for now - it'll be determined dynamically later
	char *const output = emalloc(name_len + 1024);
	char *out_ptr = output;

	memcpy(out_ptr, file_ansi, file_ansi_len);
	out_ptr += file_ansi_len;

	for (const char *inp_ptr = name; *inp_ptr != '\0'; inp_ptr++) {
		out_ptr += escapeCharacter(out_ptr, *inp_ptr, file_ansi, esc_ansi);
	}

	if (DO_COLOUR()) memcpy(out_ptr, RESET, sizeof(RESET));

	printf("%s%s", PRE_NAME_PAD, output);

	setActive(RESET_ALL);
	efree(output);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
