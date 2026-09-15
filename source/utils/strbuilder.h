/// @file utils/strbuilder.h

#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stddef.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct sb__strbuilder *StringBuilder;

StringBuilder sb_init(const size_t size);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STRBUILDER_H */
