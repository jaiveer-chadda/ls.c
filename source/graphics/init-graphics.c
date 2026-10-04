/// @file graphics/init-graphics.c

#include "graphics.h"

// only unpack the escape characters
#define X(name, esc) (esc),
const Colour file_colour_esc[FC_COUNT] = { FILE_COLOUR_TABLE };
const Colour perm_colour_esc[PC_COUNT] = { PERM_COLOUR_TABLE };
const Colour size_colour_esc[SC_COUNT] = { SIZE_COLOUR_TABLE };
const Colour time_colour_esc[TC_COUNT] = { TIME_COLOUR_TABLE };
#undef X
