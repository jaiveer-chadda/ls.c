/// @file utils/malloc.c

#include <stdio.h>
#include <errno.h>
#include <string.h> // strerror()

#include "malloc.h"
#include "model/stat-model.h" // argv0

void* emalloc(size_t obj_size) {
	void *ptr = malloc(obj_size);
	const int malloc_errno = errno;

	if (ptr == NULL) {
		fprintf(stderr, "%s: %s", argv0, strerror(malloc_errno));
		exit(EXIT_FAILURE);
	}

	return ptr;
}
