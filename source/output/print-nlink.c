/// @file graphics/print-nlink.c

#include <stdio.h>
#include <string.h>

#include "../options/options.h"
#include "../model/stat-model.h"
#include "../graphics/graphics.h"

void printNLink(const nlink_t *nlink, const mode_t *mode, bool *hardln_hl) {
	if (!do_nlink) return;

	char output[16];
	// using "output" to calculate the strlen of nlink here
	// then reusing it to hold the colour down below
	sprintf(output, "%d", *nlink);
	short int link_len = (short int)strlen(output);

	if (*mode & S_IFDIR)	strcpy(output, NLINK_COL_DIR);	// directory
	else if (*nlink == 1)	strcpy(output, NLINK_COL_REG_1);// file w 1 link
	else {													// file w >1 link
		strcpy(output, NLINK_COL_REG_MORE);
		*hardln_hl = true;
	}

	printf("%*s%s%d%s", (int)field_lengths.nlink - link_len, "", output, *nlink, RESET FIELD_PAD);
}
