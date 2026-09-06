/// @file output/escape-name.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "options/options.h"
#include "graphics/graphics.h"

#include "output.h"
#include "debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_OCT_ESC(chr) ( 0 < (chr) && (chr) <= 7 )
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define copy_and_return(dst, src) memcpy((dst), (src), sizeof(src)); return (sizeof(src) - 1)

/**
 * @brief Find the appropriate escape sequence for an inputted character.
 *
 * @param esc_seq[out] The escape sequence to represent the escaped character.
 * @param orig_char[in] The character to be escaped.
 * @return `true` if the inputted character was escaped, `false` otherwise.
 */
static inline bool escapeCharacter(char *esc, const char inp) {
	switch (inp) {
		case '\\'	: copy_and_return(esc, "\\\\");
		case '\a'	: copy_and_return(esc, "\\a" );
		case '\b'	: copy_and_return(esc, "\\b" );
		case '\t'	: copy_and_return(esc, "\\t" );
		case '\n'	: copy_and_return(esc, "\\n" );
		case '\v'	: copy_and_return(esc, "\\v" );
		case '\f'	: copy_and_return(esc, "\\f" );
		case '\r'	: copy_and_return(esc, "\\r" );
		case '\x1b'	: copy_and_return(esc, "\\e" );
		default		: break;
	}

	if DO_OCT_ESC(inp) return sprintf(esc, "\\%hu"  , (uint8_t)inp);
	if DO_HEX_ESC(inp) return sprintf(esc, "\\x%02X", (uint8_t)inp);

	*esc = inp;
	return 1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void escapeName(char *const output, const char *const input, const namlen_t inp_len, const Colour colour) {
	assert(input != NULL && output != NULL);
	(void)colour;

	const char *inp_ptr; char *out_ptr;

	for (inp_ptr = input, out_ptr = output; inp_ptr < input + inp_len; inp_ptr++) {
		out_ptr += escapeCharacter(out_ptr, *inp_ptr);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
