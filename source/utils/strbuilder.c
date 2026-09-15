/// @file utils/strbuilder.c

#include <stddef.h>
#include <assert.h>

#include "malloc.h"
#include "strbuilder.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

struct b__strbuilder {
	char *root, *head;
	size_t size;
};

/* ——————————————————————————————————————————————————————————— */

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

StringBuilder b__init(const size_t size) {
	StringBuilder p_strb = emalloc(sizeof(struct b__strbuilder));
	char *const root = size != 0 ? emalloc(size) : NULL;

	*p_strb = (struct b__strbuilder){
		.root = root, .head = root,
		.size = size
	};

	return p_strb;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void sb_free(StringBuilder str) {
	if (str->root != NULL) efree((void*)str->root);
	efree((void*)str);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore strb
