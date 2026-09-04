/// @file graphics/init-graphics.c

#include "graphics.h"

// only unpack the escape characters
#define X(name, esc) (esc),
const Colour file_colour_esc[] = { FILE_COLOUR_TABLE };
const Colour perm_colour_esc[] = { PERM_COLOUR_TABLE };
const Colour size_colour_esc[] = { SIZE_COLOUR_TABLE };
const Colour time_colour_esc[] = { TIME_COLOUR_TABLE };
#undef X
