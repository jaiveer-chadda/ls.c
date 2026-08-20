/// @file icons/icons.c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "icons.h"

#include "options/options.h"
#include "graphics/graphics.h"

#include "debugging/debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define REACHED_END_OF_ICONS(icn) ( \
	((icn.pattern) == NO_PATTERN) && \
	((icn.icon)	== NO_ICON))

#define IF_COLOUR(print) DO_COLOUR() ? print : ""

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline icon_t findIconMatch(const char *check_str, const Icon icon_arr[]) {
	Icon icon = icon_arr[0];
	for (int i = 0; !REACHED_END_OF_ICONS(icon); icon = icon_arr[i++] ) {
		if (strcmp(icon.pattern, check_str) == 0) return icon.icon;
	}
	return NO_ICON;
}

icon_t getIcon(const char *filename, const bool is_dir) {
	const Icon *NAME_ARRAY = (Icon *)(is_dir ? &DIRNAME_ICONS : &FILENAME_ICONS);
	// see if the filename matches any of the names in `NAME_ARRAY`
	icon_t icon = findIconMatch(filename, NAME_ARRAY);
	// if it matches, then it was a success - return that icon
	if (icon != NO_ICON) return icon;

	// if it didn't match any exact names, then check if it has an extension by finding the last full stop
	const char *extension = strrchr(filename, '.');
	// if it doesn't have an extension, return one of the default icons
	if (extension == NULL) return is_dir ? DEFAULT_DIR_ICON : DEFAULT_FILE_ICON; //  / 

	const Icon *EXT_ARRAY = (Icon *)(is_dir ? &DIR_EXT_ICONS : &FILE_EXT_ICONS);
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

void printIcon(const icon_t icon, const FileColour file_col) {
	if (printf(
			"%s%s%s" "%lc" "%s",
			IF_COLOUR(CSI), file_colour_esc[file_col], IF_COLOUR(END), icon, IF_COLOUR(RESET)
		) < 0
	) fputs(strerror(errno), stderr);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
