/// @file features/inum.c

#include <stdio.h>
#include "form/formatting.h"

void print_inum(const FileStat *const pFS) {
	printf(fields[FI_inum].fmt_p, getLen(FI_inum), pFS->inum, FIELD_PAD);
}
