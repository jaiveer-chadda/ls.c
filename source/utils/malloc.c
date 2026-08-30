/// @file utils/malloc.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "model/stat-model.h"
#include "debugging.h"

#ifdef DEBUG_MODE
#	define print_error(...) debug(ERROR, __VA_ARGS__)
#else
#	define print_error(...) fprintf(stderr, __VA_ARGS__)
#endif

static size_t alloc_count = 0;
static size_t free_count  = 0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void e__checkMemLeak(void) {
	if (free_count >  alloc_count) debug(FATAL, "huh?");
	if (free_count == alloc_count) return;

	debug(WARNING,
		"likely memory leak - times alloced = %zu, times freed = %zu (%lc = %zu)",
		alloc_count, free_count, L'Δ', alloc_count - free_count
	);
}

/* ———————————————————————————————————————————————————————— */

static inline void* exitIfNull(void *ptr, const int errno_) {
	if (ptr != NULL) return ptr;

	print_error("%s: %s", argv0, strerror(errno_));
	exit(EXIT_FAILURE);
}

/* ———————————————————————————————————————————————————————— */

void* emalloc(size_t size) {
	void *r_ptr = malloc(size);
	alloc_count++;
	return exitIfNull(r_ptr, errno);
}

void* ecalloc(size_t count, size_t size) {
	void *r_ptr = calloc(count, size);
	alloc_count++;
	return exitIfNull(r_ptr, errno);
}

void* erealloc(void *ptr, size_t size) {
	// `reallocf` frees the original pointer if it fails
	void *r_ptr = reallocf(ptr, size);
	return exitIfNull(r_ptr, errno);
}

/* ———————————————————————————————————————————————————————— */

void efree(void *ptr) {
	free(ptr);
	free_count++;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
