/// @file model/init-model.c

#include "stat-model.h"

// only unpack escapes
#define X(name, esc) esc,
const char *const file_colour_esc[] = { FILE_COLOUR_TABLE };
const char *const perm_colour_esc[] = { PERM_COLOUR_TABLE };
#undef X
