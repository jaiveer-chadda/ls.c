/// @file hash/hash.c

#include "hash.h"

typedef uint8_t byte_t;

#define DJB2_HASH_INIT ((hash_t)5381)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Implementation of the `djb2` hashing algorithm.
 *
 * Note: may not work with un-zeroed structs, due to differences in padding bytes.
 */
hash_t hash(const void *const input, const size_t size) {
	hash_t out = DJB2_HASH_INIT;

	for (size_t i = 0; i < size; i++) {
		//	 = (out * 33) + byte
		//	+= (out * 32) + input[i]
		out += (out << 5) + *((byte_t*)input + i);
	}

	return out;
}

/**
 * @brief Implementation of the `djb2` hashing algorithm, for strings.
 */
hash_t hashstr(const char *const string) {
	hash_t out = DJB2_HASH_INIT;

	for (const byte_t *pbyte = (byte_t*)string; *pbyte != '\0'; pbyte++) {
		out += (out << 5) + *pbyte;
	}

	return out;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
