/// @file features/devno.c

#include <stdio.h>
#include <sys/types.h>

#include "form/formatting.h"
#include "options/options.h"

void print_dev_no(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL;

	/* —— invalid ——————————————————————————————————————— */

	if (!valid) {
		printf("%s%*c%s", getcol(PUNCT), getLen(FI_dev_no), '-', FIELD_PAD);
		return;
	}

	/* —— regular ——————————————————————————————————————— */

	if (!DO_DEVNO_MAJMIN()) {
		printf("%s%*d%s", getcol(DEVNO_COLOUR), getLen(FI_dev_no), pFS->s->st_dev, FIELD_PAD);
		return;
	}

	/* —— maj,min ——————————————————————————————————————— */

	const int32_t maj = major(pFS->s->st_dev), min = minor(pFS->s->st_dev);

	// print the maj,min string into a buffer, and then align that string to the max length
	const int majmin_size = snprintf(NULL, 0, "%d,%d", maj, min);

	printf("%*s" "%s%d" "%s," "%s%d" "%s",
		getLen(FI_dev_no) - majmin_size, "", // alignment
		DEVNO_MAJ_ANSI, maj,	// major size
		PUNCT_ANSI,				// comma
		DEVNO_ANSI, min,		// minor size
		FIELD_PAD				// padding
	);

	setActive(DEVNO_COLOUR);
}
