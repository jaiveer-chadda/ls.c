/// @file output/errors.c

#include <stdio.h>
#include <string.h>

#include "output.h"
#include "options/options.h"
#include "form/formatting.h"
#include "model/stat-model.h"

/* —— print_empty_tree() ——————————————————————————————————————————————————————————————————————————————————————————— */

#define print_empty_tree() do {						\
	printf("%*s", getTotalLen(), "");				\
	print_tree(NULL, new_lines, depth + 1, true);	\
} while (0)

/* —— fileError() —————————————————————————————————————————————————————————————————————————————————————————————————— */

bool fileError(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines) {
	if (pFS->err_no == 0) return false;

	print_empty_tree();

	printf(/**/"%s%s[ "/**/"%s%s "/**/"%hu%s: "/**/"%s%s "/**/"%s]\n"/**/,
		// make the opening bracket red and dim
		PRE_NAME_PAD, (ERR_FILE_BR_ANSI),						// "%s%s[ "	--> " \e[31;2m[␣"
		// remove the dimming, leaving the "error" string just red
		(ERR_FILE_ANSI), ERR_FILE_MSG,							// "%s%s "	--> "\e[22m␣error␣"
		// re-dim the text for the colon
		pFS->err_no, (ERR_FILE_NB_ANSI),						// "%hu%s: "--> "12\e[2m:␣"
		// un-dim the text, and print strerror in red
		(ERR_FILE_ANSI), strerror(pFS->err_no),					// "%s%s "	--> "\e[22mCannot allocate memory␣"
		// finally, re-dim the text for the final bracket
		(ERR_FILE_NB_ANSI)										// "%s]\n"	--> "\e[2m]\n"
	);

	// the colour that's left is a dimmed, red style (equivalent to `\e[2;31m`)
	//	tell the 'colour object' that `\e[2;31m` is currently active
	setActive(ERR_FILE_BR_COL);

	return true;
}

/* —— dirEmpty() ——————————————————————————————————————————————————————————————————————————————————————————————————— */

bool dirEmpty(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines) {
	if (pFS->f->child_count != 0) return false;

	print_empty_tree();

	printf(/**/"%s%s( "/**/"%s%s "/**/"%s)\n"/**/,
		PRE_NAME_PAD, (EMPTY_DIR_BR_ANSI),	// "%s%s( "	--> " \e[37;2m(␣"
		(EMPTY_DIR_ANSI), EMPTY_DIR_MSG,	// "%s%s "	--> "\e[22mempty␣"
		(EMPTY_DIR_NB_ANSI)					// "%s)\n"	--> "\e[2m)\n"
	);

	// tell the colour object that the currently active colour is `\e[2;37m`
	setActive(EMPTY_DIR_BR_COL);

	return true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
