/// @file output/print-nlink.c

#include <stdio.h>
#include <string.h>

#include "../options/options.h"
#include "../model/stat-model.h"
#include "../graphics/graphics.h"

#define IS_DIR(pMode) ((*pMode & S_IFMT) == S_IFDIR)

void printNLink(const nlink_t *nlink, const mode_t *mode, bool *is_hln) {
	if (!do_nlink) return;

	// using "output" to calculate the strlen of nlink here
	// then reusing it to hold the colour down below
	char output[16];
	sprintf(output, "%d", *nlink);

	const short int link_len = (short int)strlen(output);

	if		( IS_DIR(mode) && *nlink == 2)	strcpy(output, LN_COL_DIR_EMPTY);					// empty directory
	else if	( IS_DIR(mode) && *nlink >= 3)	strcpy(output, LN_COL_DIR);							// non-empty dir
	else if (!IS_DIR(mode) && *nlink == 1)	strcpy(output, LN_COL_REG_1);						// file w   1 link
	else if (!IS_DIR(mode) && *nlink >= 2){	strcpy(output, LN_COL_REG_MORE); *is_hln = true; }	// file w > 1 link
	else									strcpy(output, LN_COL_OTHER); // a dir w 1 link or dir/file w < 1 link

	printf("%*s" "%s%d" "%s",
		(int)field_lengths.nlink - link_len, "",
		output, *nlink,
		RESET FIELD_PAD
	);
}
