/// @file features/devno.c

#include <stdio.h>
#include <sys/types.h>

#include "form/formatting.h"
#include "options/options.h"

void print_dev_no(const FileStat *const pFS) {

	/* —— invalid ——————————————————————————————————————— */

	if (pFS->s == NULL) {
		printf("%s%*c%ls", getcol(PUNCT), getLen(FI_dev_no), '-', FIELD_PAD);
		return;
	}

	/* —— regular ——————————————————————————————————————— */

	if (!DO_DEVNO_MAJMIN()) {
		printf("%s%*u%ls", getcol(DEVNO_COLOUR), getLen(FI_dev_no), pFS->s->st_dev, FIELD_PAD);
		return;
	}

	/* —— maj,min ——————————————————————————————————————— */

	const dev_t
		maj = major(pFS->s->st_dev),
		min = minor(pFS->s->st_dev);

	// print the maj,min string into a buffer, and then align that string to the max length
	const int majmin_size = snprintf(NULL, 0, "%d,%d", maj, min);
	const int front_pad = getLen(FI_dev_no) - majmin_size;

	const char
		*const major_ansi = getcol(DEVNO_MAJ_COLOUR),
		*const comma_ansi = getcol(PUNCT),
		*const minor_ansi = getcol(DEVNO_COLOUR);

	printf("%*s" "%s%d" "%s," "%s%d" "%ls",
		front_pad , "",		// field alignment
		major_ansi, maj,	// major size
		comma_ansi,			// comma
		minor_ansi, min,	// minor size
		FIELD_PAD			// end of field padding
	);
}
