/// @file utils/malloc.c

#include <stdio.h>
#include "malloc.h"

void* emalloc(size_t obj_size) {
	void *ptr = malloc(obj_size);

	if (ptr == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	return ptr;
}
