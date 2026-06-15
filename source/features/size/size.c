/// @file features/size/size.c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "../../model/stat-model.h"

void parseSize(char *size_str, const size_t size, const dev_t rdev) {
	const int maj = major(rdev), min = minor(rdev);

	if (maj + min != 0) {
		sprintf(size_str, "%d,%d", maj, min);
		return;
	}

	if (size == 0) {
		strcpy(size_str, "-");
		return;
	}

	const char SUFFIXES[] = "\0kmgtpezyrq";	// spell:disable-line

	int suffix = 0;
	long double abbr_size = (long double)size;

	while (abbr_size > 1000) {
		abbr_size /= 1000;
		suffix++;
	}

	const char size_char = SUFFIXES[suffix];
	sprintf(size_str, (size_char == '\0' ? "%.0Lf%c" : "%.1Lf%c"), abbr_size, size_char);
}
