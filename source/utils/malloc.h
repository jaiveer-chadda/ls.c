/// @file utils/malloc.h

#ifndef MALLOC_INITIALISED
#define MALLOC_INITIALISED

#include <stdlib.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
	void *e__malloc(size_t size);
	void *e__calloc(size_t count, size_t size);
	void *e__realloc(void *ptr, size_t size);
	void  e__free(void *ptr);
	void  e__checkMemLeak(void);
#	define checkMemLeak() e__checkMemLeak()
#else
	void *e__malloc(size_t size);
	void *e__calloc(size_t count, size_t size);
	void *e__realloc(void *ptr, size_t size);
	void  e__free(void *ptr);
#	define checkMemLeak()
#endif

/* —————————————————————————————————————————————————————————— */

/// Approximately multiplies a number by 1.5, in place.
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

/// Approximately multiplies a number by 1.5, and returns the result.
#define TIMES_1_5(var) \
	((var) == 1 ? 1 : (var) >> 1)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !MALLOC_INITIALISED */
