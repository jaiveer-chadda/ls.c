/// @file utils/malloc.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// this is probably the closest I'm going to get to currying in C

#define DEFINE_ALLOC_FUNC(funcname, ...) do {				\
	void *r_ptr = funcname(__VA_ARGS__);					\
	const int errno_ = errno;								\
	\
	if (r_ptr == NULL) {									\
		fprintf(stderr, "%s: %s", argv0, strerror(errno_));	\
		exit(EXIT_FAILURE);									\
	}														\
	\
	return r_ptr;											\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void*  emalloc(size_t size				 )	{ DEFINE_ALLOC_FUNC(malloc, size		); }
void*  ecalloc(size_t count	, size_t size)	{ DEFINE_ALLOC_FUNC(calloc, count, size	); }
void* erealloc(void  *ptr	, size_t size)	{ DEFINE_ALLOC_FUNC(realloc, ptr, size	); }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
