/// @file graphics/colour-object.h

#ifndef COLOUR_OBJECTS_INITIALIASED
#define COLOUR_OBJECTS_INITIALIASED

#include <inttypes.h>

/* —— Styles ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

// I only need 10 bits, but this is the smallest I can get it to
typedef uint16_t style_t; /** A bit record holding all styles that should be applied to some text. */

#define G_NONE		(style_t)0b0000000000 /** Don't set any styles. */
#define G_NORESET	(style_t)0b0000000001 /** Don't reset any styles/colours; continue using the active graphics. */
#define G_BOLD		(style_t)0b0000000010 /** Bolden text				(eqv. to `\e[1m`). */
#define G_DIM		(style_t)0b0000000100 /** Dim text					(eqv. to `\e[2m`). */
#define G_ITALIC	(style_t)0b0000001000 /** Italicise text			(eqv. to `\e[3m`). */
#define G_UNDER		(style_t)0b0000010000 /** Underline text			(eqv. to `\e[4m`). */
#define G_BLINK		(style_t)0b0000100000 /** Make text blink			(eqv. to `\e[5m`). */
#define G_INVERT	(style_t)0b0001000000 /** Invert fg & bg colours	(eqv. to `\e[7m`). */
#define G_INVIS		(style_t)0b0010000000 /** Make text invisible		(eqv. to `\e[8m`). */
#define G_STRIKE	(style_t)0b0100000000 /** Give text a strikethrough	(eqv. to `\e[9m`). */
#define G_DUNDER	(style_t)0b1000000000 /** Double-underline text		(eqv. to `\e[22m`). Only somewhat supported. */

/* —— Basic Colours ———————————————————————————————————————————————————————————————————————————————————————————————— */

/// A value in `[0, 255]`, representing an 8-bit ANSI colour code. I.e., `(colour_t)ID` = `\e[38;5;{ID}m`.
typedef uint8_t colour_t;

#define G_BLK	(colour_t)0  // \e[30m /** Black	*/
#define G_RED	(colour_t)1  // \e[31m /** Red		*/
#define G_GRN	(colour_t)2  // \e[32m /** Green	*/
#define G_YEL	(colour_t)3  // \e[33m /** Yellow	*/
#define G_BLU	(colour_t)4  // \e[34m /** Blue		*/
#define G_MAG	(colour_t)5  // \e[35m /** Magenta	*/
#define G_CYN	(colour_t)6  // \e[36m /** Cyan		*/
#define G_WHT	(colour_t)7  // \e[37m /** White	*/

#define G_BBLK	(colour_t)8  // \e[90m /** Bright Black		*/
#define G_BRED	(colour_t)9  // \e[91m /** Bright Red		*/
#define G_BGRN	(colour_t)10 // \e[92m /** Bright Green		*/
#define G_BYEL	(colour_t)11 // \e[93m /** Bright Yellow	*/
#define G_BBLU	(colour_t)12 // \e[94m /** Bright Blue		*/
#define G_BMAG	(colour_t)13 // \e[95m /** Bright Magenta	*/
#define G_BCYN	(colour_t)14 // \e[96m /** Bright Cyan		*/
#define G_BWHT	(colour_t)15 // \e[97m /** Bright White		*/

/* —— Main struct/object ——————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	style_t style;
	colour_t fg, bg;
} Colour;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !COLOUR_OBJECTS_INITIALIASED */
