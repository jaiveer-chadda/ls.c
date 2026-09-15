/// @file utils/strbuilder.h

#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stddef.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct b__strbuilder *StringBuilder;

StringBuilder b__init(const size_t size);

#define arg0__sb_init()		b__init((size_t)(0UL))
#define arg1__sb_init(len)	b__init((size_t)(len))

#define sb_init__DISPATCH(_1, NAME, ...) NAME
#define sb_init(...) sb_init__DISPATCH(__VA_ARGS__ __VA_OPT__(,) arg1__sb_init, arg0__sb_init)(__VA_ARGS__)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STRBUILDER_H */
