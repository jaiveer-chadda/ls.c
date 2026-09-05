/// @file graphics/colour/colour-object.c

#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "colour-defs.h"
#include "colour-object.h"

#include "malloc.h"
#include "debugging.h"
#include "options/options.h"

typedef struct { uint8_t r, g, b; } rgb_t;

/* ── ── Function Defs ── ───────────────────────────────────────────────────────────────────────────────────——————— */

static inline rgb_t toRGB_t(const colour_t raw);
static inline int stylelookup(const style_t style, const bool turn_style);

#ifdef DEBUG_MODE
	static inline int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...);
#	define SNPRINTF(str, size, ...) d_snprintf(str, size, __VA_ARGS__)
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

/* ── ── Static Variables ── ────────────────────────────────────────────────────────────────────────────────——————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour active = RESET_ALL;

// the initial `CSI` will always remain here; only chars after it will ever be changed
static char output_buffer[OUTPUT_BUFSIZE] = CSI;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── `setActive()` ── ────────────────────────────────────────────────────────────────────────────────────────── */

/**
 * @fn setActive
 * @brief Notify `getcol()` to what the active colour on screen is.
 *
 * Lets the the colour printing functions, `getcol()` or `colprint()`, know what the active colour on screen is,
 * in the case that a colour was printed manually.
 *
 * @param input[in] The colour which the active colour should be set.
 * @result Sets `static Colour active` to be equal to `input`.
 */
void setActive(const Colour input) {
	if (!DO_COLOUR()) return;

	active.fg	 = input.fg,
	active.bg	 = input.bg,
	active.style = input.style;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── `getcol()` ── ───────────────────────────────────────────────────────────────────────────────────────────── */

// note: this function isn't threadsafe, but that should be fine I think, since its only really used for printing

char *getcol(const Colour input_col) {
	// this is a nice and simple way to make sure that nothing's printed when colour output is turned off
	if (!DO_COLOUR()) return "";

	/// A working copy of the inputted colour object, which we can mutate if needed.
	Colour colour = input_col;

	/* ── Bounds Checking ─────────────────────────────────────────────── */

	// check that `colour.style` is <= STYLE_T_MAX
	STYLE_BOUNDS_CHECK();

	// check that fg and bg are between `COLOUR_T_MIN` and `COLOUR_T_MAX`
	FGBG_BOUNDS_CHECK(fg);
	FGBG_BOUNDS_CHECK(bg);

	/* ── Check Identical Colours ─────────────────────────────────────── */

	// if everything is exactly the same as the last time we printed, then don't do anything
	if (colour.fg	 == active.fg &&
		colour.bg	 == active.bg &&
		colour.style == active.style
	) return "";

	/* ── Process Colour::style ───────────────────────────────────────── */

	const bool has_under  = colour.has_style(G_UNDER );
	const bool has_dunder = colour.has_style(G_DUNDER);

	// UNDER/DUNDER will always overwrite each other,
	//	so there's no point resetting one just to replace it with the other
	if (has_under ) active.rem_style(G_DUNDER);
	if (has_dunder) active.rem_style(G_UNDER );

	// additionally, having both is also redundant, so, since DUNDER takes priority, remove UNDER from `colour`
	if (has_under && has_dunder) colour.rem_style(G_UNDER);

	/* ———————————————————————————————————————————————— */

	const bool do_add = colour.has_style(G_ADD);

	// if we're gonna remove BOLD and DIM from `active`, then pretend that `active`
	//	doesn't have one of them in the first place.
	//	- this way we won't have to reset both of them, which causes extra chars to be printed
	if (!do_add && // (when we're adding, we won't be removing anything, so this check is unnecessary)
		!(colour.has_style(G_BOLD)) && (active.has_style(G_BOLD)) && 
		!(colour.has_style(G_DIM) ) && (active.has_style(G_DIM) )
	) active.rem_style(G_BOLD);

	/* ———————————————————————————————————————————————— */

	char style[STYLE_BUFSIZE] = "";
	int st_len = 0; /** Current strlen of the `style` variable. */
	bool has_st = false;

	// if the current style is identical to the previous style, then nothing has to be printed
	//	this check is technically redundant, but it saves having to do a check for each of the styles
	if (colour.style != active.style) {
		style_t style_i;
		bool col_has_st, act_has_st;

		// iterate through each style, and check if the style is included in `colour.style`
		for (size_t i = 0; i < GSTYLES_LEN; i++) {
			style_i = G_STYLES[i];
			col_has_st = colour.has_style(style_i);
			act_has_st = active.has_style(style_i);

			// but only print the style if the previous style differs
			if (col_has_st && !act_has_st) {
				has_st = true;
				active.add_style(style_i); // turn the style on
				APPEND_TO_STYLE(stylelookup(style_i, ON));

			// however, if the style isn't set in `colour`, but is active, then we need to turn it off
			} else if (!col_has_st && act_has_st && !do_add) { // that is, unless we're just adding
				has_st = true;
				active.rem_style(style_i); // turn the style off
				APPEND_TO_STYLE(stylelookup(style_i, OFF));

				// since the codes to reset bold & dim are identical,
				//	we need to re-apply the other when we reset the other
				if (style_i == G_BOLD && active.has_style(G_DIM) ) APPEND_TO_STYLE(ANSI_DIM );
				if (style_i == G_DIM  && active.has_style(G_BOLD)) APPEND_TO_STYLE(ANSI_BOLD);
			}
		}
	}

	/* ── Process Colour::fg/bg ───────────────────────────────────────── */

	int fg_len, bg_len;
	bool has_fg, has_bg;
	char fg[FGBG_BUFSIZE] = "", bg[FGBG_BUFSIZE] = "";

	SIMPLIFY_FGBG(fg);
	SIMPLIFY_FGBG(bg);

	/* ── Check for Resetting ─────────────────────────────────────────── */

	// if everything is set to 0, then there's no point individually
	//	resetting everything, so we can just print `\e[m` instead.
	if (active.style + active.fg + active.bg == 0) return CSI END;

	/* ── Check for Nothing-ness ──────────────────────────────────────── */

	// if we're adding to the colours/styles, but there's nothing to add,
	//	then don't output anything
	if (do_add && !(has_st || has_fg || has_bg)) return "";

	/* ── Clean Up Semicolons ─────────────────────────────────────────── */

	if (!(has_fg || has_bg)			// if there isn't any foreground or background,
		&& has_st					// and there is at least one style code,
		&& style[st_len - 1] == ';' //   then check if the last char is a semicolon,
	) style[st_len - 1] = '\0';		//		and delete the semicolon if it exists.
	// this is to prevent the output being something like `\e[1;4;m`

	const bool do_fg_sc = has_fg && has_bg;

	/* ── Set Buffer & Return ─────────────────────────────────────────── */

	if (snprintf(output_buffer, OUTPUT_BUFSIZE,
		ANSI("%s%s" "%s" "%s"),
		style, fg, do_fg_sc ? ";" : "", bg
	) >= OUTPUT_BUFSIZE) return "";

	return output_buffer;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── `toRGB_t()` ── ───────────────────────────────────────────────────────────────────────────────────────────── */

static inline rgb_t toRGB_t(const colour_t raw) {
	assert(raw >= COLOUR_24_MIN);

	const int rgb = (raw - COLOUR_24_MIN);

	const uint8_t red = (rgb / 1000000);
	const uint8_t grn = (rgb / 1000) -  (red * 1000);
	const uint8_t blu = (rgb - ((rgb / 1000) * 1000));

	assert(0U <= red && red <= 255U);
	assert(0U <= grn && grn <= 255U);
	assert(0U <= blu && blu <= 255U);

	return (const rgb_t){ .r = red, .g = grn, .b = blu };
}

/* ── ── `d_snprintf()` ── ───────────────────────────────────────────────────────────────────────────────────────── */

#ifdef DEBUG_MODE
/// @brief A version of `snprintf` with bounds-checking, and which prints debugging messages.
static inline int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...) {
	va_list va_args;
	va_start(va_args, format);

	const int f_retcode = vsnprintf(str, size, format, va_args);
	const int f_errno = errno;
	va_end(va_args);

	if ((size_t)f_retcode >= size || f_retcode == EOF) {
		debug(WARNING, "snprintf(): `char *str`: %s",
			(f_errno != 0) ? strerror(f_errno) : "buffer overflow"
		);
	}
	return f_retcode;
}
#endif

/* ── ── `stylelookup()` ── ──────────────────────────────────────────────────────────────────────────────────────── */

/**
 * @fn stylelookup
 * @brief Get the ANSI code corresponding to turning a style on or off.
 *
 * @param style A `style_t` integer with only one style set.
 * @param turn_style Whether the ouput code should turn `style` on or off (true = on, false = off).
 * @return int: The ANSI code representing turning the input style on or off. Returns 6 or 26 if `style` was invalid.
 */
static inline int stylelookup(const style_t style, const bool turn_style) {
	assert(0x0000 < style && style <= 0x0200); // `style` is in range
	assert(log2(style) == floor(log2(style))); // `style` is a power of 2

	if (turn_style == OFF) {
		// bold and double underline don't conform to the normal escape
		//	sequences that turn styles off, so they need special exceptions
		switch (style) {
			case G_DUNDER:	return ANSI_NO_UNDER;	// on = `\e[21m`, off = `\e[24m`
			case G_BOLD:	return ANSI_NO_BOLD;	// on = `\e[1m` , off = `\e[22m`
			default: // recurse once into this function, and add 20 to its normal output
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
			return ANSI_NOTHING; // the esc seq `\e[6m` does nothing, and is harmless to print
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore gstyles fgbg foreg

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ─────────────────────────────────────────────── ── eof ── ─────────────────────────────────────────────────────── */
