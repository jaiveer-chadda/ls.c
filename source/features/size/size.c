/// @file features/size/size.c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "../../model/stat-model.h"
#include "size.h"

#define NO_SIZE_STR "-"

void parseSize(char *size_str, char *size_unit, const size_t size, const dev_t rdev) {
	const int maj = major(rdev), min = minor(rdev);

	if (maj + min != 0) {
		sprintf(size_str, "%d,%d", maj, min);
		*size_unit = ',';
		return;
	}

	if (size == 0) {
		strcpy(size_str, NO_SIZE_STR);
		*size_unit = '-';
		return;
	}

	const char SUFFIXES[] = "bkmgtpezyrq";	// spell:disable-line

	int unit = 0;
	long double abbr_size = (long double)size;

	while (abbr_size > 1000) {
		abbr_size /= 1000;
		unit++;
	}

	*size_unit = SUFFIXES[unit];
	sprintf(size_str, (unit == 0 ? "%.0Lf%c" : "%.1Lf%c"), abbr_size, *size_unit);
}
