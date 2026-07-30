/// @file features/size/size.c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "../../model/stat-model.h"
#include "size.h"

inline void parseSize(sizestr size_str, char *size_unit, off_t *size, const dev_t rdev) {
	if (rdev != 0) { // if there's any info in `rdev`, then display them instead of the `off_t`
		*size = rdev;
		const int32_t maj = major(rdev), min = minor(rdev);

		sprintf(size_str, "%d" MAJ_MIN_SEP "%d", maj, min);
		// the "unit" won't be displayed, but it's used here as a note to
		//  remember that the file size is in the maj,min format
		*size_unit = UNIT_MAJ_MIN;
		return;
	}

	// if the size is 0, don't bother going through the formatting process
	if (*size == 0) {
		strcpy(size_str, NO_SIZE_STR);
		// once again, this unit won't be displayed, but it's here to note that the size is 0
		*size_unit = UNIT_ZERO;
		return;
	}

	/* ———————————————————————————————————————————————————————————— */

	const char SUFFIXES[] = {
		UNIT_BYTE,		// \0
		UNIT_KILO,		//  k
		UNIT_MEGA,		//  M
		UNIT_GIGA,		//  G
		UNIT_TERA,		//  T
		UNIT_PETA,		//  P
		UNIT_EXA,		//  E
		UNIT_ZETA,		//  Z
		UNIT_YOTTA,		//  Y
		UNIT_RONNA,		//  R
		UNIT_QUETTA,	//  Q
	};

	int unit_idx = 0;
	long double abbr_size = (long double)*size;

	while (abbr_size >= 1000 && unit_idx <= (int)sizeof(SUFFIXES) - 1) {
		abbr_size /= 1000;
		unit_idx++;
	}

	*size_unit = SUFFIXES[unit_idx];
	sprintf(size_str, unit_idx == 0 ? "%.0Lf" : "%.1Lf", abbr_size);
}
