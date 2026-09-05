/// @file output/print-file.c

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "output.h"
#include "debugging.h"
#include "icons/icons.h"
#include "form/formatting.h"
#include "options/options.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_NOTHING 0

#define print_empty_tree() do {						\
	printf("%*s", getTotalLen(), "");				\
	print_tree(NULL, new_lines, depth + 1, true);	\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void print_inum(const FileStat *const pFS) {
	printf(fields[FI_inum].fmt_p, getLen(FI_inum), pFS->inum, FIELD_PAD);
}

static inline void print_mode(const FileStat *const pFS) {
	printf(fields[FI_mode].fmt_p, getLen(FI_mode), pFS->mode, FIELD_PAD);
}

static inline void print_usr_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->usr_name != NULL;
	printf(fields[FI_usr_name].fmt_p, getLen(FI_usr_name), valid ? pFS->f->usr_name : INV_FILE_USRNAME, FIELD_PAD);
}

static inline void print_grp_name(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->grp_name != NULL;
	printf(fields[FI_grp_name].fmt_p, getLen(FI_grp_name), valid ? pFS->f->grp_name : INV_FILE_GRPNAME, FIELD_PAD);
}

static inline void print_flag_str(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->flag_str != NULL;
	printf(fields[FI_flag_str].fmt_p, getLen(FI_flag_str), valid ? pFS->f->flag_str : NO_FLAG_STR, FIELD_PAD);
}

static inline void print_mode_str(const FileStat *const pFS) {
	printf(fields[FI_mode_str].fmt_s, pFS->mode_str);

	pFS->has_xat ? putchar(XATTR_CHAR) : (getLen(FI_xat) ? putchar(' ') : DO_NOTHING);
	pFS->has_acl ? putchar(ACL_CHAR	 ) : (getLen(FI_acl) ? putchar(' ') : DO_NOTHING);

	fputs(FIELD_PAD, stdout);
}

static inline void print_size_str(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->size_str != NULL;
	const bool do_unit = valid && DO_PRINT_SIZE_UNIT(pFS->f->size_unit);

	if (do_unit) {
		printf("%*s%c",
			getLen(FI_size_str) - 1, pFS->f->size_str,
			pFS->f->size_unit
		);

	} else {
		printf("%*s",
			getLen(FI_size_str), valid ? pFS->f->size_str : NO_SIZE_STR
		);
	}

	fputs(FIELD_PAD, stdout);
}

static inline void print_time_str(const FileStat *const pFS, const TimeType type) {
	if (pFS->f				!= NULL &&
		pFS->f->times[type] != NULL
	) {
		printf("%s" "%*s" "%s",
			getcol(time_colour_esc[pFS->f->times[type]->colour]),
			getLen(timeFieldStr(type)), pFS->f->times[type]->str,
			FIELD_PAD
		);

		return;
	}

	printf("%*s" "%s", getLen(timeFieldStr(type)), TIME_ERR_STR, FIELD_PAD);
}

static inline void print_name(const FileStat *const pFS) {
	const char *const name_or_path = (DO_PATH() && pFS->path != NULL) ? pFS->path : pFS->name;

	fputs(PRE_ICON_PAD, stdout);
	printIcon(pFS->icon, pFS->file_col);

	printf("%s" "%s" "%s" "%s",
		PRE_NAME_PAD,
		getcol(file_colour_esc[pFS->file_col]),
		name_or_path,
		getcol(RESET_ALL)
	);
}

void print_tree(lines_t new_lines, const lines_t lines, const uint8_t depth, const bool is_last) {
	// for depth 0 (the original inputs), there aren't any tree levels to print
	if (depth == 0) return;

	colprint(PUNCT);

	for (int level = 0; level < depth - 1; level++) {
		printf("%*s" "%s",
			level == 0 ? TREE_LV1_PAD : TREE_PAD, "", // add 2 spaces of padding on every level except the 1ˢᵗ one
			lines[level] ? TREE_VERT : " " // only if this level needs a line should you print one
		);
	}

	printf("%*s" "%s%s",
		// add 2 spaces of padding on every level except the 1ˢᵗ one
		depth == 1 ? TREE_LV1_PAD : TREE_PAD, "",
		// print `├` before every file except the last one, where we print `└`
		is_last ? TREE_CORNER : TREE_BRANCH,
		TREE_HORI
	);

	if (new_lines == NULL) return;

	// populate the new line array with the contents of the old one
	memcpy(new_lines, lines, sizeof(lines_t));
	// then set the most recent line to `true` _iff_ there are more files to print on this level
	new_lines[depth - 1] = !is_last;
}

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
	assert(pFS->f == NULL ? pFS->err_no > 0 : true);

	if (pFS->err_no != 0) {
		print_empty_tree();
		printf("%s[[ error: %s ]]\n", PRE_NAME_PAD, strerror(pFS->err_no));
		return;
	}

	if (!S_ISDIR(pFS->mode) || depth + 1 > MAX_DEPTH) return;

	if (pFS->f->child_count == 0) {
		print_empty_tree();

		colprint(EMPTY_DIR_BR_COL);
		printf("%s" "(%s %s", PRE_NAME_PAD, getcol(EMPTY_DIR_COL), EMPTY_DIR_MSG);
		printf(" %s)\n", getcol(EMPTY_DIR_BR_COL));
	}

	/* ———————————————————————————————————————————————— */

	for (int i = 0; i < pFS->f->child_count; i++) {
		printFile(&pFS->f->children[i], depth + 1, i == pFS->f->child_count - 1, new_lines);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
