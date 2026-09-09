/// @file features/size/size.c

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#include "malloc.h"
#include "debugging.h"
#include "form/formatting.h"
#include "options/options.h"

#define CHECK_PRINTF_ERR() do {															\
	if (str_len < 0 || (size_t)str_len >= sizeof(sizestr)) {							\
		debug(WARNING, "snprintf: %s: %s (%d)", strerror(errno), size_str, str_len);	\
		*size_unit = UNIT_ERROR;														\
		return (char*)NULL;																\
	}																					\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *parseSize(unit_t *const size_unit, const off_t size, const dev_t rdev) {
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
		setLen(FI_size_str, str_len);

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
	setLen(FI_size_str, str_len + (DO_PRINT_SIZE_UNIT(*size_unit) ? 1 : 0));

	return memcpy(emalloc(str_len + 1), size_str, str_len + 1);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getSizeColours(const unit_t unit, SizeColour *const size_col, SizeColour *const unit_col) {
	const bool do_unit = unit_col != NULL;
	switch (unit) {
		case UNIT_BYTE: *size_col = SC_BB; if (do_unit) *unit_col = SC_UB; break;
		case UNIT_KILO: *size_col = SC_BK; if (do_unit) *unit_col = SC_UK; break;
		case UNIT_MEGA: *size_col = SC_BM; if (do_unit) *unit_col = SC_UM; break;
		case UNIT_GIGA: *size_col = SC_BG; if (do_unit) *unit_col = SC_UG; break;
		default		  : *size_col = SC_BT; if (do_unit) *unit_col = SC_UT; break;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SIZE_IS_VALID(pFS) (			\
	(pFS)->f != NULL &&					\
	(pFS)->f->size_str != NULL &&		\
	(pFS)->f->size_unit != UNIT_ERROR	\
)

void print_size(const FileStat *const pFS) {
	if (!SIZE_IS_VALID(pFS) || pFS->f->size_unit == UNIT_MAJ_MIN) {
		printf("%s" "%*c" "%ls", getcol(PUNCT), getLen(FI_size), '-', FIELD_PAD);
		return;
	}

	const off_t size = pFS->s->st_size;
	const int size_len = snprintf(NULL, 0, "%'lld", size);

	SizeColour size_col;
	getSizeColours(pFS->f->size_unit, &size_col, NULL);

	printf("%*s" "%s%'lld" "%ls",
		getLen(FI_size) - size_len, "",
		getcol(size_colour_esc[size_col]), size,
		FIELD_PAD
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void printMajMinSize(const FileStat *const pFS) {
	const dev_t maj = major(pFS->s->st_rdev), min = minor(pFS->s->st_rdev);
	const size_t size_len = strlen(pFS->f->size_str);

	printf("%*s" "%s%d" "%s," "%s%d" "%ls",
		(getLen(FI_size_str) - (int)size_len), "",
		MAJ_COL_ANSI, maj,
		PUNCT_ANSI,
		MIN_COL_ANSI, min,
		FIELD_PAD
	);

	setActive(MIN_COLOUR);
}

/* ———————————————————————————————————————————————————————————————————— */

void print_size_str(const FileStat *const pFS) {
	if (!SIZE_IS_VALID(pFS)) {
		printf("%s" "%*s" "%ls", getcol(PUNCT), getLen(FI_size_str), NO_SIZE_STR, FIELD_PAD);
		return;
	}

	const char *const str = pFS->f->size_str;
	const unit_t unit = pFS->f->size_unit;

	if (unit == UNIT_MAJ_MIN) { printMajMinSize(pFS); return; }

	const bool do_unit = DO_PRINT_SIZE_UNIT(unit);
	const int size_len = (int)strlen(str);
	SizeColour size_col, unit_col;

	getSizeColours(unit, &size_col, &unit_col);

	ansi_t size_col_ansi;
	uint8_t size_col_len = 0;
	const char *const size_col_ptr = getcollen(size_colour_esc[size_col], &size_col_len);
	memcpy(size_col_ansi, size_col_ptr, size_col_len);

	printf("%*s" "%s%s%s" "%s%s" "%s%ls",
		(getLen(FI_size_str) - size_len) - do_unit, "", // padding
		S_ISDIR(pFS->mode) ? ANSI_IFCOL(DIM) : "", size_col_ansi, str,
		do_unit ? getcol(size_colour_esc[unit_col]) : "", do_unit ? (char[]){ unit, '\0' } : "",
		IFCOLOUR(RESET), 
		FIELD_PAD
	);

	setActive(RESET_ALL);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
