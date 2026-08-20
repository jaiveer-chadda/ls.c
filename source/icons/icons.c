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

static inline icon_t getDirIcon(const char *filename) {
	Icon icon = DIR_ICONS[0];
	for (int i = 0; !REACHED_END_OF_ICONS(icon); icon = DIR_ICONS[i++] ) {
		if (strcmp(icon.pattern, filename) == 0) return icon.icon;
	}
	return DEFAULT_DIR_ICON;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline icon_t getFileIcon(const char *filename) {
	(void) filename;
	return DEFAULT_FILE_ICON;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

icon_t getIcon(const char *filename, const bool is_dir) {
	return (is_dir ? getDirIcon : getFileIcon)(filename);
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
