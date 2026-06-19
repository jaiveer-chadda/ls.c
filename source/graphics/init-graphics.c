/// @file graphics/init-graphics.c

#include "graphics.h"

// only unpack the escape characters
#define X(name, esc) esc,
const char *const file_colour_esc[] = { FILE_COLOUR_TABLE };
const char *const perm_colour_esc[] = { PERM_COLOUR_TABLE };
const char *const time_colour_esc[] = { TIME_COLOUR_TABLE };
const char *const size_colour_esc[] = { SIZE_COLOUR_TABLE };
#undef X
