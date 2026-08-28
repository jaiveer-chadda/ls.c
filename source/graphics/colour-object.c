/// @file graphics/colour-object.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "colour-defs.h"
#include "colour-object.h"

#include "debugging/debugging.h"

/* ── ── Static Variables ── ────────────────────────────────────────────────────────────────────────────────——————— */

static const style_t G_STYLES[] = { G_BOLD, G_DIM, G_ITALIC, G_UNDER, G_BLINK, G_INVERT, G_INVIS, G_STRIKE, G_DUNDER };
static const size_t GSTYLES_LEN = sizeof(G_STYLES)/sizeof(G_STYLES[0]);

static Colour active = RESET_ALL;

/* ── ── `d_snprintf()` ── ───────────────────────────────────────────────────────────────────────────────────────── */

#ifdef DEBUG_MODE
#	define SNPRINTF(str, size, ...) d_snprintf(str, size, __VA_ARGS__)

	/// @brief A version of `snprintf` with bounds-checking, and which prints debugging messages.
	static inline int d_snprintf(char *restrict str, size_t size, const char *restrict format, ...) {
		va_list va_args;
		va_start(va_args, format);

		const int f_retcode = vsnprintf(str, size, format, va_args);
		const int f_errno = errno;
		va_end(va_args);

		if (f_retcode >= size || f_retcode == EOF) {
			debug(WARNING, "snprintf(): `char *str`: %s",
				(f_errno != 0) ? strerror(f_errno) : "buffer overflow"
			);
		}
		return f_retcode;
	}
#else
#	define SNPRINTF(str, size, ...) snprintf(str, size, __VA_ARGS__)
#endif

/* ── ── `stylelookup()` ── ──────────────────────────────────────────────────────────────────────────────────────── */

#define ON	true
#define OFF	false

static inline int stylelookup(const style_t style, const bool turn_style) {
	if (turn_style == OFF) {
		// bold and double underline don't conform to the normal escape
		//	sequences that turn styles off, so they need special exceptions
		int seq;
		switch (style) {
			case G_DUNDER:	return ANSI_NO_UNDER;	// on = `\e[21m`, off = `\e[24m`
			case G_BOLD:	return ANSI_NO_BOLD;	// on = `\e[1m` , off = `\e[22m`
			default: // recurse into this function, and add 20 to its normal output
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
/* ── ── `colprint()` ── ─────────────────────────────────────────────────────────────────────────────────────────── */

int colprint(const Colour input_col) {
	/// A working copy of the inputted colour object, which we can manipulate if needed.
	Colour colour = input_col;

	/* ── Bounds Checking ─────────────────────────────────────────────── */

	STYLE_BOUNDS_CHECK();

	FGBG_BOUNDS_CHECK(fg);
	FGBG_BOUNDS_CHECK(bg);

	/* ── Check Identical Colours ─────────────────────────────────────── */

	// if everything is exactly the same as the last time we printed, then don't do anything
	if (colour.style == active.style &&
		colour.fg	 == active.fg	 &&
		colour.bg	 == active.bg
	) {
		puts("\n•\n[lorem ipsum dolor]\n");
		return 0;
	}

	/* ── Set Up Strings ──────────────────────────────────────────────── */

	char style[STYLE_BUFSIZE] = "", fg[FGBG_BUFSIZE] = "", bg[FGBG_BUFSIZE] = "";
	int st_len = 0; /** Current strlen of the `style` variable. */

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

	// if we're gonna remove BOLD and DIM from `active`, then pretend that `active`
	//	doesn't have one of them in the first place.
	//	- this way we won't have to reset both of them, which causes extra chars to be printed
	if (!(colour.has_style(G_BOLD)) && (active.has_style(G_BOLD)) && 
		!(colour.has_style(G_DIM) ) && (active.has_style(G_DIM) )
	) active.rem_style(G_BOLD);

	/* ———————————————————————————————————————————————— */

	// if the current style is identical to the previous style, then nothing has to be printed
	//	this check is technically redundant, but it saves having to do a check for each of the styles
	if (colour.style != active.style) {
		style_t style_i;
		// iterate through each style, and check if the style is included in `colour.style`
		for (int i = 0; i < GSTYLES_LEN; i++) {
			style_i = G_STYLES[i];

			// but only print the style if the previous style differs, or we're resetting
			if (colour.has_style(style_i)) {
				if (!(active.has_style(style_i))) {
					active.add_style(style_i); // turn the style on
					APPEND_TO_STYLE(stylelookup(style_i, ON));
				}

			// however, if the style isn't set in `colour`, but is active, then we need to turn it off
			} else if (active.has_style(style_i)) {
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

	SIMPLIFY_FGBG(fg);
	SIMPLIFY_FGBG(bg);

	/* ── Check for Reset All ─────────────────────────────────────────── */

	// if everything is set to 0, then there's no point individually
	//	resetting everything, so we can just print `\e[m` instead.
	if (active.style + active.fg + active.bg == 0) {
		/* return printf("%s", CSI END); */

		// TODO: these two lines should be deleted once I'm done debugging
		style[0] = '\0', fg[0] = '\0', bg[0] = '\0';
		st_len = 0, has_fg = false, has_bg = false;
	}

	/* ── Clean Up Semicolons ─────────────────────────────────────────── */

	if (!(has_fg || has_bg) 		// if there isn't any foreground or background,
		&& st_len > 0				// and there is at least one style code,
		&& style[st_len - 1] == ';' //   then check if the last char is a semicolon,
	) style[st_len - 1] = '\0';		//		and delete the semicolon if it exists.
	// this is to prevent the output being something like `\e[1;4;m`

	const char* foreg_sc = has_fg && has_bg ? ";" : "";

	/* ── Print & Return ──────────────────────────────────────────────── */

	/*return*/ printf(CSI /*"%s"*/ "%s%s" "%s" "%s" END, style, fg, foreg_sc, bg);
	putchar('\n');

	// printf("st=%#hx, fg=%hd, bg=%hd\n", colour.style, colour.fg, colour.bg);
	// printf("\\e[ (%1s) (%9s) (%8s%1s) (%8sm)\n",
	// 	/**/reset_sc/**/, /**/style/**/, /**/fg, foreg_sc/**/, /**/bg/**/);
	printf("\\e[""%s%s%s%sm\n", style, fg, foreg_sc, bg);

	puts("[lorem ipsum dolor]\n");

	return -1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ─────────────────────────────────────────────── ── eof ── ─────────────────────────────────────────────────────── */
