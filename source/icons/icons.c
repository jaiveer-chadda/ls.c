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
	// determine which array we'll be using, depending on whether the file's a directory or not
	const Icon *ICON_ARRAY = (Icon *)(is_dir ? &DIRNAME_ICONS : &FILENAME_ICONS);

	icon_t icon = findIconMatch(filename, ICON_ARRAY);	// see if the filename matches any of the names in `ICON_ARRAY`
	if (icon != NO_ICON) return icon;					// if it matches, then it was a success - return that icon
	else if (is_dir)	 return DEFAULT_DIR_ICON; // 	// if it doesn't, and it's not a file, return the default icon

	// if it's not a directory, however, then check if it has a file extension by finding the last full stop
	const char *file_ext = strrchr(filename, '.');
	// if it doesn't have an extension, return the default plain file icon
	if (file_ext == NULL) return DEFAULT_FILE_ICON; // 

	// if it _does_ have an extension, check that extension for matches
	icon = findIconMatch(file_ext + 1, FILE_EXT_ICONS); // note: +1 so we don't include the literal '.'

	// finally, if a match was found, return that icon. if it wasn't, then return the unknown icon.
	//	this way, the unknown file icon 󰡯 will only be used in the case of an _unknown_ extension,
	// 	rather than for all files without extensions, as eza does it
	return icon != NO_ICON ? icon : UNKNOWN_EXT_ICON; // 󰡯
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
