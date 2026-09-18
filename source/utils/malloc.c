/// @file utils/malloc.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"
#include "model/global.h"

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

static inline void *exitIfNull(void *ptr) {
	if (ptr != NULL) return ptr;

	print_error("%s: %s", argv0, strerror(errno));
	exit(EXIT_FAILURE);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE

#define E__DEBUG_ARGS		\
	const char *const file,	\
	const char *const func,	\
	const int lineno

#define E__ARGS_IGNORE \
	(void)file; (void)func; (void)lineno

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void *e__malloc(E__DEBUG_ARGS, size_t size) {
	E__ARGS_IGNORE;
	alloc_count++;
	return exitIfNull(malloc(size));
}

void *e__calloc(E__DEBUG_ARGS, size_t count, size_t size) {
	E__ARGS_IGNORE;
	alloc_count++;
	return exitIfNull(calloc(count, size));
}

void *e__realloc(E__DEBUG_ARGS, void *ptr, size_t size) {
	E__ARGS_IGNORE;
	// `reallocf` frees the original pointer if it fails
	return exitIfNull(reallocf(ptr, size));
}

/* ———————————————————————————————————————————————————————— */

void e__free(E__DEBUG_ARGS, void *ptr) {
	E__ARGS_IGNORE;
	free(ptr);
	free_count++;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#else /* !DEBUG_MODE */
void *e__malloc	(size_t size) 				{ alloc_count++; return exitIfNull(malloc(size))		; }
void *e__calloc	(size_t count, size_t size)	{ alloc_count++; return exitIfNull(calloc(count, size))	; }
void *e__realloc(void *ptr, size_t size)	{				 return exitIfNull(reallocf(ptr, size))	; }
void  e__free	(void *ptr)					{ free_count ++; free(ptr)								; }
#endif /* DEBUG_MODE */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
