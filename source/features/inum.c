/// @file features/inum.c

#include <stdio.h>

#include "malloc.h"
#include "form/formatting.h"
#include "graphics/graphics.h"

/// Approximately multiplies a number by 1.5
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

#define INIT_INUM_COUNT 8

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const Colour INUM_COLOURS[] = {
	toColour( .fg = 193 ),
	toColour( .fg = 157 ),
	toColour( .fg = 115 ),
	toColour( .fg = 116 ),
	toColour( .fg =  81 ),
	toColour( .fg =  37 ),
};

static const size_t INUM_COLOURS_LEN = sizeof(INUM_COLOURS) / sizeof(INUM_COLOURS[0]);

static bool
	inited = false,
	sorted = false;

static ino_t *all_inums;
static uint32_t
	inum_store_count = 0,
	inum_alloc_count = 0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void initInums(void) {
	inited = true;

	all_inums = emalloc(sizeof(ino_t) * INIT_INUM_COUNT);
	inum_store_count = inum_alloc_count = INIT_INUM_COUNT;
}

void processInum(ino_t inum) {
	if (!inited) initInums();

	if (inum_store_count + 1 > inum_alloc_count) {
		const uint32_t new_count = MULT_BY_1_5(inum_alloc_count);
		all_inums = erealloc(all_inums, sizeof(ino_t) * new_count);

		inum_alloc_count = new_count;
	}

	all_inums[inum_store_count++] = inum;
}

/* ——————————————————————————————————————————————————— */

static inline int compareInums(const void *inp1, const void *inp2) {
	return
		(*((const ino_t*)inp1) > *((const ino_t*)inp2)) -
		(*((const ino_t*)inp1) < *((const ino_t*)inp2));
}

/* ——————————————————————————————————————————————————— */

void print_inum(const FileStat *const pFS) {
	if (!sorted) qsort(all_inums, inum_store_count, sizeof(ino_t), compareInums);

	const ino_t *elem = bsearch(&(pFS->inum), all_inums, inum_store_count, sizeof(ino_t), compareInums);
	const uint64_t idx = elem != NULL ? elem - all_inums : 0llu;

	printf("%s" "%*llu" "%s",
		getcol(INUM_COLOURS[(idx * INUM_COLOURS_LEN) / inum_store_count]),
		getLen(FI_inum),
		pFS->inum,
		FIELD_PAD
	);
}
