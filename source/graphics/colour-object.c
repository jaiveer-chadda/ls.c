/// @file graphics/colour-object.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "colour-object.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define COLOUR_NONE		((Colour){0})
#define DARK_MODE_INIT	((Colour){ .style = G_NONE, .fg = G_WHITE, .bg = G_BLACK })
#define LIGHT_MODE_INIT	((Colour){ .style = G_NONE, .fg = G_WHITE, .bg = G_BLACK })

/* —————————————————————————————————————————————————————————————————— */

#define fg_ANSI_CODE 3
#define bg_ANSI_CODE 4

#define SIMPLIFY_ANSI(fgbg) do {																	\
	if		(col.fgbg <=  7) sprintf(fgbg##_str, "%d%hhu"	 , fgbg##_ANSI_CODE		, col.fgbg);	\
	else if (col.fgbg <= 15) sprintf(fgbg##_str, "%d%hhu"	 , fgbg##_ANSI_CODE + 6	, col.fgbg - 8);\
	else					 sprintf(fgbg##_str, "%d8;5;%hhu", fgbg##_ANSI_CODE		, col.fgbg);	\
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
	// I'm making the assumption that if someone wants a black foreground, black background, and no style,
	//	then they want the colour to be reset.
	if (col.style + col.fg + col.bg == 0) return 0;

	/* —————————————————————————————————————————————————————————————————— */

	const bool do_reset = !(col.style & G_NO_RESET);
	char style[256] = "", fg_str[256] = "", bg_str[256] = "";

	/* —————————————————————————————————————————————————————————————————— */

	// this check is technically redundant, but it saves having to do a check for each of the styles
	for (int i = 0; i < GSTYLES_LEN; i++) {
		if (col.style & G_STYLES[i]) {
			strcat(style, stylelookup(G_STYLES[i]));
		}
	}

	/* —————————————————————————————————————————————————————————————————— */

	SIMPLIFY_ANSI(fg);
	SIMPLIFY_ANSI(bg);

	/* —————————————————————————————————————————————————————————————————— */

	printf("\\e[" "%s" "%s%s;%sm" "%s", do_reset ? ";" : "", style, fg_str, bg_str, "\n");
	printf("\33[" "%s" "%s%s;%sm" "%s", do_reset ? ";" : "", style, fg_str, bg_str, "[lorem ipsum dolor]\33[m\n");

	/* —————————————————————————————————————————————————————————————————— */

	return 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define test_1 ((Colour){ .style = G_BOLD | G_UNDER | G_NO_RESET, .fg = 125, .bg = G_BLUE })
#define test_2 ((Colour){ .style = G_DIM  | G_UNDER				, .fg = 125, .bg = G_RED })
#define test_3 ((Colour){ .style = G_NONE, .fg = 125, .bg = G_RED })

int main(const int argc, const char* argv[]) {
	colprint(test_1); putchar('\n');
	colprint(test_2); putchar('\n');
	colprint(test_3); putchar('\n');

	return 0;
}

// /* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

