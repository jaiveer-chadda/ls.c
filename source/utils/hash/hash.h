/// @file hash/hash.h

#ifndef HASH_H
#define HASH_H

#include <stddef.h> // size_t
#include <inttypes.h> // uint64_t

typedef uint64_t hash_t;

hash_t	  hash(const void *const input, const size_t size);
hash_t hashstr(const char *const string);

#endif /* !HASH_H */
