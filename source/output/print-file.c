/// @file output/print-file.c

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "options/options.h"
#include "features/features.h"

static inline void printFields(const FileStat *const pFS);

/* —— printFile() —————————————————————————————————————————————————————————————————————————————————————————————————— */

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines) {
	// if an file's `FileStat` pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	lines_t new_lines = {0};

	/* —— print fields ———————————————————————————————————————————————————————————————————————————————— */

	// make sure we're not starting the line with any colour leaking
	colprint(RESET_ALL);

	// print all of the main feature fields
	printFields(pFS);

	// print the tree branches before the name
	print_tree(new_lines, lines, depth, is_last);
	// print the file's icon and name
	print_name(pFS);

	// finally, print the file's suffix and end the file's output by outputting a newline
	if (do_suffix() && pFS->suffix != '\0') putchar(pFS->suffix);
	putchar('\n');

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

	// if we made it through the checks, then iterate through this dir's children, and recursively print them
	for (int i = 0; i < pFS->f->child_count; i++) {
		printFile(&pFS->f->children[i], depth + 1, i == pFS->f->child_count - 1, new_lines);
	}
}

/* —— printFields() ———————————————————————————————————————————————————————————————————————————————————————————————— */

#define print_time_raw(p,t) /** @todo implement */;

// note: to use the `print_field` macro, a function must have the following signature:
//	`void print_[field_name](const FileStat *const pFS)`
#define print_field(field)  if (do_##field()) print_##field(pFS)
#define print_time(type) if (do_time_t(type)) { \
	if (do_time		()) print_time_raw(pFS, (type)); \
	if (do_time_str	()) print_time_str(pFS, (type)); \
}

/* ——————————————————————————————————————————————————— */

static inline void printFields(const FileStat *const pFS) {
	print_field(inum	);
	print_field(mode	);
	print_field(mode_str);
	print_field(size_str);
	print_field(usr_name);
	print_field(grp_name);
	print_field(flag_str);

	print_time(A_TIME);
	print_time(M_TIME);
	print_time(C_TIME);
	print_time(B_TIME);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
