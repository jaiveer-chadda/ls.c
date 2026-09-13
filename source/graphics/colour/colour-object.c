/// @file graphics/colour/colour-object.c

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "colour-defs.h"
#include "colour-object.h"

#include "debugging.h"
#include "options/options.h"

typedef struct { uint8_t r, g, b; } rgb_t;

/* ── ── Function Defs ── ────────────────────────────────────────────────────────────────────────────────────────── */

static inline rgb_t toRGB_t(const colour_t raw);
static inline int stylelookup(const style_t style, const bool turn_style);
static inline void simplify_fgbg(
	char *const fgbg, colour_t *const act, int *const len, bool *const has_fgbg,
	const colour_t col, const int code, const bool set_active, const bool do_add
);

#ifdef DEBUG_MODE
	static inline int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...);
#	define SNPRINTF(str, size, ...) d_snprintf(str, size, __VA_ARGS__)
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

/* ── ── Static Variables ── ─────────────────────────────────────────────────────────────────────────────────────── */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour active = RESET_ALL;

/* —————————————————————————————————————————————————————————————————— */

/**
 * @brief A heap-like buffer to store ANSI escape sequences to be printed.
 *
 *	  - Note: Actually stored on the stack.
 *
 * ---
 * 
 * A kilobyte (`MAX_ANSI_SIZE * COLHEAP_CAPACITY` == `64 * 16` == `1024 bytes`) of "heap" storage - enough to hold 16
 *	maximum-size ANSI escape sequences.
 *
 * ---
 *
 * This heap replaces a single `output_buffer`, which held an ANSI escape sequence until it was printed.
 *
 * The issue with that solution, however, was that I could never use `getcol` twice in a single `printf` statement -
 *	I would have to either copy the colour into a buffer, then print the buffer, or print the first colour(s) on
 *	its/their own, and then print the final colour in the `printf`.
 *
 * This was causing all types of inefficiencies. `colheap` can help solve those by having more than `COLHEAP_CAPACITY`
 *	automatically-managed buffers to store colours in before they're printed.
 *
 *	  - Although in practice, the last `MAX_ANSI_SIZE` worth of bytes will never be fully used, due to the way
 *		`colheap` is rotated, so there are more like `COLHEAP_CAPACITY - 1` max-size buffers.
 *
 *	  - However, in reality, there are far more than `COLHEAP_CAPACITY` escape sequences worth of buffers, since most
 *		escape sequences don't take up anywhere near as much as `MAX_ANSI_SIZE` bytes.
 * 
 * ---
 *
 * Note: `colheap` is initialised by being filled with nullbytes, which isn't strictly necessary, however, makes
 *	debugging significantly easier, were something to go wrong.
 */
static char colheap[MAX_ANSI_SIZE * COLHEAP_CAPACITY] = {0};

/** A pointer to the next available space on `colheap`. */
static char *colheap_ptr = colheap;

/** A constant pointer to the last addressable byte on `colheap`. */
static const char *const colheap_end = colheap + sizeof(colheap) - 1;

/* —————————————————————————————————————————————————————————————————— */

static inline char *get_colheap_ptr(void) {
	// if the next write to `colheap` has even the possibility of overflowing the heap,
	//	then reset the buffer, and move the pointer back to the beginning of the heap
	if (colheap_ptr + sizeof(ansi_t) >= colheap_end) {
		#ifdef DEBUG_MODE
			// turning everything back into nullbytes will make it much easier to debug if something goes wrong
			colheap_ptr = memset(colheap, 0, sizeof(colheap));
		#else
			colheap_ptr = colheap;
		#endif
	}

	return colheap_ptr;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── `getcol()` ── ───────────────────────────────────────────────────────────────────────────────────────────── */

// note: this function isn't threadsafe, but that should be fine I think, since its only really used for printing

#define RETURN_LEN(len)		do { if (collen != NULL) (*collen = ((uint8_t)(len)));	} while (0)
#define RETURN_LITERAL(str)	do { RETURN_LEN(sizeof(str) - 1); return (str);			} while (0)

char *c__getcol(const Colour input_col, const bool set_active, uint8_t *const collen) {
	// simple way to make sure that nothing's printed when colour output is turned off
	if (!DO_COLOUR()) RETURN_LITERAL("");

	/// A copy of the inputted colour object, which we can mutate if needed.
	Colour colour = input_col;

	/* ── Bounds Checking ─────────────────────────────────────────────── */

	#ifdef DEBUG_MODE
		// check that `colour.style` is <= STYLE_T_MAX
		STYLE_BOUNDS_CHECK();

		// check that fg and bg are between `COLOUR_T_MIN` and `COLOUR_T_MAX`
		FGBG_BOUNDS_CHECK(fg);
		FGBG_BOUNDS_CHECK(bg);
	#endif

	/* ── Check Identical Colours ─────────────────────────────────────── */

	// if everything is exactly the same as the last time we printed, or we dont want to print anything, return nothing
	if (areEqual(colour, active) || areEqual(colour, NO_CHANGE)) RETURN_LITERAL("");

	/* ── Process Colour::style ───────────────────────────────────────── */

	const bool has_under  = colour.has_style(G_UNDER );
	const bool has_dunder = colour.has_style(G_DUNDER);

	// UNDER/DUNDER will always overwrite each other,
	//	so there's no point resetting one just to replace it with the other
	if (set_active && has_under ) active.rem_style(G_DUNDER);
	if (set_active && has_dunder) active.rem_style(G_UNDER );

	// additionally, having both is also redundant, so, since DUNDER takes priority, remove UNDER from `colour`
	if (has_under && has_dunder) colour.rem_style(G_UNDER);

	/* ———————————————————————————————————————————————— */

	const bool do_add = colour.has_style(G_ADD);

	// if we're gonna remove BOLD and DIM from `active`, then pretend that `active`
	//	doesn't have one of them in the first place.
	//	- this way we won't have to reset both of them, which causes extra chars to be printed
	if (!do_add && set_active && // (when we're adding, we won't be removing anything, so this check is unnecessary)
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
				if (set_active) active.add_style(style_i); // turn the style on
				APPEND_TO_STYLE(stylelookup(style_i, ON));

			// however, if the style isn't set in `colour`, but is active, then we need to turn it off
			} else if (!col_has_st && act_has_st && !do_add) { // that is, unless we're just adding
				has_st = true;
				if (set_active) active.rem_style(style_i); // turn the style off
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
	if (active.style + active.fg + active.bg == 0) RETURN_LITERAL(CSI END);

	/* ── Check for Nothing-ness ──────────────────────────────────────── */

	// if we're adding to the colours/styles, but there's nothing to add,
	//	then don't output anything
	if (do_add && !(has_st || has_fg || has_bg)) RETURN_LITERAL("");

	/* ── Clean Up Semicolons ─────────────────────────────────────────── */

	if (!(has_fg || has_bg)			// if there isn't any foreground or background,
		&& has_st					// and there is at least one style code,
		&& style[st_len - 1] == ';' //   then check if the last char is a semicolon,
	) style[st_len - 1] = '\0';		//		and delete the semicolon if it exists.
	// this is to prevent the output being something like `\e[1;4;m`

	const bool do_fg_sc = has_fg && has_bg;

	/* ── Set Buffer & Return ─────────────────────────────────────────── */

	const size_t output_len = snprintf(
		( colheap_ptr = get_colheap_ptr() ), sizeof(ansi_t),
		ANSI("%s%s" "%s" "%s"),
		style, fg, do_fg_sc ? ";" : "", bg
	);

	if (output_len >= sizeof(ansi_t)) { WRITE_LEN_WARNING(); RETURN_LITERAL(""); }

	// first save the pointer to the output colour, only then increment colheap_ptr to the next available space
	char *const output_ptr = colheap_ptr;
	colheap_ptr += output_len + 1; // +1 to include the nullbyte

	RETURN_LEN(output_len);
	return output_ptr;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── Ext Helper Funcs ── ─────────────────────────────────────────────────────────────────────────────────────── */

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

Colour getActive(void) { return active; }

bool areEqual(const Colour c1, const Colour c2) {
	return
		c1.fg	 == c2.fg &&
		c1.bg	 == c2.bg &&
		c1.style == c2.style;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ── ── `simplify_fgbg()` ── ────────────────────────────────────────────────────────────────────────────────────── */

#define SET_FGBG(fgbg, is_8bit, mode, ansi_col) \
	SNPRINTF((fgbg), FGBG_BUFSIZE, ((is_8bit) ? "%d" ANSI_8BIT_SEQ "%d" : "%d%d"), (mode), (ansi_col))

static inline void simplify_fgbg(
	char *const fgbg, colour_t *const act, int *const len, bool *const has_fgbg,
	const colour_t col, const int code, const bool set_active, const bool do_add
) {
	*len = 0;
	if (IS_8B(col)) {
		if		(col == *act || (col == G_NO_FGBG && (*act == G_NO_FGBG || do_add))) *len = 0;
		else if	(col == G_NO_FGBG) *len = SET_FGBG(fgbg, false, code			  , ANSI_FGBG_OFF	); // 39
		else if	(col == G_BLACK	 ) *len = SET_FGBG(fgbg, false, code			  , ANSI_BLACK		); // 30
		else if	(col <= G_REG_END) *len = SET_FGBG(fgbg, false, code			  , col				); // 31
		else if	(col <= G_BRT_END) *len = SET_FGBG(fgbg, false, code + ANSI_RB_MOD, col - G_RB_DIFF	); // 92
		else					   *len = SET_FGBG(fgbg, true , code			  , col				); // 38;5

	} else if (col != *act) {
		const rgb_t rgb = toRGB_t(col);
		*len = SNPRINTF(fgbg, FGBG_BUFSIZE, "%d8;2;%hu;%hu;%hu", code, rgb.r, rgb.g, rgb.b);
	}

	*has_fgbg = (*len > 0);
	if (set_active && *has_fgbg) *act = col;
}

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
