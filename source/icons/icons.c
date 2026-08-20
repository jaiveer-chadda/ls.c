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
	const Icon *ICON_ARRAY = (Icon *)(is_dir ? &DIR_ICONS : &FILENAME_ICONS);

	icon_t icon = findIconMatch(filename, ICON_ARRAY);

	if (icon != NO_ICON	) return icon;
	if (is_dir			) return DEFAULT_DIR_ICON;

	const char *file_ext = strrchr(filename, '.');
	if (file_ext == NULL) return DEFAULT_FILE_ICON;

	icon = findIconMatch(file_ext + 1, EXT_ICONS);
	return icon != NO_ICON ? icon : UNKNOWN_FILE_ICON;
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
