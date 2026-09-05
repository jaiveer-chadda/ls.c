/// @file output/print-file.c

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "form/formatting.h"
#include "options/options.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines) {
	// if an file's FileStat pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	/* ———————————————————————————————————————————————— */

	colprint(RESET_ALL);

	if (do_inum		()) print_inum	  (pFS);
	if (do_mode		()) print_mode	  (pFS);
	if (do_mode_str	()) print_mode_str(pFS);
	if (do_size_str	()) print_size_str(pFS);
	if (do_usr_name	()) print_usr_name(pFS);
	if (do_grp_name	()) print_grp_name(pFS);
	if (do_flag_str	()) print_flag_str(pFS);
	if (do_time_str ()) {
		if (do_time_t(A_TIME)) print_time_str(pFS, A_TIME);
		if (do_time_t(M_TIME)) print_time_str(pFS, M_TIME);
		if (do_time_t(C_TIME)) print_time_str(pFS, C_TIME);
		if (do_time_t(B_TIME)) print_time_str(pFS, B_TIME);
	}

	/* ———————————————————————————————————————————————— */

	lines_t new_lines = {0};
	print_tree(new_lines, lines, depth, is_last);

	/* ———————————————————————————————————————————————— */

	print_name(pFS);
	if (do_suffix() && pFS->suffix != '\0') putchar(pFS->suffix);

	/* ———————————————————————————————————————————————— */
 
	putchar('\n'); // end the entry printing, and output a newline

	/* ———————————————————————————————————————————————————————————————————————————————————————————————— */

	// assert that if `pFS->f` is NULL, errno will be set
	assert(pFS->f == NULL ? pFS->err_no != 0 : true);

	// trying to print a file that raised an error while parsing/processing it
	if (pFS->err_no != 0) {
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

		return;
	}

	/* ———————————————————————————————————————————————— */

	// there shouldn't be a way to go over the recursion limit
	assert(depth + 1 < RECURSION_LIMIT);
	// if this isn't a directory (or we're not treating it as one), or we've reached the recursion limit, then return
	if (!S_ISDIR(pFS->mode) || DIRS_AS_FILES() || depth + 1 > MAX_DEPTH) return;

	/* ———————————————————————————————————————————————— */

	// trying to recurse into an empty directory
	if (pFS->f->child_count == 0) {
		print_empty_tree();

		printf(/**/"%s%s( "/**/"%s%s "/**/"%s)\n"/**/,
			PRE_NAME_PAD, (EMPTY_DIR_BR_ANSI),	// "%s%s( "	--> " \e[37;2m(␣"
			(EMPTY_DIR_ANSI), EMPTY_DIR_MSG,	// "%s%s "	--> "\e[22mempty␣"
			(EMPTY_DIR_NB_ANSI)					// "%s)\n"	--> "\e[2m)\n"
		);

		// tell the colour object that the currently active colour is `\e[2;37m`
		setActive(EMPTY_DIR_BR_COL);

		return;
	}

	/* ———————————————————————————————————————————————— */

	for (int i = 0; i < pFS->f->child_count; i++) {
		printFile(&pFS->f->children[i], depth + 1, i == pFS->f->child_count - 1, new_lines);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
