/// @file icons/icons.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "icons.h"
#include "options/options.h"
#include "graphics/graphics.h"

#define IF_COLOUR(print) DO_COLOUR() ? print : ""

icon_t getIcon(const char *filename) {
	(void) filename;
	return L'';
}

void printIcon(const icon_t icon, const FileColour file_col) {
	if (printf(
			"%s%s%s" "%lc" "%s",
			IF_COLOUR(CSI), file_colour_esc[file_col], IF_COLOUR(END), icon, IF_COLOUR(RESET)
		) < 0
	) fputs(strerror(errno), stderr);
}
