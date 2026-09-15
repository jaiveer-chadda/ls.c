/// @file utils/strbuilder.c

#include <stddef.h>

#include "malloc.h"
#include "strbuilder.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

struct b__strbuilder {
	char *root, *head;
	size_t size;
};

#define length(p_sb) ((size_t)((p_sb)->head - (p_sb)->root))

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

// spell:ignore strb
