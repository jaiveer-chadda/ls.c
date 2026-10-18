/// @file output/escape-name.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "strbuilder.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// How much memory we should allocate for each name, if we don't know the length of the original name.
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

/* —— getHOME() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char *getHOME(size_t *const size) {
	static const char *HOME = NULL;
	static size_t home_size = 0;

	// if we don't have a value for `$HOME` stored in the cache...
	if (HOME == NULL) {
		HOME = getenv("HOME");
		if (HOME != NULL) home_size = strlen(HOME);
	}

	if (size != NULL) *size = home_size;
	return HOME;
}

/* —— printEscdName() —————————————————————————————————————————————————————————————————————————————————————————————— */

// note: I can't use `do/while` for this, since it has a `continue` statement in it
#define CHECK_HOME_MATCH()															\
	/* if there's still a chance that we can match `$HOME` */						\
	if (ABBR_PATHS() && match_home) {												\
		/* increment the pointer. if it doesn't match input, then we've failed */	\
		if (*home_ptr++ != *inp_ptr) match_home = false;							\
		/* if, however, the pointer is at '\0', then we know we've found `$HOME`*/	\
		/*	however, only match `$HOME` if it doesn't exactly match `name` */		\
		if (*home_ptr == '\0' && *inp_ptr != '\0' && *(inp_ptr + 1) != '\0') {		\
			/* if so, clear the string up to the beginning of the padding/colour */	\
			sb_delete(path_str, sb_length(path_str) - pre_path_len);				\
			/* add `~`, ignore the current char, and move on to the next char */	\
			sb_addchr(path_str, '~');												\
			inp_ptr++;																\
			continue;																\
		}																			\
	}

/* ———————————————————————————————————————————————————————————— */

void printEscdName(const char *const name, const Colour colour, const bool do_padding) {

	/* —— Setup ——————————————————————————————————————————————— */

	const Colour esc_colour = has_bg(colour) ? ESC_CHAR_BG_COLOUR : ESC_CHAR_FG_COLOUR;
	StringBuilder path_str = sb_init(INIT_ALLOC_LEN);

	/* —— Add Padding & Colour ———————————————————————————————— */

	/** The length we should revert back to if we find & replace `$HOME`. */
	size_t pre_path_len = 0;

	// if we add the padding to the output buffer, we can use `fputs`, rather than `printf` when printing
	if (do_padding) pre_path_len += sb_addlit(path_str, PRE_NAME_PAD);

	// add the file's colour to the start of the output sequence
	if (!DO_ANY_ESC(name[0])) pre_path_len += sb_addcol(path_str, colour);

	/* —— Escape & Add Each Char —————————————————————————————— */

	// only get `$HOME` if we're actually going to use it
	const char *const HOME = ABBR_PATHS() ? getHOME(NULL) : "";
	bool match_home = true; /** Whether or not we're still trying to match `$HOME`. */

	char esc_buf[4] = {0}; // 4 is the maximum length of a character's escape sequence (`\x7F`)
	uint8_t	esc_len = 0;

	const char *inp_ptr = name;
	const char *home_ptr = HOME;

	/* ———————————————————————————————————————————————————————— */

	while (*inp_ptr != '\0') {

		// if the current char needs to be escaped
		if (DO_ANY_ESC(*inp_ptr)) {
			// add the escape sequence colour
			sb_addcol(path_str, esc_colour);

			// iterate through all subsequent escpae characters, printing them one by one
			//	printing them in sequence like this, prevents us from having to print a new
			//	colour for each character every time
			while (DO_ANY_ESC(*inp_ptr)) {
				CHECK_HOME_MATCH();

				esc_len = escapeCharacter(esc_buf, *inp_ptr++);
				sb_addstr(path_str, esc_buf, esc_len);
			}

		} else { // if the current char _doesn't_ need to be escaped
			// if we're not on the first char, add the file's colour to the output
			if (inp_ptr != name) sb_addcol(path_str, colour);

			while (*inp_ptr != '\0' && !DO_ANY_ESC(*inp_ptr)) {
				CHECK_HOME_MATCH();
				sb_addchr(path_str, *inp_ptr++);
			}
		}
	}

	/* —— Print, Free, & Cleanup —————————————————————————————— */

	sb_putsf(path_str);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
