/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "options/options.h"
#include "graphics/graphics.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_OCT_ESC(chr) ( 0 < (chr) && (chr) <= 7 ) /** 1 → 7 */
#define DO_HEX_ESC(chr) ((7 < (chr) && (chr) <= 31) || (chr) == 127) /** 8 → 31, 127 */

/** 1 → 31, 92, 127 */
#define DO_ANY_ESC(chr) \
	(DO_OCT_ESC(chr) || DO_HEX_ESC(chr) || (chr) == '\\')

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define copy_and_return(fmt, src) do { \
	if (last_was_esc) { \
		return sprintf(esc, ("\\" fmt), (src)); \
	} else { \
		return sprintf(esc, ("%s\\" fmt /* "%s" */), IFCOLOUR(char_ansi), (src)/* , IFCOLOUR(file_ansi) */); \
	} \
} while (0)

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
	const char *const char_ansi,
	const bool last_was_esc
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

	/* —————————————————————————————————————————————————————————————————— */
	// nothing to escape

	*esc = inp;
	return 1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printEscdName(const char *const name, const namlen_t name_len, const Colour colour) {
	(void)name; (void)name_len; (void)colour;

	/*
	 * if
	 * 
	 */

	/* —————————————————————————————————————————————————————————————————— */

	fputs(PRE_NAME_PAD, stdout);

	const char *const esc_ansi = colour.has_bg() ? ESC_CHAR_BG_ANSI : ESC_CHAR_FG_ANSI;
	const Colour esc_colour = colour.has_bg() ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;
	const Colour prev_active_col = getActive();

	uint8_t init_ansi_len, file_ansi_len;

	char *getcol_ptr = getcol_ns_len(colour, &init_ansi_len);
	char init_ansi[MAX_ANSI_SIZE];
	memcpy(init_ansi, getcol_ptr, init_ansi_len + 1);

	// make `getcol` think that it's printing after an escape sequence, and see what it returns
	setActive(esc_colour);
	const char *const file_ansi = getcol_ns_len(colour, &file_ansi_len);
	setActive(prev_active_col);

	// allocate memory for the output, and setup the output pointer
	char *const output = emalloc(name_len + 1024);
	char *out_ptr = output;

	// if the file's colour is already the one that's active, then we don't have to print anything
	//	otherwise, add the file's colour to the start of the output sequence

	if (!areEqual(colour, prev_active_col) && !DO_ANY_ESC(name[0])) {
		memcpy(out_ptr, init_ansi, init_ansi_len + 1);
		out_ptr += init_ansi_len;
	} else {
		// fputs("<s>", stdout); // (same)
	}

	uint8_t esc_len = 0;
	bool last_was_esc = false, did_esc = false, is_first;
	(void)did_esc;

	const char *inp_ptr;

	for (inp_ptr = name; *inp_ptr != '\0'; inp_ptr++) {

		out_ptr += ( esc_len = escapeCharacter(out_ptr, *inp_ptr, file_ansi, esc_ansi, DO_ANY_ESC(*(inp_ptr - 1))) );

		// if this char was escaped, but the next one won't be
		if (DO_ANY_ESC(*inp_ptr) && !DO_ANY_ESC(*(inp_ptr + 1)) && *(inp_ptr + 1) != '\0') {
			memcpy(out_ptr, file_ansi, file_ansi_len);
			out_ptr += file_ansi_len;
		}
	}

	*out_ptr = '\0';

	fputs(output, stdout);
	// printf("<|>");

	if (DO_ANY_ESC(*(inp_ptr - 1))) {
		setActive(esc_colour);
	} else {
		setActive(colour);
	}

	// Colour temp = getActive();

	// setActive(RESET_ALL);
	// printf(" << act = %s >> ", getcol(temp));

	efree(output);
	return;

	/* —————————————————————————————————————————————————————————————————— */
	/* —————————————————————————————————————————————————————————————————— */


	// const Colour save_colour = getActive();
	// setActive(colour.has_bg() ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR);

	// uint8_t file_ansi_len = 0;
	// const char *const file_ansi = getcol_ns_len(colour, &file_ansi_len);
	// setActive(save_colour);

	// // the exact size is temporary for now - it'll be determined dynamically later
	// char *const output = emalloc(name_len + 1024);
	// char *out_ptr = output;

	// memcpy(out_ptr, file_ansi, file_ansi_len);
	// out_ptr += file_ansi_len;

	// for (const char *inp_ptr = name; *inp_ptr != '\0'; inp_ptr++) {
	// 	out_ptr += escapeCharacter(out_ptr, *inp_ptr, file_ansi, esc_ansi);
	// }

	// if (DO_COLOUR()) memcpy(out_ptr, RESET, sizeof(RESET));

	// printf("%s%s", PRE_NAME_PAD, output);

	// setActive(RESET_ALL);
	// efree(output);
}

#pragma clang diagnostic pop

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
