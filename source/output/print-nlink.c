/// @file output/print-nlink.c

#include <stdio.h>
#include <string.h>

#include "../options/options.h"
#include "../model/stat-model.h"
#include "../graphics/graphics.h"

#define IS_DIR(pMode) ((*pMode & S_IFMT) == S_IFDIR)

void printNLink(const nlink_t *nlink, const mode_t *mode, bool *is_hln) {
	if (!do_nlink) return;

	// using "nlink_str" to calculate the strlen of nlink
	char nlink_str[16], colour[16];

	sprintf(nlink_str, "%d", *nlink);
	const short int link_len = (short int)strlen(nlink_str);

	if		( IS_DIR(mode) && *nlink == 2)	strcpy(colour, LN_COL_DIR_EMPTY);					// empty directory
	else if	( IS_DIR(mode) && *nlink >= 3)	strcpy(colour, LN_COL_DIR);							// non-empty dir
	else if (!IS_DIR(mode) && *nlink == 1)	strcpy(colour, LN_COL_REG_1);						// file w   1 link
	else if (!IS_DIR(mode) && *nlink >= 2){	strcpy(colour, LN_COL_REG_MORE); *is_hln = true; }	// file w > 1 link
	else									strcpy(colour, LN_COL_OTHER); // a dir w 1 link or dir/file w < 1 link

	printf("%*s" "%s%s" "%s",
		(int)field_lengths.nlink - link_len, "",
		colour, nlink_str,
		RESET FIELD_PAD
	);
}
