/// @file graphics/colour-object.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "colour-object.h"

#ifdef DEBUG_MODE
#	include <errno.h>
#	include "debugging/debugging.h"
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define STYLE_BUFSIZE 21
#define FGBG_BUFSIZE  10

#define fg_ANSI_CODE 3
#define bg_ANSI_CODE 4

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define SNPRINTF(str, size, ...) do { \
		const int snprintf_retc = snprintf(str, size, __VA_ARGS__); \
		const int snprintf_errno = errno; \
		if (snprintf_retc >= size || snprintf_retc == -1) \
			debug(ERROR, "colprint(): `char style[]`: %s", strerror(snprintf_errno)); \
	} while (0)
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

#define SIMPLIFY_ANSI(fgbg) do { \
	if		(col.fgbg == prev.fgbg || col.fgbg == 0) { /* do nothing - keep this colour the same */ } \
	else if	(col.fgbg == -1) SNPRINTF(fgbg, FGBG_BUFSIZE, "%d0"		 , fgbg##_ANSI_CODE						); \
	else if	(col.fgbg <=  7) SNPRINTF(fgbg, FGBG_BUFSIZE, "%d%hd"	 , fgbg##_ANSI_CODE		, col.fgbg		); \
	else if (col.fgbg <= 15) SNPRINTF(fgbg, FGBG_BUFSIZE, "%d%hd"	 , fgbg##_ANSI_CODE + 6	, col.fgbg - 8	); \
	else					 SNPRINTF(fgbg, FGBG_BUFSIZE, "%d8;5;%hd", fgbg##_ANSI_CODE		, col.fgbg		); \
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour prev = RESET_ALL;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline char *stylelookup(uint16_t style) {
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wimplicit-fallthrough"
	switch (style) {
		case G_BOLD		: return  "1;";
		case G_DIM		: return  "2;";
		case G_ITALIC	: return  "3;";
		case G_UNDER	: return  "4;";
		case G_BLINK	: return  "5;";
		case G_INVERT	: return  "7;";
		case G_INVIS	: return  "8;";
		case G_STRIKE	: return  "9;";
		case G_DUNDER	: return "22;";
		case G_RESET	: /* fallthrough */ ;
		default			: return   ";";
	}
	#pragma clang diagnostic pop
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void colprint(const Colour col) {

	// if everything is exactly the same as the last time we printed, then don't do anything
	if (col.style == prev.style &&
		col.fg	  == prev.fg	&&
		col.bg	  == prev.bg
	) return;

	/* —————————————————————————————————————————————————————————————————— */

	char style[STYLE_BUFSIZE] = "", fg[FGBG_BUFSIZE] = "", bg[FGBG_BUFSIZE] = "";

	/* —————————————————————————————————————————————————————————————————— */

	const bool do_reset = col.style & G_RESET;

	// if the current style is identical to the previous style, then nothing has to be printed
	//	this check is technically redundant, but it saves having to do a check for each of the styles
	if (col.style != prev.style) {
		// iterate through each style, and check if the style is included in `col.style`
		for (int i = 0; i < GSTYLES_LEN; i++) {
			if (col.style & G_STYLES[i] && !(prev.style & G_STYLES[i])) {
				#ifdef DEBUG_MODE
					const int strlcat_retc = strlcat(style, stylelookup(G_STYLES[i]), STYLE_BUFSIZE);
					const int strlcat_errno = errno;

					if (strlcat_retc >= STYLE_BUFSIZE || strlcat_retc == -1) {
						debug(ERROR, "colprint(): `char style[]`: %s", strerror(strlcat_errno));
					}
				#else
					strlcat(style, stylelookup(G_STYLES[i]), STYLE_BUFSIZE);
				#endif
			}
		}
	}

	/* —————————————————————————————————————————————————————————————————— */

	SIMPLIFY_ANSI(fg);
	SIMPLIFY_ANSI(bg);

	/* —————————————————————————————————————————————————————————————————— */

	const char *fg_sc	 = (strlen(fg) > 0)	? ";" : "";
	const char *reset_sc = do_reset			? ";" : "";

	printf("\33[" "%s" "%s%s%s%sm"	  	, reset_sc, style, fg, fg_sc, bg);
	printf("\\e[" "%s" "%s%s%s%sm" "%s"	, reset_sc, style, fg, fg_sc, bg, "\n");
	printf("\33[" "%s" "%s%s%s%sm" "%s"	, reset_sc, style, fg, fg_sc, bg, "[lorem ipsum dolor]\n");

	/* —————————————————————————————————————————————————————————————————— */

	prev = col;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define test_1 ((Colour){ .style = G_BOLD | G_UNDER	, .fg = 125, .bg = G_BLU})
#define test_2 ((Colour){ .style = G_DIM  | G_UNDER	, .fg =  20, .bg = G_RED})
#define test_3 ((Colour){ .style = G_NONE			, .fg = 218, .bg = G_BLK})
#define test_4 ((Colour){ .style = G_NONE			, .fg =  20, .bg = G_BLK})

int main(const int argc, const char* argv[]) {
	colprint(test_1)	; putchar('\n');
	colprint(test_2)	; putchar('\n');
	colprint(test_3)	; putchar('\n');
	colprint(test_2)	; putchar('\n');
	colprint(test_4)	; putchar('\n');
	colprint(RESET_ALL)	; putchar('\n');
	return 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

