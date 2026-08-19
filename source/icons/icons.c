/// @file icons/icons.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "icons.h"

void getIcon(icon_t *icon, const char *filename) {
	(void) filename;
	*icon = L'';
}

void printIcon(const icon_t icon) {
	if (putwchar(icon) < 0) {
		fputs(strerror(errno), stderr);
	}
}
