/// @file options/usage.c

#include <stdio.h>
#include <stdlib.h>
#include "options.h"

void usage(const int exit_code) {
	// fputs("\33[31musage\33[m\n", stderr);
	exit(exit_code);
}
