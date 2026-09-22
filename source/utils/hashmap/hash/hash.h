/// @file hash/hash.h

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <inttypes.h>

uint64_t hash(const void *const input, const size_t size);

#endif /* !HASH_H */
