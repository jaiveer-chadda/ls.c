/// @file graphics/init-graphics.c

#include "graphics.h"

// only unpack the escape characters
#define X(name, esc) (esc),
const Colour file_colour_esc[FC_COUNT] = { FILE_COLOUR_TABLE };
const Colour perm_colour_esc[PC_COUNT] = { PERM_COLOUR_TABLE };
const Colour size_colour_esc[SC_COUNT] = { SIZE_COLOUR_TABLE };
const Colour time_colour_esc[TC_COUNT] = { TIME_COLOUR_TABLE };
#undef X

#define X(name, chr, colour) [name] = chr,
const char git_branch_chars[GBR_COUNT] = { GIT_BRANCH_TABLE };
#undef X

#define X(name, chr, colour) [name] = colour,
const Colour git_branch_colours[GBR_COUNT] = { GIT_BRANCH_TABLE };
#undef X

