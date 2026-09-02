/// @file features/size/size.c

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "malloc.h"
#include "debugging.h"

#include "size.h"

#define CHECK_PRINTF_ERR() do {															\
	if (str_len < 0 || (size_t)str_len >= sizeof(sizestr)) {							\
		debug(WARNING, "snprintf: %s: %s (%d)", strerror(errno), size_str, str_len);	\
		*size_unit = UNIT_ERROR;														\
		return (char*)NULL;																\
	}																					\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

inline char *parseSize(char *const size_unit, const off_t size, const dev_t rdev) {
	sizestr size_str = "";

	if (rdev != 0) { // if there's any info in `rdev`, then display them instead of the `off_t`
		// the unit won't be displayed, but it's used here as a note to
		//  remember that the file size is in the maj,min format
		*size_unit = UNIT_MAJ_MIN;

		const dev_t maj = major(rdev), min = minor(rdev);
		const int str_len = snprintf(size_str, sizeof(sizestr), "%d" MAJ_MIN_SEP "%d", maj, min);

		// if `snprintf` fails, mark this size down as an error, and move on
		CHECK_PRINTF_ERR();

		size_str[str_len] = '\0';
		return memcpy(emalloc(str_len + 1), size_str, str_len + 1);
	}

	/* ———————————————————————————————————————————————————————————— */

	// if the size is 0, don't bother going through the formatting process
	if (size == 0) {
		// once again, this unit won't be displayed, but it's here to note that the size is 0
		*size_unit = UNIT_ZERO;
		return (char*)NULL;
	}

	/* ———————————————————————————————————————————————————————————— */

	const char SIZE_UNITS[] = {
		UNIT_BYTE, UNIT_KILO, UNIT_MEGA, UNIT_GIGA, UNIT_TERA, UNIT_PETA,
		UNIT_EXA, UNIT_ZETA, UNIT_YOTTA, UNIT_RONNA, UNIT_QUETTA
	};

	size_t unit_idx = 0;
	long double abbr_size = (long double)size;

	while (abbr_size >= 1000 && unit_idx++ < sizeof(SIZE_UNITS)) {
		abbr_size /= 1000;
	}

	/* ———————————————————————————————————————————————————————————— */

	*size_unit = SIZE_UNITS[unit_idx];

	const int str_len = snprintf(size_str, sizeof(sizestr), *size_unit == UNIT_BYTE ? "%.0Lf" : "%.1Lf", abbr_size);
	CHECK_PRINTF_ERR();

	size_str[str_len] = '\0';
	return memcpy(emalloc(str_len + 1), size_str, str_len + 1);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
