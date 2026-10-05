/// @file utils/malloc.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"
#include "model/global.h"

#ifdef DEBUG_MODE
	static size_t alloc_count = 0, freed_count = 0;

#	define add_to_alloc(num) (alloc_count += (num))
#	define add_to_freed(num) (freed_count += (num))
#	define print_error(...) debug(ERROR, __VA_ARGS__)
#else
#	define add_to_alloc(num) (void)num
#	define add_to_freed(num) (void)num
#	define print_error(...) fprintf(stderr, __VA_ARGS__)
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
	void checkMemLeak(void) {
		if (freed_count >  alloc_count) debug(ERROR, "freed memory more times than allocated...?");
		if (freed_count == alloc_count) {
			debug(SUCCESS, "likely no memory leak - times alloced = %zu, times freed = %zu (%lc = %zd)",
				alloc_count, freed_count, L'Δ', (ssize_t)(alloc_count - freed_count)
			);
			return;
		}

		debug(WARNING, "likely memory leak - times alloced = %zu, times freed = %zu (%lc = %zd)",
			alloc_count, freed_count, L'Δ', (ssize_t)(alloc_count - freed_count)
		);
	}

	void alloced(const size_t count) {
		add_to_alloc(count);
	}
#endif

/* ———————————————————————————————————————————————————————— */

static inline void *exitIfNull(void *ptr) {
	if (ptr != NULL) return ptr;

	print_error("%s: fatal memory error: %s", argv0, strerror(errno));
	exit(EXIT_FAILURE);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void* emalloc(size_t size) {
	add_to_alloc(1);
	return exitIfNull(malloc(size));
}

void* ecalloc(size_t count, size_t size) {
	add_to_alloc(1);
	return exitIfNull(calloc(count, size));
}

void* erealloc(void *ptr, size_t size) {
	// `reallocf` frees the original pointer if it fails
	return exitIfNull(reallocf(ptr, size));
}

/* ———————————————————————————————————————————————————————— */

void efree(void *ptr) {
	free(ptr);
	add_to_freed(1);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
