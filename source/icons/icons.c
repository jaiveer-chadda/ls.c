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

#define REACHED_END_OF_ICONS(icon) ( \
	((icon.pattern) == END_OF_ICONS.pattern	) && \
	((icon.icon)	== END_OF_ICONS.icon	))

#define IF_COLOUR(print) DO_COLOUR() ? print : ""

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

icon_t getIcon(const char *filename, const bool is_dir) {
	const Icon *ICON_ARRAY = (Icon *)(is_dir ? &DIR_ICONS : &FILENAME_ICONS);
	Icon icon = ICON_ARRAY[0];

	for (int i = 0; !REACHED_END_OF_ICONS(icon); icon = ICON_ARRAY[i++] ) {
		if (strcmp(icon.pattern, filename) == 0) return icon.icon;
	}

	if (is_dir) return DEFAULT_DIR_ICON;

	const char *file_ext = strrchr(filename, '.');
	if (file_ext == NULL) return DEFAULT_FILE_ICON;

	icon = EXT_ICONS[0];
	for (int i = 0; !REACHED_END_OF_ICONS(icon); icon = EXT_ICONS[i++] ) {
		if (strcmp(icon.pattern, file_ext + 1) == 0) return icon.icon;
	}

	return DEFAULT_FILE_ICON;
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
