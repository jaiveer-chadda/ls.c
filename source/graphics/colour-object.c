/// @file graphics/colour-object.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "debugging/debugging.h"
#include "colour-object.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define ANSI_OFF_MOD	(+20) /** The modifier that turns (most) ANSI on-codes into off-codes. */
#define ANSI_REG_BRT_MOD (+6) /** The modifier that turns ANSI colour codes from regular to bright. */

#define ANSI_fg_CODE	3 /** The number which regular colour fg codes begin with. E.g. `\e[35m` or `\e[38;5;255m`. */
#define ANSI_bg_CODE	4 /** The number which regular colour fg codes begin with. E.g. `\e[44m` or `\e[48;5;128m`. */

#define ANSI_BLACK		0
#define ANSI_FGBG_OFF	9
#define ANSI_8BIT_SEQ	"8;5;"

#define ANSI_BOLD		1
#define ANSI_DIM		2
#define ANSI_ITALIC		3
#define ANSI_UNDER		4
#define ANSI_BLINK		5
#define ANSI_NOTHING	6
#define ANSI_INVERT		7
#define ANSI_INVIS		8
#define ANSI_STRIKE		9
#define ANSI_DUNDER		21

#define ANSI_NO_BOLD	ANSI_OFF_MOD + ANSI_BOLD
#define ANSI_NO_DIM		ANSI_NO_BOLD
#define ANSI_NO_ITALIC	ANSI_OFF_MOD + ANSI_ITALIC
#define ANSI_NO_UNDER	ANSI_OFF_MOD + ANSI_UNDER
#define ANSI_NO_BLINK	ANSI_OFF_MOD + ANSI_BLINK
#define ANSI_NO_INVERT	ANSI_OFF_MOD + ANSI_INVERT
#define ANSI_NO_INVIS	ANSI_OFF_MOD + ANSI_INVIS
#define ANSI_NO_STRIKE	ANSI_OFF_MOD + ANSI_STRIKE
#define ANSI_NO_DUNDER	ANSI_NO_UNDER

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifndef CSI
#	define CSI "\033["
#	define END "m"
#endif

/**	The number of characters needed to represent every style's reset sequence (usually longer),
 * including a trailing semicolon and null terminator.
 *	- This would be: `"22;23;24;25;27;28;29;\0"`. */
#define STYLE_BUFSIZE 22

/**	The maximum number of characters needed to represent an 8-bit ANSI colour code, including a null terminator.
 *	- This would be: `"38;5;255\0"`. */
#define FGBG_BUFSIZE  9

#define ON	true
#define OFF	false

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define SNPRINTF(str, size, ...) d_snprintf(str, size, __VA_ARGS__)

	/// @brief A version of `snprintf` with bounds-checking, and which prints debugging messages.
	int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...) {
		va_list va_args;
		va_start(va_args, format);

		const int f_retcode = vsnprintf(str, size, format, va_args);
		const int f_errno = errno;
		va_end(va_args);

		if (f_retcode >= size || f_retcode == -1) {
			debug(WARNING, "snprintf(): `char *str`: %s",
				(f_errno != 0) ? strerror(f_errno) : "buffer overflow"
			);
		}
		return f_retcode;
	}
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

/* —————————————————————————————————————————————————————————————————— */

#define SET_FGBG(fgbg, is_8bit, mode, ansi_col) \
	SNPRINTF((fgbg), FGBG_BUFSIZE, ((is_8bit) ? "%d" ANSI_8BIT_SEQ "%hd" : "%d%hd"), (mode), (ansi_col))

#define SIMPLIFY_ANSI(fgbg) do {				\
	const colour_t col	=  (colour.fgbg);		\
	const int code		=  (ANSI_##fgbg##_CODE);\
	int *const len		= &(fgbg##_len);		\
	\
	if		(col == G_NO_FGBG && (active.fgbg) == G_NO_FGBG) *len = 0; /* don't change the fg/bg colour */		\
	else if	(col == G_NO_FGBG)	*len = SET_FGBG(fgbg, false, code					, ANSI_FGBG_OFF			);	\
	else if	(col == G_BLACK	 )	*len = SET_FGBG(fgbg, false, code					, ANSI_BLACK			);	\
	else if	(col <= G_REG_END)	*len = SET_FGBG(fgbg, false, code					, col					);	\
	else if	(col <= G_BRT_END)	*len = SET_FGBG(fgbg, false, code + ANSI_REG_BRT_MOD, col - G_REG_BRT_DIFF	);	\
	else						*len = SET_FGBG(fgbg, true , code					, col					);	\
	\
	has_##fgbg = (*len > 0);			\
	if (has_##fgbg) active.fgbg = col;	\
} while (0)

/* —————————————————————————————————————————————————————————————————— */

#define FGBG_OOR_WARNING(fgbg)								\
	fprintf(stderr,											\
		"Warning: `Colour::"#fgbg"` is out of range: %hd.\n"\
		"Valid range is: %d <= "#fgbg" <= %d.\n"			\
		"`"#fgbg"` has been locally set as follows:\n"		\
		"   abs(%hd) %% %d = %hd\n",						\
		(input_col.fgbg),									\
		COLOUR_T_MIN, COLOUR_T_MAX,							\
		(input_col.fgbg), COLOUR_T_MAX, (colour.fgbg)		\
	)

#define STYLE_OOR_WARNING()									\
	fprintf(stderr,											\
		"Warning: `Colour::style` is out of range: %#hx.\n"	\
		"Valid range is: 0x0 <= style <= %#hx.\n"			\
		"`style` has been locally set to 0x0.\n",			\
		(input_col.style), STYLE_T_MAX						\
	)

#define FGBG_BOUNDS_CHECK(fgbg) do {								\
	if (colour.fgbg < COLOUR_T_MIN || colour.fgbg > COLOUR_T_MAX) {	\
		colour.fgbg = abs(colour.fgbg) % COLOUR_T_MAX;				\
		FGBG_OOR_WARNING(fgbg);										\
	}																\
} while(0)

#define STYLE_BOUNDS_CHECK() do {		\
	if (colour.style > STYLE_T_MAX) {	\
		colour.style = G_NONE;			\
		STYLE_OOR_WARNING();			\
	}									\
} while(0)

/* —————————————————————————————————————————————————————————————————— */

#define HAS_STYLE(col_obj) ((col_obj).style & style_i)

#define APPEND_TO_STYLE(num) \
	st_len += SNPRINTF(style + st_len, STYLE_BUFSIZE - st_len, "%d;", num)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour active = RESET_ALL;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int stylelookup(const style_t style, const bool turn_style) {
	if (turn_style == OFF) {
		// bold and double underline don't conform to the normal escape
		//	sequences that turn styles off, so they need special exceptions
		int seq;
		switch (style) {
			case G_DUNDER:	return ANSI_NO_UNDER;	// on = `\e[21m`, off = `\e[24m`
			case G_BOLD:	return ANSI_NO_BOLD;	// on = `\e[1m` , off = `\e[22m`
			default: // recurse into this function, and add 20 to its normal output
				return stylelookup(style, ON) + ANSI_OFF_MOD; // on = `\e[Xm` , off = `\e[2Xm`
		}
	}

	switch (style) {
		case G_BOLD		: return ANSI_BOLD	;
		case G_DIM		: return ANSI_DIM	;
		case G_ITALIC	: return ANSI_ITALIC;
		case G_UNDER	: return ANSI_UNDER	;
		case G_BLINK	: return ANSI_BLINK	;
		case G_INVERT	: return ANSI_INVERT;
		case G_INVIS	: return ANSI_INVIS	;
		case G_STRIKE	: return ANSI_STRIKE;
		case G_DUNDER	: return ANSI_DUNDER;
		default:
			debug(WARNING, "Invalid `Colour::style` value: '%#x'", style);
			return ANSI_NOTHING; // the esc seq `\e[6m` does nothing, ∴ this code is harmless to print
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int colprint(const Colour input_col) {
	/// A working copy of the inputted colour object, which we can manipulate if needed.
	Colour colour = input_col;

	/* —————————————————————————————————————————————————————————————————— */

	STYLE_BOUNDS_CHECK();

	FGBG_BOUNDS_CHECK(fg);
	FGBG_BOUNDS_CHECK(bg);

	/* —————————————————————————————————————————————————————————————————— */

	const bool do_reset = colour.style & G_RESET;

	// if everything is exactly the same as the last time we printed, then don't do anything
	//	except for when we're resetting
	if (colour.style == active.style &&
		colour.fg	  == active.fg	&&
		colour.bg	  == active.bg	&&
		!do_reset
	) {
		puts("•\n[lorem ipsum dolor]");
		return 0;
	}

	/* —————————————————————————————————————————————————————————————————— */

	char style[STYLE_BUFSIZE] = "", fg[FGBG_BUFSIZE] = "", bg[FGBG_BUFSIZE] = "";

	/* —————————————————————————————————————————————————————————————————— */

	/// Current strlen of the `style` variable.
	int st_len = 0;

	// if the current style is identical to the previous style, then nothing has to be printed
	//	this check is technically redundant, but it saves having to do a check for each of the styles
	if (colour.style != active.style || do_reset) {
		style_t style_i;
		// iterate through each style, and check if the style is included in `colour.style`
		for (int i = 0; i < GSTYLES_LEN; i++) {
			style_i = G_STYLES[i];

			// however, only print the style if the previous style differs, or we're resetting
			if (HAS_STYLE(colour)) {
				if (!HAS_STYLE(active) || do_reset) {
					active.style |= style_i; // turn the style on
					APPEND_TO_STYLE(stylelookup(style_i, ON));
				}

			} else if (HAS_STYLE(active)) {
				// TODO: check for the collision between resetting BOLD and DIM
				active.style &= ~style_i; // turn the style off
				APPEND_TO_STYLE(stylelookup(style_i, OFF));
			}
		}
	}

	/* —————————————————————————————————————————————————————————————————— */

	int fg_len, bg_len;
	bool has_fg, has_bg;

	SIMPLIFY_ANSI(fg);
	SIMPLIFY_ANSI(bg);

	/* —————————————————————————————————————————————————————————————————— */

	if (!(has_fg || has_bg) 		// if there isn't any foreground or background,
		&& st_len > 0				// and there is at least one style code,
		&& style[st_len - 1] == ';' //   then check if the last char is a semicolon,
	) style[st_len - 1] = '\0';		//		and delete the semicolon if it exists.
	// this is to prevent the output being something like `\e[1;4;m`

	/* —————————————————————————————————————————————————————————————————— */

	const char* reset_sc = do_reset			? ";" : "";
	const char* foreg_sc = has_fg && has_bg ? ";" : "";

	/*return*/ printf(CSI "%s" "%s%s" "%s" "%s" END, reset_sc, style, fg, foreg_sc, bg);
	fflush(stdout);

	printf("st=%#hx, fg=%hd, bg=%hd\n", colour.style, colour.fg, colour.bg);
	puts("        |  style  | |   fg    | |   bg    |");
	printf("\\e[ (%1s) (%9s) (%8s%1s) (%8sm)\n",
		/**/reset_sc/**/, /**/style/**/, /**/fg, foreg_sc/**/, /**/bg/**/);
	printf("\\e[""%s""%s%s%s%s" END "\n", reset_sc, style, fg, foreg_sc, bg);

	puts("[lorem ipsum dolor]\n");

	/* —————————————————————————————————————————————————————————————————— */

	return -1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
