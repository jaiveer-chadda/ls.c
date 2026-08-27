/// @file graphics/colour-object.c

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "colour-object.h"
#include "debugging/debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifndef CSI
#	define CSI "\033["
#	define END "m"
#endif

#define STYLE_BUFSIZE 21
#define FGBG_BUFSIZE  10

#define fg_ANSI_CODE 3
#define bg_ANSI_CODE 4

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define SNPRINTF(str, size, ...) d_snprintf(str, size, __VA_ARGS__)

	/// @brief A version of snprintf which does bounds checks and prints debugging messages.
	int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...) {
		va_list va_args;
		va_start(va_args, format);

		const int f_retcode = vsnprintf(str, size, format, va_args);
		const int f_errno = errno;
		va_end(va_args);

		if (f_retcode >= size || f_retcode == -1) {
			debug(ERROR, "snprintf(): `char str[]`: %s",
				(f_errno != 0) ? strerror(f_errno) : "buffer overflow"
			);
		}
		return f_retcode;
	}
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

#define SIMPLIFY_ANSI(fgbg) do { /* `fgbg` will be either `fg` or `bg` */ \
	if		(col.fgbg ==  0 || col.fgbg == prev.fgbg) { /* do nothing - keep this colour the same */ } \
	else if	(col.fgbg == -1) fgbg##_len = SNPRINTF(fgbg, FGBG_BUFSIZE, "%d0"		, fgbg##_ANSI_CODE						); \
	else if	(col.fgbg <=  7) fgbg##_len = SNPRINTF(fgbg, FGBG_BUFSIZE, "%d%hd"		, fgbg##_ANSI_CODE		, col.fgbg		); \
	else if (col.fgbg <= 15) fgbg##_len = SNPRINTF(fgbg, FGBG_BUFSIZE, "%d%hd"		, fgbg##_ANSI_CODE + 6	, col.fgbg - 8	); \
	else					 fgbg##_len = SNPRINTF(fgbg, FGBG_BUFSIZE, "%d8;5;%hd"	, fgbg##_ANSI_CODE		, col.fgbg		); \
} while (0)

#define HAS_STYLE(col_obj) ((col_obj).style & G_STYLES[i])

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour prev = RESET_ALL;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int stylelookup(style_t style) {
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wimplicit-fallthrough"
	switch (style) {
		case G_BOLD		: return  1;
		case G_DIM		: return  2;
		case G_ITALIC	: return  3;
		case G_UNDER	: return  4;
		case G_BLINK	: return  5;
		case G_INVERT	: return  7;
		case G_INVIS	: return  8;
		case G_STRIKE	: return  9;
		case G_DUNDER	: return 22;
		case G_RESET	: /* fallthrough */ ;
		default			: return  0;
	}
	#pragma clang diagnostic pop
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void colprint(const Colour col) {

	const bool do_reset = col.style & G_RESET;

	// if everything is exactly the same as the last time we printed, then don't do anything
	if (col.style == prev.style &&
		col.fg	  == prev.fg	&&
		col.bg	  == prev.bg	&&
		!do_reset // unless we're resetting things
	) {
		puts("•\n[lorem ipsum dolor]");
		return;
	}

	/* —————————————————————————————————————————————————————————————————— */

	char style[STYLE_BUFSIZE] = "", fg[FGBG_BUFSIZE] = "", bg[FGBG_BUFSIZE] = "";

	/* —————————————————————————————————————————————————————————————————— */

	/// Current strlen of the `style` variable.
	size_t st_len = 0;

	// if the current style is identical to the previous style, then nothing has to be printed
	//	this check is technically redundant, but it saves having to do a check for each of the styles
	if (col.style != prev.style || do_reset) {
		// iterate through each style, and check if the style is included in `col.style`
		for (int i = 0; i < GSTYLES_LEN; i++) {
			// however, only print the style if the previous style differs, or we're resetting
			if (HAS_STYLE(col) && (!HAS_STYLE(prev) || do_reset)) {
				st_len += SNPRINTF(style + st_len, STYLE_BUFSIZE - st_len, "%d;", stylelookup(G_STYLES[i]));
			}
		}
	}

	// remove the trailing semicolon
	//	- this is to prevent the output being something like `\e[4;m`,
	//		if there aren't any fg or bg colours to set
	if (style[st_len - 1] == ';') {
		style[st_len - 1] = '\0';
	}

	/* —————————————————————————————————————————————————————————————————— */

	int fg_len, bg_len;
	(void) bg_len;

	SIMPLIFY_ANSI(fg);
	SIMPLIFY_ANSI(bg);

	/* —————————————————————————————————————————————————————————————————— */

	const char *style_sc = st_len > 0 ? ";" : "";
	const char *foreg_sc = fg_len > 0 ? ";" : "";
	const char *reset_sc = do_reset	  ? ";" : "";

	printf(CSI "%s" "%s%s" "%s" "%s" END, reset_sc, style, fg, foreg_sc, bg);
	printf("\\e[""%s""%s%s%s%s" END "%s", reset_sc, style, fg, foreg_sc, bg, "\n");
	printf(CSI	 "%s""%s%s%s%s" END "%s", reset_sc, style, fg, foreg_sc, bg, "[lorem ipsum dolor]\n");

	/* —————————————————————————————————————————————————————————————————— */

	prev = col;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define test_1 ((Colour){ .style = G_BOLD | G_UNDER	, .fg = 125, .bg = G_BLU})
#define test_2 ((Colour){ .style = G_DIM  | G_UNDER	, .fg =  20, .bg = G_RED})
#define test_3 ((Colour){ .style = G_NONE			, .fg = 218, .bg = G_BLK})
#define test_4 ((Colour){ .style = G_NONE			, .fg =  20, .bg = G_BLK})

#define test_5 ((Colour){ .style = G_BOLD | G_ITALIC })
#define test_6 ((Colour){ .style = G_BOLD | G_UNDER })

int main(const int argc, const char* argv[]) {
	// colprint(test_1)	; putchar('\n');
	// colprint(test_2)	; putchar('\n');
	// colprint(test_3)	; putchar('\n');
	// colprint(test_2)	; putchar('\n');
	// colprint(test_4)	; putchar('\n');

	colprint(RESET_ALL)	; putchar('\n');

	colprint(test_5)	; putchar('\n');
	colprint(test_6)	; putchar('\n');

	return 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
