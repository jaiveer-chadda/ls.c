/// @file utils/malloc.h

#ifndef MALLOC_INITIALISED
#define MALLOC_INITIALISED

#include <stdlib.h>

void* emalloc(size_t size);
void* ecalloc(size_t count, size_t size);
void* erealloc(void *ptr, size_t size);

void efree(void *ptr);

#ifdef DEBUG_MODE
	void e__checkMemLeak(void);
#	define checkMemLeak() e__checkMemLeak()
#else
#	define checkMemLeak()
#endif

#endif /* !MALLOC_INITIALISED */
