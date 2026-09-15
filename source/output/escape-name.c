/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
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

#define copy_and_return(fmt, src) \
	return sprintf(esc, ("\\" fmt), (src));

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

	uint8_t init_ansi_len = 0, esc_ansi_len, file_ansi_len;

	// if the file's colour is different to the active colour, and the first char in the name isn't escaped,
	//	then print some colour before the name
	const bool do_init_col = !areEqual(colour, getActive()) && !DO_ANY_ESC(name[0]);
	const Colour esc_colour = has_bg(colour) ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;

	const char
		*const init_ansi = do_init_col ? getcollen(colour, &init_ansi_len) : NULL,
		*const esc_ansi	 = getcollen(esc_colour, &esc_ansi_len),
		*const file_ansi = getcollen(colour, &file_ansi_len);

	/* —— Alloc & Ouput Setup ————————————————————————————————— */

	size_t alloc_size =
		INIT_ALLOC_LEN
		+ (do_padding  ? sizeof(PRE_NAME_PAD) : 0)
		+ (do_init_col ? init_ansi_len		  : 0);

	// allocate memory for the output, and setup the output pointer
	char *output = emalloc(alloc_size);
	char *out_ptr = output;

	/* —— Add Padding & Colour ———————————————————————————————— */

	if (do_padding) {
		// if we add the padding to the output buffer, we can use `fputs`, rather than `printf` when printing
		memcpy(out_ptr, PRE_NAME_PAD, sizeof(PRE_NAME_PAD) - 1);
		out_ptr += sizeof(PRE_NAME_PAD) - 1;
	}

	if (do_init_col) {
		// add the file's colour to the start of the output sequence
		memcpy(out_ptr, init_ansi, init_ansi_len);
		out_ptr += init_ansi_len;
	}

	/* —— Escape & Add Each Char —————————————————————————————— */

	const char *inp_ptr = name;
	while (*inp_ptr != '\0') {

		if (DO_ANY_ESC(*inp_ptr)) {
			CHECK_MEM_ALLOC(esc_ansi_len);

			memcpy(out_ptr, esc_ansi, esc_ansi_len);
			out_ptr += esc_ansi_len;

			while (DO_ANY_ESC(*inp_ptr)) {
				CHECK_MEM_ALLOC(4); // 4 is the maximum length of a character's escape sequence (`\x7F`)
				out_ptr += escapeCharacter(out_ptr, *inp_ptr++);
			}

		} else {
			if (inp_ptr != name) {
				CHECK_MEM_ALLOC(file_ansi_len);

				memcpy(out_ptr, file_ansi, file_ansi_len);
				out_ptr += file_ansi_len;
			}

			while (*inp_ptr != '\0' && !DO_ANY_ESC(*inp_ptr)) {
				CHECK_MEM_ALLOC(1);
				*out_ptr++ = *inp_ptr++;
			}
		}
	}

	*out_ptr = '\0';

	/* —— Print, Free, & Cleanup —————————————————————————————— */

	fputs(output, stdout);
	efree(output);

	if (inp_ptr != name) setActive(DO_ANY_ESC(*(inp_ptr - 1)) ? esc_colour : colour);
	return;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
