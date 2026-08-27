/// @file graphics/colour-object.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "colour-object.h"
#include "debugging/debugging.h"

#define NOBOLD	22
#define NOUNDER	24

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifndef CSI
#	define CSI "\033["
#	define END "m"
#endif

/**	The number of characters needed to represent every style, including a trailing semicolon and null terminator.
 *	- This would be: `"1;2;3;4;5;7;8;9;22;\0"`. */
#define STYLE_BUFSIZE 20
/**	The maximum number of characters needed to represent an 8-bit ANSI colour code, including a null terminator.
 *	- This would be: `"38;5;255\0"`. */
#define FGBG_BUFSIZE  9

#define fg_ANSI_CODE 3
#define bg_ANSI_CODE 4

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define SNPRINTF(str, size, ...) d_snprintf(str, size, __VA_ARGS__)

	/// @brief A version of snprintf with bounds-checking and which prints debugging messages.
	int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...) {
		va_list va_args;
		va_start(va_args, format);

		const int f_retcode = vsnprintf(str, size, format, va_args);
		const int f_errno = errno;
		va_end(va_args);

		if (f_retcode >= size || f_retcode == -1) {
			debug(WARNING, "snprintf(): `char str[]`: %s",
				(f_errno != 0) ? strerror(f_errno) : "buffer overflow"
			);
		}
		return f_retcode;
	}
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

/* —————————————————————————————————————————————————————————————————— */

#define SIMPLIFY_ANSI(fgbg) do {				\
	const colour_t col	=  (colour.fgbg);		\
	const int code		=  (fgbg##_ANSI_CODE);	\
	int *const len		= &(fgbg##_len);		\
	\
	if		(col ==  0 && (active.fgbg) == 0) *len = 0; /* don't change the fg/bg colour */		\
	else if	(col ==  0)	*len = SNPRINTF(fgbg, FGBG_BUFSIZE,		 "%d9",	code			 	);	\
	else if	(col == -1)	*len = SNPRINTF(fgbg, FGBG_BUFSIZE,		 "%d0",	code			 	);	\
	else if	(col <=  7)	*len = SNPRINTF(fgbg, FGBG_BUFSIZE,	   "%d%hd",	code	, col	 	);	\
	else if	(col <= 15)	*len = SNPRINTF(fgbg, FGBG_BUFSIZE,	   "%d%hd",	code + 6, col -	8	);	\
	else				*len = SNPRINTF(fgbg, FGBG_BUFSIZE,"%d8;5;%hd",	code	, col	 	);	\
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

/* —————————————————————————————————————————————————————————————————— */

#define HAS_STYLE(col_obj) ((col_obj).style & style_i)

#define APPEND_TO_STYLE(num) \
	st_len += SNPRINTF(style + st_len, STYLE_BUFSIZE - st_len, "%d;", num)

#define SC_IF(condition) ((condition) ? ";" : "")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour active = RESET_ALL;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int stylelookup(const style_t style) {
	switch (style) {
		case G_BOLD		: return  1;
		case G_DIM		: return  2;
		case G_ITALIC	: return  3;
		case G_UNDER	: return  4;
		case G_BLINK	: return  5;
		case G_INVERT	: return  7;
		case G_INVIS	: return  8;
		case G_STRIKE	: return  9;
		case G_DUNDER	: return 21;
		default:
			debug(WARNING, "Invalid style in `Colour` object: '%#x'", style);
			return 6; // the esc seq `\e[6m` does nothing, ∴ this number is harmless & has no side effects.
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int colprint(const Colour input_col) {
	/// A working copy of the inputted colour object, which we can manipulate if needed.
	Colour colour = input_col;

	/* —————————————————————————————————————————————————————————————————— */

	if (colour.style > STYLE_T_MAX) {
		colour.style = G_NONE;
		STYLE_OOR_WARNING();
	}

	if (colour.fg < COLOUR_T_MIN || colour.fg > COLOUR_T_MAX) {
		colour.fg = abs(colour.fg) % COLOUR_T_MAX;
		FGBG_OOR_WARNING(fg);
	}

	if (colour.bg < COLOUR_T_MIN || colour.bg > COLOUR_T_MAX) {
		colour.bg = abs(colour.bg) % COLOUR_T_MAX;
		FGBG_OOR_WARNING(bg);
	}

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
					APPEND_TO_STYLE(stylelookup(style_i));
				}

			} else if (HAS_STYLE(active)) {
				active.style &= ~style_i; // turn the style off

				// bold and double underline don't conform to the normal escape
				//	sequences that turn styles off, so they need special exceptions
				int seq;
				switch (style_i) {
					case G_DUNDER: seq = NOUNDER; break;			// on = `\e[21m`, off = `\e[24m`
					case G_BOLD	 : seq = NOBOLD ; break;			// on = `\e[1m` , off = `\e[22m`
					default		 : seq = stylelookup(style_i) + 20;	// on = `\e[Xm` , off = `\e[2Xm`
				}

				APPEND_TO_STYLE(seq);
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

	printf(CSI "%s" "%s%s" "%s" "%s" END, reset_sc, style, fg, foreg_sc, bg);
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
