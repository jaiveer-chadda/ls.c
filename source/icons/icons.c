/// @file icons/icons.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "icons.h"

#include "utils/strings.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define REACHED_END_OF_ICONS(icn) ( \
	((icn.pattern) == NO_PATTERN) && \
	((icn.icon)	== NO_ICON))

#ifdef DEBUG_MODE
#	include "debugging/debugging.h"
#	define PRINTF_CHECK_ERROR(...) do {										\
		if (printf(__VA_ARGS__) == EOF) {									\
			const int printf_errno = errno;									\
			debug(ERROR, "printIcon: printf: %s", strerror(printf_errno));	\
		}																	\
	} while (0)
#else
#	define PRINTF_CHECK_ERROR(...) printf(__VA_ARGS__)
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline icon_t findIconMatch(const char *const check_str, const Icon icon_arr[]) {
	Icon icon = icon_arr[0];
	for (int i = 0; !REACHED_END_OF_ICONS(icon); icon = icon_arr[i++] ) {
		if (strcmp(icon.pattern, check_str) == 0) return icon.icon;
	}
	return NO_ICON;
}

icon_t getIcon(const char *filename, const bool is_dir) {
	path_t name_buf;
	toLower(name_buf, filename);

	// find the basename of the file, since that's the only part that needs to be matched
	const char *name = strrchr(name_buf, '/');
	// if there's no `/` in the name, then just revert to the normal name
	if (name == NULL) name = name_buf;

	// which array we should search in when looking for icons
	const Icon *const NAME_ARRAY = (Icon *)(is_dir ? &DIRNAME_ICONS : &FILENAME_ICONS);
	// see if the filename matches any of the names in `NAME_ARRAY`
	icon_t icon = findIconMatch(name, NAME_ARRAY);
	// if it matches, then it was a success - return that icon
	if (icon != NO_ICON) return icon;

	// if it didn't match any exact names, then check if it has an extension by finding the last full stop
	const char *const extension = strrchr(name + 1, '.'); // the +1 stops it from trying to match dotfiles
	// if it doesn't have an extension, return one of the default icons
	if (extension == NULL) return is_dir ? DEFAULT_DIR_ICON : DEFAULT_FILE_ICON; //  / 

	// once again, find the appropriate icon array for dirs/files
	const Icon *const EXT_ARRAY = (Icon *)(is_dir ? &DIR_EXT_ICONS : &FILE_EXT_ICONS);

	// if it _does_ have an extension, check that extension for matches
	icon = findIconMatch(extension + 1, EXT_ARRAY); // note: +1 so we don't include the literal '.'
	if (icon != NO_ICON) return icon;

	// if it no match was found, and the file isn't a directory, return the 'unknown' icon.
	//	this way, the unknown file icon 󰡯 will only be used in the case of an _unknown_ extension,
	// 	rather than, as eza does it, for _all_ files without extensions
	return is_dir ? DEFAULT_DIR_ICON : UNKNOWN_EXT_ICON; //  / 󰡯
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_icon(const FileStat *const pFS) {
	/// @todo implement the `DO_ICON` option
	// if (!DO_ICON()) return;

	Colour colour = {0};

	if (DO_COLOUR()) {
		colour = file_colour_esc[pFS->file_col];

		// if the colour has a background, then set its forground to the background colour
		if (has_bg(colour)) {
			colour.fg = colour.bg;
			colour.bg = G_NO_BG;
		}

		// the icon also shouldn't have any underlining
		if (colour.style & G_UNDER ) colour.style &= ~G_UNDER ;
		if (colour.style & G_DUNDER) colour.style &= ~G_DUNDER;
	}

	PRINTF_CHECK_ERROR("%s" "%s" "%lc",
		PRE_ICON_PAD,
		getcol(colour),
		(pFS->icon == NO_ICON) ? IC_ERROR : pFS->icon
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
