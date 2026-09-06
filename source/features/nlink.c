/// @file features/nlink.c

#include <stdio.h>
#include "form/formatting.h"

void print_nlink(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL;
	printf(
		valid ? fields[FI_nlink].fmt_p : "%*c%ls",
		getLen(FI_nlink),
		valid ? pFS->s->st_nlink : '-',
		FIELD_PAD
	);
}
