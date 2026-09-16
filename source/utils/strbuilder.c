/// @file utils/strbuilder.c

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "malloc.h"
#include "strbuilder.h"

/* —— Definitions —————————————————————————————————————————————————————————————————————————————————————————————————— */

struct b__strbuilder {
	char *root, *head;
	size_t size;
};

/* ——————————————————————————————————————————————————————————— */

#if !__bool_true_false_are_defined
#	define true 1
#	define false 0
#endif

#ifdef MULT_BY_1_5
#	undef MULT_BY_1_5
#endif

/**
 * @brief Approximately multiply a number by 1.5.
 *
 * This version differs to the one defined in `malloc.h` in the case where `var` is `0`.
 *
 * ---
 *
 * @returns
 * 	- `var == 0` → `var = 1`
 *
 *	- `var == 1` → `var = 1`
 *
 *	- `var >= 2` → `var += (var >> 1)`
 */
#define MULT_BY_1_5(var)\
	((var) += ((var) <= 1 ? 1 : (var) >> 1)) \

/** @brief Find the current strlen of the string stored at `p_sb` */
#define length(p_sb) ((size_t)((p_sb)->head - (p_sb)->root))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Static Functions ————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void sb_realloc(StringBuilder p_strb, const size_t increase) {
	// If we already have enough memory, dont try adding any more.
	if (p_strb->size >= length(p_strb) + increase) return;

	// Keep multiplying the size until we have enough allocated memory to fit the requested amount.
	while (p_strb->size < length(p_strb) + increase) MULT_BY_1_5(p_strb->size);
	assert(p_strb->size > 0);

	// Note down how man bytes we've written to memory already,
	//	since this info won't be correct if `root` changes during reallocation.
	const size_t len = length(p_strb);

	// Reallocate as much memory as we need.
	// Note: If `size` was left uninitialised (i.e. as `0`), then `root` will be `NULL`.
	//	 When `realloc` is given `NULL` as its first argument, it acts like `malloc`, and assigns new memory for us.
	p_strb->root = erealloc(p_strb->root, p_strb->size);

	// Move the head of the string to the new location of `root`.
	p_strb->head = p_strb->root + len;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— sb_init() & sb_free() ———————————————————————————————————————————————————————————————————————————————————————— */

StringBuilder b__init(const size_t size) {
	StringBuilder p_strb = emalloc(sizeof(struct b__strbuilder));
	char *const root = size != 0 ? emalloc(size) : NULL;

	*p_strb = (struct b__strbuilder){
		.root = root, .head = root,
		.size = size
	};

	return p_strb;
}

/* ——————————————————————————————————————————————————— */

void sb_free(StringBuilder p_strb) {
	if (p_strb->root != NULL) {
		efree((void*)p_strb->root);
	}

	efree((void*)p_strb);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Adder Functions —————————————————————————————————————————————————————————————————————————————————————————————— */

size_t b__addstr(StringBuilder p_strb, const char *const src, const size_t size) {
	const size_t size_ = size > 0 ? size : strlen(src);
	sb_realloc(p_strb, size_);

	memcpy(p_strb->head, src, size_);
	p_strb->head += size_;

	return size_;
}

/* ——————————————————————————————————————————————————— */

size_t sb_addchr(StringBuilder p_strb, const char chr) {
	sb_realloc(p_strb, 1);

	*p_strb->head++ = chr;
	return 1;
}

/* ——————————————————————————————————————————————————— */

size_t sb_addcol(StringBuilder p_strb, const Colour col) {
	uint8_t col_size = 0;
	const char *const ansi_str = getcollen(col, &col_size);

	return sb_addstr(p_strb, ansi_str, col_size);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Output Functions ————————————————————————————————————————————————————————————————————————————————————————————— */

size_t sb_fputsf(StringBuilder p_strb, FILE *const file, const bool do_free) {
	sb_realloc(p_strb, 1);
	*p_strb->head = '\0';

	fputs(p_strb->root, file);

	const size_t len = length(p_strb);
	if (do_free) sb_free(p_strb);

	return len;
}

/* ——————————————————————————————————————————————————— */

char *sb_strdup(StringBuilder p_strb) {
	sb_realloc(p_strb, 1);
	*p_strb->head++ = '\0';

	char *const output = emalloc(length(p_strb));
	memcpy(output, p_strb->root, length(p_strb));

	sb_free(p_strb);
	return output;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Util Functions ——————————————————————————————————————————————————————————————————————————————————————————————— */

size_t sb_length(StringBuilder p_strb) { return length(p_strb); }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore strb
