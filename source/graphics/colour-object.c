/// @file graphics/colour-object.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "colour-object.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RESET_ALL	((Colour){ .style = G_NONE, .fg = G_NO_FG, .bg = G_NO_BG })

/* —————————————————————————————————————————————————————————————————— */

#define fg_ANSI_CODE 3
#define bg_ANSI_CODE 4

#define SIMPLIFY_ANSI(fgbg) do {																	\
	if		(col.fgbg == -1) sprintf(fgbg##_str, "%d0"		, fgbg##_ANSI_CODE				  );	\
	else if	(col.fgbg <=  7) sprintf(fgbg##_str, "%d%hd"	, fgbg##_ANSI_CODE		, col.fgbg);	\
	else if (col.fgbg <= 15) sprintf(fgbg##_str, "%d%hd"	, fgbg##_ANSI_CODE + 6	, col.fgbg - 8);\
	else					 sprintf(fgbg##_str, "%d8;5;%hd", fgbg##_ANSI_CODE		, col.fgbg);	\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline char *stylelookup(uint16_t style) {
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
		default			: return   ";";
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int colprint(const Colour col) {

	const bool do_reset = col.style & G_RESET;
	char style[256] = "", fg_str[256] = "", bg_str[256] = "";

	/* —————————————————————————————————————————————————————————————————— */

	// this check is technically redundant, but it saves having to do a check for each of the styles
	for (int i = 0; i < GSTYLES_LEN; i++) {
		if (col.style & G_STYLES[i]) {
			strcat(style, stylelookup(G_STYLES[i]));
		}
	}

	/* —————————————————————————————————————————————————————————————————— */

	if (col.fg != G_NO_FG) SIMPLIFY_ANSI(fg);
	if (col.bg != G_NO_BG) SIMPLIFY_ANSI(bg);

	/* —————————————————————————————————————————————————————————————————— */

	printf("\33[" "%s" "%s%s%s%sm"	  	, do_reset ? ";" : "", style, fg_str, strlen(fg_str) > 0 ? ";" : "", bg_str);
	printf("\\e[" "%s" "%s%s%s%sm" "%s"	, do_reset ? ";" : "", style, fg_str, strlen(fg_str) > 0 ? ";" : "", bg_str, "\n");
	printf("\33[" "%s" "%s%s%s%sm" "%s"	, do_reset ? ";" : "", style, fg_str, strlen(fg_str) > 0 ? ";" : "", bg_str, "[lorem ipsum dolor]\n");

	/* —————————————————————————————————————————————————————————————————— */

	return 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define test_1 ((Colour){ .style = G_BOLD | G_UNDER	, .fg = 125, .bg = G_BLU})
#define test_2 ((Colour){ .style = G_DIM  | G_UNDER	, .fg =  20, .bg = G_RED})
#define test_3 ((Colour){ .style = G_NONE			, .fg = 218, .bg = G_BLK})

int main(const int argc, const char* argv[]) {
	colprint(test_1)	; putchar('\n');
	colprint(test_2)	; putchar('\n');
	colprint(test_3)	; putchar('\n');
	colprint(RESET_ALL)	; putchar('\n');

	return 0;
}

// /* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

