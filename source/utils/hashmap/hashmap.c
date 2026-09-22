/// @file utils/hashmap/hashmap.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./hashmap.h"
#include "./hash/hash.h"

/* —— Macro Definitions ———————————————————————————————————————————————————————————————————————————————————————————— */

#define HASH_TABLE_SIZE 128

/// Find the location in the hash table where this key would be stored.
#define keyHash(key, ksize) (hash((key), (ksize)) % HASH_TABLE_SIZE)

/* —— Typedefs & Structs ——————————————————————————————————————————————————————————————————————————————————————————— */

typedef LList bucket_t;

/// @brief The internal struct to which the `HashMap` type points.
struct hm__hashmap {
	bucket_t *table; // array of buckets
};

/// @brief A key-value pair.
typedef struct kvpair_t {
	void *val;
	void *key; size_t ksize;
} kvpair_t;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— hm_init() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

HashMap hm_init(void) {
	HashMap hmap = malloc(sizeof(struct hm__hashmap));
	hmap->table = calloc(HASH_TABLE_SIZE, sizeof(bucket_t));
	return hmap;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— hm_free() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void hm__free_bucket(bucket_t bucket) {
	// if the bucket is uninitialised, then there's nothing to free
	if (bucket == NULL) return;

	ll_iter_reset(); // initialise the bucket iteration
	kvpair_t *pkv_pair;

	// iterate through the linked list, getting a pointer to another key-value pair each time
	while (( pkv_pair = (kvpair_t*)ll_iter(bucket) )) {
		if (pkv_pair == NULL) continue;

		// free the memory allocated for the key, then the pair as a whole
		if (pkv_pair->key != NULL) free(pkv_pair->key);
		free(pkv_pair);
	}

	ll_free(bucket);
}

/* —————————————————————————————————————————————————— */

void hm_free(HashMap map) {
	if (map == NULL) return;

	if (map->table != NULL) {
		// iterate over all buckets in the table, and free their constituent parts
		for (int i = 0; i < HASH_TABLE_SIZE; i++) hm__free_bucket(map->table[i]);
		free(map->table); // free the table array
	}

	free(map); // finally, free the struct holding the hashmap itself
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— hm_add() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

void hm_add(HashMap map, const void *const key, const size_t ksize, const void *const value) {
	// get a pointer to the bucket in which we should store this key
	bucket_t *bucket = &map->table[keyHash(key, ksize)];
	// if the bucket doesn't exist yet, then initialise a new one
	if (*bucket == NULL) *bucket = ll_init();

	// allocate memory for the key-value pair
	kvpair_t *pair = malloc(sizeof(kvpair_t));
	*pair = (kvpair_t){
		// allocate some more memory so the key can be duplicated and stored
		.key = memcpy(malloc(ksize), key, ksize),
		.ksize = ksize,
		.val = (void*)value
	};

	// add the key-value pair to the bucket (the linked list)
	ll_append(*bucket, pair);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— hm_get() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

void *hm_get(HashMap map, const void *const key, const size_t ksize) {
	// find the bucket which this key should be stored in
	const bucket_t bucket = map->table[keyHash(key, ksize)];

	// if a bucket doesn't exist for this key's hash, then we know the key isn't in the hashmap
	if (bucket == NULL) return NULL;

	ll_iter_reset(); // initialise the iteration
	const kvpair_t *elem;

	// iterate through the linked list, and check each stored key against the inputted key
	while (( elem = (kvpair_t*)ll_iter(bucket) )) {
		if (ksize == elem->ksize && memcmp(key, elem->key, ksize) == 0) {
			return elem->val;
		}
	}

	// if we couldn't find any keys that matched the inputted key, then that key isn't in the hashmap either
	return NULL;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— hm_pop() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

void *hm_pop(HashMap map, const void *const key, const size_t ksize) {
	// get a pointer to the bucket in which this key is stored
	bucket_t bucket = map->table[keyHash(key, ksize)];

	if (bucket == NULL) return NULL; // key not in mapping

	const kvpair_t *elem;
	ll_iter_reset();
	idx_t idx = -1;

	while (( elem = (kvpair_t*)ll_iter(bucket) )) {
		if (ksize != elem->ksize || memcmp(key, elem->key, ksize) != 0) continue;

		void *retval = elem->val;

		free(elem->key);			// free the memory allocated for the key
		free((void*)elem);			// then free it for the pair
		(void)ll_pop(bucket, idx);	// then remove this pair from the bucket entirely
		(void)ll_iter_reset();		// finally, make sure the iteration is reset for next time

		return retval;
	}

	return NULL; // key not found
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
