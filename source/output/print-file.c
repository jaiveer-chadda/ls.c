/// @file output/print-file.c

#include <stdio.h>

#include "output.h"
#include "form/formatting.h"
#include "options/options.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define modext(field, istru) (pFS->has_##field	?  (istru) : ' ')
#define ch_ful(field, nfull) (pFS->f != NULL	?  (pFS->f->field) : nfull)
#define ch_NUL(field, isnul) (pFS->f != NULL	? ((pFS->f->field) != NULL ? (pFS->f->field) : isnul) : "?")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printFile(FileStat *pFS, const uint8_t depth) {
	// if an file's FileStat pointer points to `NULL`, we weren't able to be `stat` it in the first place
	if (pFS == NULL) return;

	/* ———————————————————————————————————————————————— */

	printf("%8x "		, (unsigned)pFS->inum);
	printf("%06o "		, pFS->mode);
	printf("%10s%c%c"	, pFS->mode_str, modext(xat, '@'), modext(acl, '+'));

	printf("%*s %c "	, getLen(size_str), ch_NUL(size_str, "-"), ch_ful(size_unit, ' '));
	printf("%-*s %-*s "	, getLen(usr_name), ch_ful(usr_name, "?"), getLen(grp_name), ch_ful(grp_name, "?"));

	printf("%-*s "		, getLen(flag_str), ch_NUL(flag_str, "-"));
	printf("%*s"		, getLen(mtime_str), ch_ful(times[M_TIME]->str, "-"));

	printf("%*s"		, (depth * 4) + 1, "");
	printf("%s%s%s"		, CSI, file_colour_esc[pFS->f->file_col], END);
	printf("%lc %s"		, pFS->icon, pFS->name);
	printf("%s%c%s"		, "\33[34m", pFS->suffix, RESET);

	putchar('\n');

	/* ———————————————————————————————————————————————— */

	if (!S_ISDIR(pFS->mode) || depth + 1 > MAX_DEPTH) return;

	if (pFS->f == NULL || pFS->f->child_count == -1) { printf("\t%*s[[ error ]]\n", 92, ""); return; }
	else if 			 (pFS->f->child_count ==  0) { printf("\t%*s(  empty  )\n", 92, ""); return; }

	/* ———————————————————————————————————————————————— */

	for (int i = 0; i < pFS->f->child_count; i++) printFile(&pFS->f->children[i], depth + 1);
}
