/// @file utils/strbuilder.c

#include <stddef.h>

#include "malloc.h"
#include "strbuilder.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

struct sb__strbuilder {
	char *root, *head;
	size_t size;
};

#define length(p_sb) ((size_t)((p_sb)->head - (p_sb)->root))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

StringBuilder sb_init(const size_t size) {
	StringBuilder p_strb = emalloc(sizeof(struct sb__strbuilder));
	char *const root = emalloc(size);

	*p_strb = (struct sb__strbuilder){
		.root = root, .head = root,
		.size = size
	};

	return p_strb;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore strb
