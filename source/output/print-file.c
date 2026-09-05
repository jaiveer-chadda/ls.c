/// @file output/print-file.c

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "options/options.h"
#include "features/features.h"

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines) {
	// if an file's `FileStat` pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	/* —— print main fields ——————————————————————————————————————————————————————————————————————————— */

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

	/* —— print name & extras ————————————————————————————————————————————————————————————————————————— */

	lines_t new_lines = {0};

	print_tree(new_lines, lines, depth, is_last);
	print_name(pFS);

	if (do_suffix() && pFS->suffix != '\0') putchar(pFS->suffix);
	putchar('\n');  // end the entry printing, by outputting a newline

	/* —— error checking —————————————————————————————————————————————————————————————————————————————— */

	assert(pFS->f == NULL ? pFS->err_no != 0 : true);  // if `pFS->f` is NULL, errno should always be set
	assert(depth + 1 < RECURSION_LIMIT);  // there shouldn't be a way to go over the recursion limit

	// catch trying to print a file which raised an error while parsing/processing it
	if (fileError(pFS, depth, new_lines)) return;

	// if this isn't a directory (or we're not treating it as one), or we've reached the recursion limit, then return
	if (!S_ISDIR(pFS->mode) || DIRS_AS_FILES() || depth + 1 > MAX_DEPTH) return;

	// catch trying to recurse into an empty directory
	if (dirEmpty(pFS, depth, new_lines)) return;

	/* —— recurse ————————————————————————————————————————————————————————————————————————————————————— */

	for (int i = 0; i < pFS->f->child_count; i++) {
		printFile(&pFS->f->children[i], depth + 1, i == pFS->f->child_count - 1, new_lines);
	}
}
