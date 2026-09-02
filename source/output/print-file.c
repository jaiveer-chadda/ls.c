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

void print_inum(const ino_t  inum) { printf(fields[FI_inum].fmt_p, getLen(FI_inum), inum, FIELD_PAD); }
void print_mode(const mode_t mode) { printf(fields[FI_mode].fmt_p, getLen(FI_mode), mode, FIELD_PAD); }

void print_usr_name(const char *const usr_name) {
	printf(fields[FI_usr_name].fmt_p, getLen(FI_usr_name), usr_name, FIELD_PAD);
}
void print_grp_name(const char *const grp_name) {
	printf(fields[FI_grp_name].fmt_p, getLen(FI_grp_name), grp_name, FIELD_PAD);
}
void print_flag_str(const char *const flag_str) {
	printf(fields[FI_flag_str].fmt_p, getLen(FI_flag_str), flag_str != NULL ? flag_str : "-", FIELD_PAD);
}

void print_mode_str(const modestr mode_str, const bool has_xat, const bool has_acl) {
	printf(fields[FI_mode_str].fmt_l, getLen(FI_mode_str), mode_str);

	putchar(has_xat ? XATTR_CHAR : ' ');
	putchar(has_acl ? ACL_CHAR	 : ' ');

	fputs(FIELD_PAD, stdout);
}

void print_size_str(const char *const size_str, const char size_unit) {
	printf("%*s%c%s",
		getLen(FI_size_str), size_str != NULL ? size_str : "-",
		size_unit ? size_unit : ' ',
		FIELD_PAD
	);
}

void print_time_str(TimeInfo *const times[4], const TimeType type) {
	printf(CSI_FG "%s" END "%*s" RESET "%s",
		time_colour_esc[times[type]->colour],
		getLen(timeFieldStr(type)), times[type]->str,
		FIELD_PAD
	);
}

void print_name(const char *const name, const icon_t icon, const FileColour colour) {
	printf("%s" "%s%s%s" "%lc %s" "%s",
		PRE_NAME_PAD,
		CSI, file_colour_esc[colour], END,
		icon, name,
		RESET
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines) {
	// if an file's FileStat pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	/* ———————————————————————————————————————————————— */

	print_inum(pFS->inum);
	print_mode(pFS->mode);
	print_mode_str(pFS->mode_str, pFS->has_xat, pFS->has_acl);
	print_size_str(pFS->f->size_str, pFS->f->size_unit);
	print_usr_name(pFS->f->usr_name);
	print_grp_name(pFS->f->grp_name);
	print_flag_str(pFS->f->flag_str);
	print_time_str(pFS->f->times, M_TIME);

	for (int i = 0; i < depth - 1; i++) printf("%*s%s", i ? 2 : 1 , "", lines[i] ? "│" : " ");

	lines_t new_lines;
	memcpy(new_lines, lines, sizeof(lines_t));

	if (depth != 0) {
		printf("%*s%s", depth != 1 ? 2 : 1, "", is_last ? "└─" : "├─");
		new_lines[depth - 1] = !is_last;
	}

	print_name(pFS->name, pFS->icon, pFS->f->file_col);

	putchar(pFS->suffix);
	putchar('\n');

	/* ———————————————————————————————————————————————— */

	if (!S_ISDIR(pFS->mode) || depth + 1 > MAX_DEPTH) return;

	// if (pFS->f == NULL || pFS->f->child_count == -1) { printf("\t%*s[[ error ]]\n", 92, ""); return; }
	// else if				 (pFS->f->child_count ==  0) { printf("\t%*s(  empty  )\n", 92, ""); return; }

	/* ———————————————————————————————————————————————— */

	for (int i = 0; i < pFS->f->child_count; i++) {
		printFile(&pFS->f->children[i], depth + 1, i == pFS->f->child_count - 1, new_lines);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
