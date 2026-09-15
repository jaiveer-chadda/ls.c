/// @file utils/strbuilder.h

#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stddef.h>
#include "graphics/colour/colour-object.h"

/* —— typedefs ————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct b__strbuilder *const StringBuilder;

/* —— function declarations ———————————————————————————————————————————————————————————————————————————————————————— */

StringBuilder b__init(const size_t size);
void sb_free(StringBuilder p_strb);

size_t sb_addchr(StringBuilder p_strb, const char chr);
size_t sb_addcol(StringBuilder p_strb, const Colour col);
size_t b__addstr(StringBuilder p_strb, const char *const src, const size_t size);

/* —— sb_init() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

#define arg0__sb_init(	 ) b__init((size_t)(0UL))
#define arg1__sb_init(len) b__init((size_t)(len))

#define sb_init(...) sb_init__DISPATCH(__VA_ARGS__ __VA_OPT__(,) arg1__sb_init, arg0__sb_init)(__VA_ARGS__)
#define sb_init__DISPATCH(_1, NAME, ...) NAME

/* —— sb_addstr() ——————————————————————————————————— */

#define arg2__sb_addstr(p_strb, src		 ) b__addstr((StringBuilder)(p_strb), (const char *const)(src), (size_t)(0))
#define arg3__sb_addstr(p_strb, src, size) b__addstr((StringBuilder)(p_strb), (const char *const)(src), (size_t)(size))

#define sb_addstr__DISPATCH(_1, _2, _3, NAME, ...) NAME
#define sb_addstr(...) sb_addstr__DISPATCH(__VA_ARGS__, arg3__sb_addstr, arg2__sb_addstr, DUMMY)(__VA_ARGS__)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STRBUILDER_H */

// spell:ignore strb
