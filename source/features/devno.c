/// @file features/devno.c

#include <stdio.h>
#include "form/formatting.h"

void print_dev_no(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL;
	printf(fields[FI_dev_no].fmt_p, getLen(FI_dev_no), valid ? pFS->s->st_dev : 0, FIELD_PAD);
}
