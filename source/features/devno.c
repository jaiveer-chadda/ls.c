/// @file features/devno.c

#include <stdio.h>
#include <sys/types.h>

#include "form/formatting.h"
#include "options/options.h"

#define BUFSIZE 32

void print_dev_no(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL;

	if (!valid || !DO_DEVNO_MAJMIN()) {
		printf("%*c%s", getLen(FI_dev_no), valid ? pFS->s->st_dev : '-', FIELD_PAD);
		return;
	}

	const int32_t maj = major(pFS->s->st_dev), min = minor(pFS->s->st_dev);
	char buf[BUFSIZE] = "";

	// print the maj,min string into a buffer, and then align that string to the max length
	snprintf(buf, BUFSIZE, "%d,%d", maj, min);
	printf("%*s%s", getLen(FI_dev_no), buf, FIELD_PAD);
}
