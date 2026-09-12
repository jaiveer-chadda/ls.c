/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// How much memory we should allocate for each name, if we don't know the length of the original name
#define INIT_ALLOC_LEN 16

/// Approximately multiplies a number by 1.5
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

/* ———————————————————————————————————————————————————————— */

#define DO_OCT_ESC(chr) ( 0 < (chr) && (chr) <= 7 ) /** 1 → 7 */
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127) /** 8 → 31, 127 */

/** 1 → 31, 92, 127 */
#define DO_ANY_ESC(chr) \
	(DO_OCT_ESC(chr) || DO_HEX_ESC(chr) || (chr) == '\\')

/* —— escapeCharacter() ———————————————————————————————————————————————————————————————————————————————————————————— */

#define copy_and_return(fmt, src) \
	return sprintf(esc, ("%s\\" fmt), IFCOLOUR(last_was_esc ? "" : chr_ansi), (src));

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
static inline uint8_t escapeCharacter(char *esc, const char chr, const char *const chr_ansi, const bool last_was_esc) {
	// if a character has a pre-defined escape sequence, print it
	switch (chr) {
		// note: backslashes are being escaped to eliminate ambiguity when not printing in colour
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

	*esc = chr;	// nothing to escape - push the inputted char back onto the buffer
	return 1;	// length = 1
}

/* —— printEscdName() —————————————————————————————————————————————————————————————————————————————————————————————— */

/** Whether the last character parsed was an escaped character or not. */
#define LAST_WAS_ESC() ((inp_ptr != name) && DO_ANY_ESC(*(inp_ptr - 1)))

void printEscdName(const char *const name, const Colour colour) {

	/* —— Colour Constants ———————————————————————————————————— */

	/// The colour that was being displayed before this function was called.
	const Colour active_col = getActive();
	/// A `Colour` object representing the colour with which to highlight escaped characters.
	const Colour esc_colour = has_bg(colour) ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;
	/// The raw ANSI string representing the colour with which to highlight escaped characters.
	const char *const esc_ansi = has_bg(colour) ? ESC_CHAR_BG_ANSI : ESC_CHAR_FG_ANSI;
	/// The length of the string stored in `esc_ansi`. 
	const size_t esc_ansi_len = sizeof(has_bg(colour) ? ESC_CHAR_BG_ANSI : ESC_CHAR_FG_ANSI) - 1;

	/* —— Colour Setup ———————————————————————————————————————— */

	uint8_t init_ansi_len, file_ansi_len;
	const char *initcol_ptr;
	ansi_t init_ansi;

	// if the file's colour is different to the active colour, and the first char in the name isn't escaped,
	//	then print some colour before the name
	const bool do_init_col = (!(areEqual(colour, active_col) || DO_ANY_ESC(name[0])));

	if (do_init_col) {
		// since `getcol` returns the same pointer every time, we need to copy this ansi escape into a
		//	buffer before we process anything else
		initcol_ptr = getcol_ns_len(colour, &init_ansi_len);
		memcpy(init_ansi, initcol_ptr, init_ansi_len);
	}

	// make `getcol` think that it's printing after the escape character colour, and see what it returns
	//	this will, naturally, be the sequence that's printed after an escape character
	setActive(esc_colour);
	const char *const file_ansi = getcol_ns_len(colour, &file_ansi_len);

	/* —— Alloc & Ouput Setup ————————————————————————————————— */

	size_t alloc_size = INIT_ALLOC_LEN + sizeof(PRE_NAME_PAD) + (do_init_col ? init_ansi_len : 0);
	#define output_size ((size_t)(out_ptr - output))

	// allocate memory for the output, and setup the output pointer
	char *output = emalloc(alloc_size);
	char *out_ptr = output;

	/* —— Add Padding & Colour ———————————————————————————————— */

	// if we add the padding to the output buffer, we can use `fputs`, rather than `printf` when printing
	memcpy(out_ptr, PRE_NAME_PAD, sizeof(PRE_NAME_PAD) - 1);
	out_ptr += sizeof(PRE_NAME_PAD) - 1;

	if (do_init_col) {
		// add the file's colour to the start of the output sequence
		memcpy(out_ptr, init_ansi, init_ansi_len);
		out_ptr += init_ansi_len;
	}

	/* —— Escape & Add Each Char —————————————————————————————— */

	/// The maximum that `output_size` can increase by each loop (+1 so we don't have to realloc before the nullbyte).
	const size_t max_increase = esc_ansi_len + file_ansi_len + 4 + 1;

	const char *inp_ptr;
	for (inp_ptr = name; *inp_ptr != '\0'; inp_ptr++) {
		if (output_size + max_increase > alloc_size) {
			// make sure we'll have enough allocated memory
			while (alloc_size < output_size + max_increase) MULT_BY_1_5(alloc_size);

			// note down how much memory we've written to `output` already
			const size_t size = output_size;
			output = erealloc(output, alloc_size);
			// move the output pointer to the new location of `output`
			out_ptr = output + size;
		}

		// if the last char was escaped, but this one won't be, then re-activate the file's colour
		if (LAST_WAS_ESC() && !DO_ANY_ESC(*inp_ptr)) {
			memcpy(out_ptr, file_ansi, file_ansi_len);
			out_ptr += file_ansi_len;
		}

		// escape the character, and move the output pointer along by its length
		out_ptr += escapeCharacter(out_ptr, *inp_ptr, esc_ansi, LAST_WAS_ESC());
	}

	*out_ptr = '\0';

	/* —— Print, Free, & Cleanup —————————————————————————————— */

	fputs(output, stdout);
	efree(output);

	// let `getcol` know what the last colour used was
	setActive(LAST_WAS_ESC() ? esc_colour : colour);
	return;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
