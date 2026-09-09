/// @file features/nlink.c

#include <stdio.h>
#include "form/formatting.h"

static inline Colour getLinkColour(const nlink_t nlink, const bool is_dir) {
	if (is_dir) {
		if (nlink == 2) return LN_COL_DIR_EMPTY;
		if (nlink >= 3) return LN_COL_DIR;

	} else {
		if (nlink == 1) return LN_COL_REG_1;
		if (nlink >= 2) return LN_COL_REG_MORE;
	}
	return LN_COL_OTHER;
}

void print_nlink(const FileStat *const pFS) {
	if (pFS->s == NULL) {
		printf("%s" "%*c" "%ls", getcol(PUNCT), getLen(FI_nlink), '-', FIELD_PAD);
		return;
	}

	const nlink_t nlink = pFS->s->st_nlink;
	const int nlink_len = snprintf(NULL, 0, "%hu", nlink);

	const Colour col = getLinkColour(nlink, S_ISDIR(pFS->mode));
	const char *const ansi_col = getcol(col);

	printf("%*s" "%s%hu" "%s" "%ls",
		getLen(FI_nlink) - nlink_len, "",
		ansi_col, nlink,
		col.has_bg() ? getcol(RESET_ALL) : "",
		FIELD_PAD
	);
}
