/// @file output/print-nlink.c

#include <stdio.h>
#include <string.h>

#include "../form/formatting.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

void printNLink(const nlink_t *nlink, const mode_t *mode) {
	if (!do_nlink()) return;

	// using "nlink_str" to calculate the strlen of nlink
	char nlink_str[16], colour[16];

	sprintf(nlink_str, "%d", *nlink);
	const short int link_len = (short int)strlen(nlink_str);

	if		( S_ISDIR(*mode) && *nlink == 2) strcpy(colour, LN_COL_DIR_EMPTY);	// empty directory
	else if	( S_ISDIR(*mode) && *nlink >= 3) strcpy(colour, LN_COL_DIR);		// non-empty dir
	else if (!S_ISDIR(*mode) && *nlink == 1) strcpy(colour, LN_COL_REG_1);		// file w	1 link
	else if (!S_ISDIR(*mode) && *nlink >= 2) strcpy(colour, LN_COL_REG_MORE);	// file w >	1 link
	else									 strcpy(colour, LN_COL_OTHER);		// dir w 1 link or dir/file w 0 links

	const int spaces = (int)field_lengths.nlink - link_len;

	printf("%*s" "%s%s%s" "%s" "%s%s",
		spaces, "",
		CSI, colour, END,
		nlink_str,
		RESET, FIELD_PAD
	);
}
