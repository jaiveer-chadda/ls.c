/// @file utils/malloc.h

#ifndef UTILS__MALLOC_H
#define UTILS__MALLOC_H

#include <stdlib.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define E__DEBUG_ARGS		\
		const char *const file,	\
		const char *const func,	\
		const int lineno

#	define E__DEBUG_PARAMS \
		__FILE__, __func__, __LINE__

	void *e__malloc	(E__DEBUG_ARGS, size_t size);
	void *e__calloc	(E__DEBUG_ARGS, size_t count, size_t size);
	void *e__realloc(E__DEBUG_ARGS, void *ptr, size_t size);
	void  e__free	(E__DEBUG_ARGS, void *ptr);
	void  e__checkMemLeak(void);

#	define emalloc(size			) e__malloc	(E__DEBUG_PARAMS, size		 )
#	define ecalloc(count, size	) e__calloc	(E__DEBUG_PARAMS, count, size)
#	define erealloc(ptr	, size	) e__realloc(E__DEBUG_PARAMS, ptr  , size)
#	define efree(ptr			) e__free	(E__DEBUG_PARAMS, ptr		 )
#	define checkMemLeak() e__checkMemLeak()

#else
	void *e__malloc(size_t size);
	void *e__calloc(size_t count, size_t size);
	void *e__realloc(void *ptr, size_t size);
	void  e__free(void *ptr);

#	define emalloc(size			) e__malloc	(size		)
#	define ecalloc(count, size	) e__calloc	(count, size)
#	define erealloc(ptr	, size	) e__realloc(ptr  , size)
#	define efree(ptr			) e__free	(ptr		)
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

#endif /* !UTILS__MALLOC_H */
