/// @file features/inum.c

#include <stdio.h>

#include "malloc.h"
#include "form/formatting.h"
#include "graphics/graphics.h"

#define INIT_INUM_COUNT 8

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static const Colour INUM_COLOURS_S[] = { INUM_COLOURS }; // the `_S` is for static
static const size_t INUM_COLOURS_LEN = sizeof(INUM_COLOURS_S) / sizeof(INUM_COLOURS_S[0]);

static ino_t *all_inums;
static uint32_t store_count = 0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void processInum(const ino_t inum) {
	static bool inited = false;
	static uint32_t alloc_count = 0;

	if (!inited && ( inited = true )) {
		all_inums = emalloc(sizeof(ino_t) * ( alloc_count = INIT_INUM_COUNT ));
	}

	if (store_count + 1 > alloc_count) {
		all_inums = erealloc(all_inums, sizeof(ino_t) * MULT_BY_1_5(alloc_count));
	}

	all_inums[store_count++] = inum;
}

/* ——————————————————————————————————————————————————— */

#define getIno(inp) (*((const ino_t *const)(inp)))

static inline int compareInums(const void *inp1, const void *inp2) {
	return
		(getIno(inp1) > getIno(inp2)) -
		(getIno(inp1) < getIno(inp2));
}

/* ——————————————————————————————————————————————————— */

void print_inum(const FileStat *const pFS) {
	static bool sorted = false;

	if (!sorted && ( sorted = true )) {
		qsort(all_inums, store_count, sizeof(ino_t), compareInums);
	}

	const ino_t *const inum = bsearch(&(pFS->inum), all_inums, store_count, sizeof(ino_t), compareInums);
	const uint64_t idx = inum != NULL ? inum - all_inums : 0llu;

	printf("%s" "%*llu" "%ls",
		getcol(INUM_COLOURS_S[(idx * INUM_COLOURS_LEN) / store_count]),
		getLen(FI_inum),
		pFS->inum,
		FIELD_PAD
	);
}
