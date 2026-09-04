/// @file graphics/colour/colour-defs.h

#ifndef COLOUR_DEFS_H
#define COLOUR_DEFS_H

#include "colour-object.h"

/* —— ANSI Constants ——————————————————————————————————————————————————————————————————————————————————————————————— */

#ifndef CSI
#	define CSI		 "\033[" // \e[
#	define END		 "m"	 // m
#	define ANSI(esc) CSI esc END
#endif

#define ANSI_OFF_MOD	(+20) /** The modifier that turns (most) ANSI on-codes into off-codes. */
#define ANSI_REG_BRT_MOD (+6) /** The modifier that turns ANSI colour codes from regular to bright. */

#define ANSI_fg_CODE	3 /** The number which regular colour fg codes begin with. E.g. `\e[35m` or `\e[38;5;255m`. */
#define ANSI_bg_CODE	4 /** The number which regular colour fg codes begin with. E.g. `\e[44m` or `\e[48;5;128m`. */

#define ANSI_BLACK		0
#define ANSI_FGBG_OFF	9
#define ANSI_8BIT_SEQ	"8;5;"

/* —————————————————————————————————————————————————————————————————— */

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

#define ANSI_NO_DIM		(ANSI_OFF_MOD + ANSI_DIM)		/** 22 */
#define ANSI_NO_BOLD	 ANSI_NO_DIM					/** 22 */
#define ANSI_NO_ITALIC	(ANSI_OFF_MOD + ANSI_ITALIC	)	/** 23 */
#define ANSI_NO_UNDER	(ANSI_OFF_MOD + ANSI_UNDER	)	/** 24 */
#define ANSI_NO_BLINK	(ANSI_OFF_MOD + ANSI_BLINK	)	/** 25 */
#define ANSI_NO_INVERT	(ANSI_OFF_MOD + ANSI_INVERT	)	/** 27 */
#define ANSI_NO_INVIS	(ANSI_OFF_MOD + ANSI_INVIS	)	/** 28 */
#define ANSI_NO_STRIKE	(ANSI_OFF_MOD + ANSI_STRIKE	)	/** 29 */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Buffer Sizes ————————————————————————————————————————————————————————————————————————————————————————————————— */

/**	The number of characters needed to represent every style's reset sequence (usually longer),
 * including a trailing semicolon and null terminator.
 *	- This would be: `"22;23;24;25;27;28;29;\0"`. */
#define STYLE_BUFSIZE 22

/**	The maximum number of characters needed to represent an ANSI colour code, including a null terminator.
 *	- This would be: `"38;2;255;255;255\0"`. */
#define FGBG_BUFSIZE  17

/* —— Style Handling ——————————————————————————————————————————————————————————————————————————————————————————————— */

#define add_style(st) style |=  (st) /** Add   `st`to	the style attribute. */
#define rem_style(st) style &= ~(st) /** Remove`st`from the style attribute. */

#define APPEND_TO_STYLE(num) \
	st_len += SNPRINTF(style + st_len, STYLE_BUFSIZE - st_len, "%d;", num)

/* —— FG/BG Handling ——————————————————————————————————————————————————————————————————————————————————————————————— */

#define SET(fgbg, is_8bit, mode, ansi_col)		\
	SNPRINTF((fgbg), FGBG_BUFSIZE, ((is_8bit) ? "%d" ANSI_8BIT_SEQ "%d" : "%d%d"), (mode), (ansi_col))

#define SIMPLIFY_FGBG(fgbg) do {				\
	colour_t *const act	= &(active.fgbg);		\
	const colour_t col	=  (colour.fgbg);		\
	const int code		=  (ANSI_##fgbg##_CODE);\
	int *const len		= &(fgbg##_len);		\
	\
	if (IS_8B(col)) {							\
		if		(col == *act || (col == G_NO_FGBG && (*act == G_NO_FGBG || do_add))) *len = 0;	\
		else if	(col == G_NO_FGBG) *len = SET(fgbg, false, code					  , ANSI_FGBG_OFF		); /* 39 */ \
		else if	(col == G_BLACK	 ) *len = SET(fgbg, false, code					  , ANSI_BLACK			); /* 30 */ \
		else if	(col <= G_REG_END) *len = SET(fgbg, false, code					  , col					); /* 31 */ \
		else if	(col <= G_BRT_END) *len = SET(fgbg, false, code + ANSI_REG_BRT_MOD, col - G_REG_BRT_DIFF); /* 92 */ \
		else					   *len = SET(fgbg, true , code					  , col					); /* 38;5*/\
	\
	} else {									\
		if (col == *act) {						\
			*len = 0;							\
		\
		} else {								\
			const rgb_t rgb = toRGB_t(col);		\
			*len = SNPRINTF(fgbg, FGBG_BUFSIZE,	\
				"%d8;2;%hu;%hu;%hu",			\
				code, rgb.r, rgb.g, rgb.b		\
			);									\
		}										\
	}											\
	\
	has_##fgbg = (*len > 0);					\
	if (has_##fgbg) *act = col;					\
} while(0)

/* —— Bounds Checks ———————————————————————————————————————————————————————————————————————————————————————————————— */

// #define FGBG_OOR_WARNING(fgbg)								\
// 	fprintf(stderr,											\
// 		"Warning: `Colour::"#fgbg"` is out of range: %hd.\n"\
// 		"Valid range is: %d <= "#fgbg" <= %d.\n"			\
// 		"`"#fgbg"` has been locally set as follows:\n"		\
// 		"   abs(%hd) %% %d = %hd\n",						\
// 		(input_col.fgbg),									\
// 		COLOUR_8_MIN, COLOUR_8_MAX,							\
// 		(input_col.fgbg), COLOUR_8_MAX, (colour.fgbg)		\
// 	)

#define STYLE_OOR_WARNING()									\
	fprintf(stderr,											\
		"Warning: `Colour::style` is out of range: %#hx.\n"	\
		"Valid range is: 0x0 <= style <= %#hx.\n"			\
		"`style` has been locally set to 0x0.\n",			\
		(input_col.style), STYLE_T_MAX						\
	)

/* —— Warning Msgs —————————————————————————————————————————————————— */

#define FGBG_BOUNDS_CHECK(fgbg) do {										\
	if (!((COLOUR_8_MIN <= colour.fgbg && colour.fgbg <=  COLOUR_8_MAX) ||	\
		( COLOUR_24_MIN <= colour.fgbg && colour.fgbg <= COLOUR_24_MAX))	\
	) {																		\
		colour.fgbg = abs(colour.fgbg) % COLOUR_8_MAX;						\
		return -1;															\
	}																		\
} while(0)

#define STYLE_BOUNDS_CHECK() do {		\
	if (colour.style > STYLE_T_MAX) {	\
		colour.style = G_NONE;			\
		STYLE_OOR_WARNING();			\
	}									\
} while(0)

/* —————————————————————————————————————————————————————————————————— */

// spell:ignore fgbg

#endif /* !COLOUR_DEFS_H */

/* ———————————————————————————————————————————————————eof——————————————————————————————————————————————————————————— */
