/// @file graphics/colour-object.h

#ifndef COLOUR_OBJECTS_INITIALIASED
#define COLOUR_OBJECTS_INITIALIASED

#include <inttypes.h>

/* —— Styles ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

// I only need 10 bits, but this is the smallest I can get it to
typedef uint16_t style_t; /** A bit record holding all styles that should be applied to some text. */

#define STYLE_T_MAX ((style_t)((1 << 10) - 1)) /** 1023 == 0x03FF */

#define G_NONE		((style_t)0x0000) /**	 0 - Don't set any new styles. */
#define G_RESET		((style_t)0x0001) /**	 1 - Reset graphics before printing. Also resets colours.*/
#define G_BOLD		((style_t)0x0002) /**	 2 - Bolden text				(equivalent to `\e[1m`). */
#define G_DIM		((style_t)0x0004) /**	 4 - Dim text					(equivalent to `\e[2m`). */
#define G_ITALIC	((style_t)0x0008) /**	 8 - Italicise text				(equivalent to `\e[3m`). */
#define G_UNDER		((style_t)0x0010) /**	16 - Underline text				(equivalent to `\e[4m`). */
#define G_BLINK		((style_t)0x0020) /**	32 - Make text blink			(equivalent to `\e[5m`). */
#define G_INVERT	((style_t)0x0040) /**	64 - Invert fg & bg colours		(equivalent to `\e[7m`). */
#define G_INVIS		((style_t)0x0080) /**  128 - Make text invisible		(equivalent to `\e[8m`). */
#define G_STRIKE	((style_t)0x0100) /**  256 - Give text a strikethrough	(equivalent to `\e[9m`). */
#define G_DUNDER	((style_t)0x0200) /**  512 - Double-underline text		(equivalent to `\e[22m`).*/
#define G_ALL		((style_t)0x03FF) /** 1023 - Set all styles (only really useful for debugging).  */

/* —— Basic Colours ———————————————————————————————————————————————————————————————————————————————————————————————— */

/// A value in `[-1, 255]`, representing an 8-bit ANSI colour code. I.e., `(colour_t)ID` = `\e[38;5;{ID}m`.
typedef int16_t colour_t;

#define COLOUR_T_MIN ((colour_t)-1)			/**  -1 */
#define COLOUR_T_MAX ((colour_t)UINT8_MAX)	/** 255 */

#define G_NO_FG	((colour_t)0)	/** Don't change the foreground colour. */
#define G_NO_BG	((colour_t)0)	/** Don't change the background colour. */

#define G_BLK	((colour_t)-1)	// \e[30m /** Black		*/
#define G_RED	((colour_t)1)	// \e[31m /** Red		*/
#define G_GRN	((colour_t)2)	// \e[32m /** Green		*/
#define G_YEL	((colour_t)3)	// \e[33m /** Yellow	*/
#define G_BLU	((colour_t)4)	// \e[34m /** Blue		*/
#define G_MAG	((colour_t)5)	// \e[35m /** Magenta	*/
#define G_CYN	((colour_t)6)	// \e[36m /** Cyan		*/
#define G_WHT	((colour_t)7)	// \e[37m /** White		*/

#define G_BBLK	((colour_t)8)	// \e[90m /** Bright Black	 */
#define G_BRED	((colour_t)9)	// \e[91m /** Bright Red	 */
#define G_BGRN	((colour_t)10)	// \e[92m /** Bright Green	 */
#define G_BYEL	((colour_t)11)	// \e[93m /** Bright Yellow	 */
#define G_BBLU	((colour_t)12)	// \e[94m /** Bright Blue	 */
#define G_BMAG	((colour_t)13)	// \e[95m /** Bright Magenta */
#define G_BCYN	((colour_t)14)	// \e[96m /** Bright Cyan	 */
#define G_BWHT	((colour_t)15)	// \e[97m /** Bright White	 */

#define G_BLACK			G_BLK
#define G_GREEN			G_GRN
#define G_YELLOW		G_YEL
#define G_BLUE			G_BLU
#define G_MAGENTA		G_MAG
#define G_CYAN			G_CYN
#define G_WHITE			G_WHT
#define G_BRT_BLACK		G_BBLK /** Bright Black		*/
#define G_BRT_RED		G_BRED /** Bright Red		*/
#define G_BRT_GREEN		G_BGRN /** Bright Green		*/
#define G_BRT_YELLOW	G_BYEL /** Bright Yellow	*/
#define G_BRT_BLUE		G_BBLU /** Bright Blue		*/
#define G_BRT_MAGENTA	G_BMAG /** Bright Magenta	*/
#define G_BRT_CYAN		G_BCYN /** Bright Cyan		*/
#define G_BRT_WHITE		G_BWHT /** Bright White		*/

/* —— Main struct/object ——————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	style_t style;
	colour_t fg, bg;
} Colour;

#define RESET_ALL ((Colour){ .style = G_NONE, .fg = G_NO_FG, .bg = G_NO_BG }) /** Equivalent to `((Colour){0})`. */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int colprint(const Colour input_col);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !COLOUR_OBJECTS_INITIALIASED */
