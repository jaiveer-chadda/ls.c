/// @file graphics/colour-object.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "colour-object.h"

typedef struct {
	style_t style;
	colour_t fg, bg;
} Colour_;

#define COLOUR_NONE		((Colour){0})
#define DARK_MODE_INIT	((Colour){ .style = G_NONE						 , .fg = G_WHITE, .bg = G_BLACK })
#define LIGHT_MODE_INIT	((Colour){ .style = G_NONE						 , .fg = G_WHITE, .bg = G_BLACK })
#define test_1			((Colour){ .style = G_BOLD | G_UNDER | G_NO_RESET, .fg = G_BLACK, .bg = G_BLUE })

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);
static Colour prev = /* IS_DARK_MODE ? */ DARK_MODE_INIT /* : LIGHT_MODE_INIT */;

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
	printf("st : %#x \nfg : %hhu\nbg : %hhu\n\n", col.style, col.fg, col.bg);

	// I'm making the assumption that if someone wants a black foreground, black background, and no style,
	//	then they want the colour to be reset.
	if (col.style + col.fg + col.bg == 0) { prev = col; return 0; }

	/* —————————————————————————————————————————————————————————————————— */

	const bool do_reset = !(col.style & G_NO_RESET);
	char style[256] = "", fg_str[256] = "", bg_str[256] = "";

	/* —————————————————————————————————————————————————————————————————— */

	// this check is technically redundant, but it saves having to do a check for each of the styles
	if (col.style != prev.style) {
		for (int i = 0; i < GSTYLES_LEN; i++) {
			if (col.style & G_STYLES[i] && !(prev.style & G_STYLES[i])) {
				strcat(style, stylelookup(G_STYLES[i]));
			}
		}
	}

	/* —————————————————————————————————————————————————————————————————— */

	if		(col.fg == prev.fg) { /* do nothing - don't add anything to the output */ }
	else if	(col.fg <=	7)	sprintf(fg_str, 	"3%hhu;", col.fg);
	else if (col.fg <= 15)	sprintf(fg_str, 	"9%hhu;", col.fg - 8);
	else					sprintf(fg_str, "38;5;%hhu;", col.fg);
	
	/* —————————————————————————————————————————————————————————————————— */

	if		(col.bg == prev.bg) { /* do nothing - don't add anything to the output */ }
	else if	(col.bg <=	7)	sprintf(bg_str, 	"4%hhum", col.bg);
	else if (col.bg <= 15)	sprintf(bg_str,    "10%hhum", col.bg - 8);
	else					sprintf(bg_str, "48;5;%hhum", col.bg);

	/* —————————————————————————————————————————————————————————————————— */

	printf("\\e[" "%s" "%s%s%s" "%s", do_reset ? ";" : "", style, fg_str, bg_str, "\n");
	printf("\33[" "%s" "%s%s%s" "%s", do_reset ? ";" : "", style, fg_str, bg_str, "[lorem ipsum dolor]\33[m\n");

	/* —————————————————————————————————————————————————————————————————— */

	prev = col;
	return 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, const char* argv[]) {
	colprint(test_1);
	return EXIT_SUCCESS;
}

// /* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

