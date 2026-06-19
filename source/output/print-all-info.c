/// @file output/print-all-info.c

#include <stdio.h>
#include <string.h>

#include "../options/options.h"
#include "../graphics/graphics.h"
#include "../features/mode/mode.h"

#include "output.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PRINT_FIELD(field)										\
	if (do_##field) {											\
		strcpy(fmt_str, fmt_strs_long.field);					\
		strcat(fmt_str, FIELD_PAD);								\
		printf(fmt_str, (int)field_lengths.field, file.field);	\
	}

/* ——————————————————————————————————————————————————————————————————————————— */

#define PRINT_TIME_STR()																				\
	if (DO_COLOUR) {																					\
		sprintf(fmt_str, "%%s%s" RESET FIELD_PAD, fmt_strs_long.time_str);								\
		printf(fmt_str, time_colour_esc[file.time_col], (int)field_lengths.time_str, file.time_str);	\
	} else PRINT_FIELD(time_str)

#define PRINT_MODE_STR() if (DO_COLOUR) printModeStr(file.mode_str)				; else PRINT_FIELD(mode_str)
#define PRINT_FLAG_STR() if (DO_COLOUR) printFlagStr(&(file.flags))				; else PRINT_FIELD(flag_str)
#define PRINT_USR_NAME() if (DO_COLOUR) printUsrName(&(file.uid), file.usr_name); else PRINT_FIELD(usr_name)
#define PRINT_GRP_NAME() if (DO_COLOUR) printGrpName(&(file.gid), file.grp_name); else PRINT_FIELD(grp_name)
#define PRINT_SIZE_STR()				printSizeStr(file.size_str, file.size_unit)

#define PRINT_NLINK()														\
	if (DO_COLOUR) {														\
		printNLink(&(file.nlink), &(file.mode), &(file.do_hardlink_hl));	\
	} else PRINT_FIELD(nlink)

/* ——————————————————————————————————————————————————————————————————————————— */

inline void printFields(const FileInfo *all_files, const int *count) {
	char fmt_str[16];

	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];

		PRINT_FIELD(inode);	PRINT_FIELD(dev_no);
		PRINT_FIELD(mode);	PRINT_MODE_STR();

		PRINT_NLINK();
		PRINT_FIELD(size);	PRINT_SIZE_STR();
		PRINT_FIELD(uid);	PRINT_USR_NAME();
		PRINT_FIELD(gid);	PRINT_GRP_NAME();
		PRINT_FIELD(flags);	PRINT_FLAG_STR();
		PRINT_FIELD(time);	PRINT_TIME_STR();

		printName(file.name, &(file.file_col), &(file.do_hardlink_hl), &(file.flags));

		if (do_suffix && file.suffix != '\0') printf("%c", file.suffix);

		printSymlink(file.link_to, file.ln_suf);
		printf("\n");
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
