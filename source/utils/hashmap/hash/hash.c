/// @file hash/hash.c

#include "hash.h"

typedef unsigned char byte_t;

/**
 * @brief Implementation of the `djb2` hashing algorithm.
 *
 * Note: may not work with un-zeroed structs, due to differences in padding bytes.
 */
uint64_t hash(const void *const input, const size_t size) {
	uint64_t hashed = 5381;

	for (size_t i = 0; i < size; i++) {
		hashed = ((hashed << 5) + hashed) + *((byte_t*)input + i);
	}

	return hashed;
}
