/// @file output/print-file.c

#include <stdio.h>
#include <string.h>

#include "output.h"
#include "form/formatting.h"
#include "options/options.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define modext(field, istru) (pFS->has_##field	?  (istru) : ' ')
#define ch_ful(field, nfull) (pFS->f != NULL	?  (pFS->f->field) : nfull)
#define ch_NUL(field, isnul) (pFS->f != NULL	? ((pFS->f->field) != NULL ? (pFS->f->field) : isnul) : "?")

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
	printf(fields[FI_mode_str].fmt_l, getLen(FI_mode_str), pFS->mode_str);

	putchar(pFS->has_xat ? XATTR_CHAR : ' ');
	putchar(pFS->has_acl ? ACL_CHAR	  : ' ');

	fputs(FIELD_PAD, stdout);
}

static inline void print_size_str(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->size_str != NULL;

	printf("%*s%c%s",
		getLen(FI_size_str), valid ? pFS->f->size_str : NO_SIZE_STR,
		/// @todo handle `size_unit` printing
		valid ? (pFS->f->size_unit ? pFS->f->size_unit : ' ') : ' ',
		FIELD_PAD
	);
}

static inline void print_time_str(const FileStat *const pFS, const TimeType type) {
	if (pFS->f != NULL && pFS->f->times[type] != NULL) {
		printf(CSI_FG "%s" END "%*s" RESET "%s",
			time_colour_esc[pFS->f->times[type]->colour],
			getLen(timeFieldStr(type)), pFS->f->times[type]->str,
			FIELD_PAD
		);
		return;
	}

	printf("%*s" RESET "%s", getLen(timeFieldStr(type)), TIME_ERR_STR, FIELD_PAD);
}

static inline void print_name(const FileStat *const pFS) {
	const char *const to_print = (DO_PATH() && pFS->path != NULL) ? pFS->path : pFS->name;
	printf("%s" "%s%s%s" "%lc %s" "%s",
		PRE_NAME_PAD,
		CSI, file_colour_esc[pFS->file_col], END,
		pFS->icon, to_print,
		RESET
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines) {
	// if an file's FileStat pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	/* ———————————————————————————————————————————————— */

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

	for (int i = 0; i < depth - 1; i++) printf("%*s%s", i ? 2 : 1 , "", lines[i] ? "│" : " ");

	lines_t new_lines;
	memcpy(new_lines, lines, sizeof(lines_t));

	if (depth != 0) {
		printf("%*s%s", depth != 1 ? 2 : 1, "", is_last ? "└─" : "├─");
		new_lines[depth - 1] = !is_last;
	}

	/* ———————————————————————————————————————————————— */

	print_name(pFS);

	putchar(pFS->suffix);
	putchar('\n');

	/* ———————————————————————————————————————————————— */

	if (!S_ISDIR(pFS->mode) || depth + 1 > MAX_DEPTH) return;

	// if (pFS->f == NULL || pFS->f->child_count == -1) { printf("\t%*s[[ error ]]\n", 92, ""); return; }
	// else if				 (pFS->f->child_count ==  0) { printf("\t%*s(  empty  )\n", 92, ""); return; }
	if (pFS->f == NULL || pFS->f->child_count == -1) return;
	else if				 (pFS->f->child_count ==  0) return;

	/* ———————————————————————————————————————————————— */

	for (int i = 0; i < pFS->f->child_count; i++) {
		printFile(&pFS->f->children[i], depth + 1, i == pFS->f->child_count - 1, new_lines);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
