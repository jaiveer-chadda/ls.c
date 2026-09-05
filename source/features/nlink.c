/// @file features/nlink.c

#include <stdio.h>
#include "form/formatting.h"

void print_nlink(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL;
	printf(fields[FI_nlink].fmt_p, getLen(FI_nlink), valid ? pFS->s->st_nlink : 0, FIELD_PAD);
}
