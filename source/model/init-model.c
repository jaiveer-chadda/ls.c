/// @file model/init-model.c

#include "stat-model.h"

const char *const file_colour_esc[] = {
	// only unpack the escapes
	#define X(name, esc) esc,
	FILE_COLOUR_TABLE
	#undef X
};
