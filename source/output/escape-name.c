/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "strbuilder.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// How much memory we should allocate for each name, if we don't know the length of the original name
#define INIT_ALLOC_LEN 16

/* ———————————————————————————————————————————————————————————— */

#define DO_OCT_ESC(chr) ( 0 < (chr) && (chr) <= 7 ) /** 1 → 7 */
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127) /** 8 → 31, 127 */

/** 1 → 31, 92, 127 */
#define DO_ANY_ESC(chr) \
	(DO_OCT_ESC(chr) || DO_HEX_ESC(chr) || (chr) == '\\')

/* —— escapeCharacter() ———————————————————————————————————————————————————————————————————————————————————————————— */

#define return_esc(c) {			 \
	esc[0] = '\\', esc[1] = (c); \
	return 2;					 \
}

/**
 * @brief Find the appropriate escape sequence for an inputted character.
 *
 * @param esc[out]			The buffer to which the escape sequence should be written.
 * @param chr[in]			The character to be escaped.
 * @param chr_ansi[in]		The colour which which the escaped character should be highlighted.
 * @param last_was_esc[in]	Whether the last character written by this function was escaped or not.
 *
 * @return uint8_t: The number of bytes written.
 *		Note that the maximum number of bytes that can be written by this function is:
 *			`[strlen("\x7F") = 4] + strlen(chr_ansi)`
 */
static inline uint8_t escapeCharacter(char *esc, const char chr) {
	// if a character has a pre-defined escape sequence, print it
	switch (chr) {
		// note: backslashes are being escaped to eliminate ambiguity when not printing in colour
		case '\\' : return_esc('\\'	);
		case '\a' : return_esc(	'a'	);
		case '\b' : return_esc(	'b'	);
		case '\t' : return_esc(	't'	);
		case '\n' : return_esc(	'n'	);
		case '\v' : return_esc(	'v'	);
		case '\f' : return_esc(	'f'	);
		case '\r' : return_esc(	'r'	);
		case '\33': return_esc(	'e'	);
		default	  : break;
	}

	if DO_OCT_ESC(chr) return sprintf(esc, "\\%hu"	, chr);
	if DO_HEX_ESC(chr) return sprintf(esc, "\\x%02X", chr);

	*esc = chr;	// nothing to escape - push the inputted char back onto the buffer
	return 1;	// length = 1
}

/* —— printEscdName() —————————————————————————————————————————————————————————————————————————————————————————————— */

#define output_size ((size_t)(out_ptr - output))

#define CHECK_MEM_ALLOC(max_increase) do {											\
	if (output_size + (max_increase) + 1 <= alloc_size) break;						\
	/* make sure we'll have enough allocated memory */								\
	while (alloc_size < output_size + (max_increase) + 1) MULT_BY_1_5(alloc_size);	\
	/* note down how much memory we've written to `output` already */				\
	const size_t size = output_size;												\
	output = erealloc(output, alloc_size);											\
	/* move the output pointer to the new location of `output` */					\
	out_ptr = output + size;														\
} while (0)

/* ———————————————————————————————————————————————————————————— */

void printEscdName(const char *const name, const Colour colour, const bool do_padding) {

	/* —— Colour Setup ———————————————————————————————————————— */

	// if the file's colour is different to the active colour, and the first char in the name isn't escaped,
	//	then print some colour before the name
	const bool do_init_col = !areEqual(colour, getActive()) && !DO_ANY_ESC(name[0]);
	const Colour esc_colour = has_bg(colour) ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;

	/* —— Alloc & Ouput Setup ————————————————————————————————— */

	/// @todo refactor this to use a `StringBuilder`
	/// @todo while iterating through the string, keep checking if it matches `$HOME`
	///			if it does, then replace `/Users/name` with `~`

	StringBuilder path_str = sb_init(INIT_ALLOC_LEN);

	/* —— Add Padding & Colour ———————————————————————————————— */

		// if we add the padding to the output buffer, we can use `fputs`, rather than `printf` when printing
	if (do_padding) sb_addlit(path_str, PRE_NAME_PAD);

		// add the file's colour to the start of the output sequence
	if (do_init_col) sb_addcol(path_str, colour);

	/* —— Escape & Add Each Char —————————————————————————————— */

	char esc_buf[4] = {0}; // 4 is the maximum length of a character's escape sequence (`\x7F`)
	uint8_t	esc_len = 0;

	const char *inp_ptr = name;
	while (*inp_ptr != '\0') {
		if (DO_ANY_ESC(*inp_ptr)) {
			sb_addcol(path_str, esc_colour);

			while (DO_ANY_ESC(*inp_ptr)) {
				esc_len = escapeCharacter(esc_buf, *inp_ptr++);
				sb_addstr(path_str, esc_buf, esc_len);
			}

		} else {
			if (inp_ptr != name) sb_addcol(path_str, colour);
			while (*inp_ptr != '\0' && !DO_ANY_ESC(*inp_ptr)) sb_addchr(path_str, *inp_ptr++);
			}
		}

	/* —— Print, Free, & Cleanup —————————————————————————————— */

	sb_putsf(path_str);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
