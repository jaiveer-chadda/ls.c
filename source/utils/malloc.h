/// @file utils/malloc.h

#ifndef UTILS__MALLOC_H_
#define UTILS__MALLOC_H_

#include <stdlib.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void* emalloc(size_t size);
void* ecalloc(size_t count, size_t size);
void* erealloc(void *ptr, size_t size);

void efree(void *ptr);

/* —————————————————————————————————————————————————————————— */

/// Approximately multiplies a number by 1.5, in place.
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

/// Approximately multiplies a number by 1.5, and returns the result.
#define TIMES_1_5(var) \
	((var) == 1 ? 1 : (var) >> 1)

/* —————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
	void e__checkMemLeak(void);
#	define checkMemLeak() e__checkMemLeak()
#else
#	define checkMemLeak()
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !UTILS__MALLOC_H_ */
