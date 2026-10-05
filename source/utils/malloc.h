/// @file utils/malloc.h

#ifndef UTILS__MALLOC_H_
#define UTILS__MALLOC_H_

#include <stdlib.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define DEBUG_ARGS	, const char *const file, const char *const func, const int line
#	define DEBUG_PASSED	,					file,					func,			line
#	define DEBUG_PARAMS	,				  __FILE__,				  __func__,		  __LINE__
#else
#	define DEBUG_ARGS
#	define DEBUG_PARAMS
#	define DEBUG_PASSED
#endif

void  e__free(void *ptr DEBUG_ARGS);
void* e__malloc(size_t size DEBUG_ARGS);
void* e__calloc(size_t count, size_t size DEBUG_ARGS);
void* e__realloc(void *ptr, size_t size DEBUG_ARGS);

#define efree(ptr)				e__free((ptr) DEBUG_PARAMS)
#define emalloc(size)			e__malloc((size) DEBUG_PARAMS)
#define ecalloc(num, size)		e__calloc((num), (size) DEBUG_PARAMS)
#define erealloc(ptr, size)		e__realloc((ptr), (size) DEBUG_PARAMS)

/* —————————————————————————————————————————————————————————— */

/** @brief Approximately multiplies a number by 1.5, in place. */
#define MULT_BY_1_5(var) \
	((var) += (var) == 1 ? 1 : (var) >> 1)

/** @brief Approximately multiplies a number by 1.5, and returns the result. */
#define TIMES_1_5(var) \
	((var) == 1 ? 1 : (var) >> 1)

/* —————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
	void checkMemLeak(void);
	void e__alloced(const size_t count DEBUG_ARGS);
#	define alloced(count) e__alloced(count DEBUG_PARAMS)
#else
#	define checkMemLeak()
#	define alloced(count) (void)count
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !UTILS__MALLOC_H_ */
