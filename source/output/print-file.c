/// @file output/print-file.c

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "icons/icons.h"
#include "options/options.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void print_suff(const FileStat *const pFS);
static inline void printFields(const FileStat *const pFS);
static inline bool stopRecursing(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines);

/* —— printFile() —————————————————————————————————————————————————————————————————————————————————————————————————— */

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines) {
	// if we weren't able to `stat` the file in the first place, then there'll be nothing to print
	if (!isValidFS(pFS)) return;
	// set up the array that'll be used to track which tree branches need to be printed
	lines_t new_lines = {0};

	/* —— print fields ———————————————————————————————————————————————————————————————————————————————— */

	printFields(pFS); // print all "feature" fields (i.e. fields which are defined in `features.h`)

	// after the fields, print the tree stucture
	print_tree(new_lines, lines, depth, is_last);
	// then print the file's icon, name, and suffix
	print_icon(pFS); print_name(pFS); print_suff(pFS);

	/// @todo print targets of links
	/// @todo print info about mount devices

	putchar('\n'); // finally, end this entry's output by printing a newline

	/* —— recurse ————————————————————————————————————————————————————————————————————————————————————— */

	// if there's no reason we shouldn't recurse
	if (!stopRecursing(pFS, depth, new_lines)) {
		// then iterate through this directory's children, and recursively print them
		for (int i = 0; i < pFS->f->child_count; i++) {
			const bool is_last_child = (i == pFS->f->child_count - 1);
			printFile(&pFS->f->children[i], depth + 1, is_last_child, new_lines);
		}
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— print_suff() ————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void print_suff(const FileStat *const pFS) {
	if (!do_suffix() || pFS->suffix == '\0') return;
	printf("%s%c", getcol(RESET_ALL), pFS->suffix);
}

/* —— printFields() ———————————————————————————————————————————————————————————————————————————————————————————————— */

// #define print_field(field)  if (do_##field()) print_##field(pFS)
#define print_field(field) do { if (do_##field()) print_##field(pFS); colprint(RESET_ALL); } while (0)

#define print_time(type) if (do_time_t(type)) { \
	if (do_time	   ()) print_time_raw(pFS, (type)); \
	if (do_time_str()) print_time_str(pFS, (type)); \
}

/* ——————————————————————————————————————————————————— */

static inline void printFields(const FileStat *const pFS) {
	print_field(inum ); print_field(dev_no	);
	print_field(mode ); print_field(mode_str);
	print_field(nlink);
	print_field(size ); print_field(size_str);
	print_field(uid	 ); print_field(usr_name);
	print_field(gid	 ); print_field(grp_name);
	print_field(flags); print_field(flag_str);

	print_time(A_TIME); print_time(M_TIME);
	print_time(C_TIME); print_time(B_TIME);
}

/* —— stopRecursing() ————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool stopRecursing(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines) {
	assert(pFS->f == NULL ? pFS->err_no != 0 : true);  // if `pFS->f` is NULL, errno should always be set
	assert(depth + 1 < RECURSION_LIMIT);  // there shouldn't be a way to ever go over the maximum recursion limit

	return ( // stop recursing if ...
		fileError(pFS, depth, new_lines)	// the file raised an error while parsing/processing,
		|| !S_ISDIR(pFS->mode)				// the file isn't a directory,
		|| DIRS_AS_FILES()					//	(or it is a directory, but we're not treating it as one)
		|| (depth) + 1 > MAX_DEPTH			// we've reached the user's chosen recursion level,
		|| dirEmpty(pFS, depth, new_lines)	// we're trying to recurse into an empty directory
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
