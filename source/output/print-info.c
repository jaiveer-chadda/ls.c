/// @file info/print-info.c

#include <stdio.h>
#include <string.h>

#include "../info/info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"
#include "../features/mode/mode.h"

#include "output.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SHOULD_ALIGN_RIGHT(field) \
	(strcmp(field##_TITLE, size_TITLE) == 0 || strcmp(field##_TITLE, time_str_TITLE) == 0)

#define PRINT_HEADER(field) \
	if (do_##field)	{ \
		printf( \
			SHOULD_ALIGN_RIGHT(field) ? "%*s%s" : "%-*s%s", \
			(int)field_lengths.field + GRAPHICS_LEN - (int)strlen(FIELD_PAD), \
			HEADER_HL field##_TITLE HEADER_HL_OFF, FIELD_PAD \
		); \
	}

inline void printHeader(void) {
	const int GRAPHICS_LEN = (int)strlen(HEADER_HL HEADER_HL_OFF FIELD_PAD);

	PRINT_HEADER(inode);	PRINT_HEADER(dev_no);
	PRINT_HEADER(mode);		PRINT_HEADER(mode_str);
	PRINT_HEADER(nlink);
	PRINT_HEADER(size);		PRINT_HEADER(size_str);
	PRINT_HEADER(uid);		PRINT_HEADER(usr_name);
	PRINT_HEADER(gid);		PRINT_HEADER(grp_name);
	PRINT_HEADER(flags);	PRINT_HEADER(flag_str);
	PRINT_HEADER(time);		PRINT_HEADER(time_str);

	puts(" " HEADER_HL name_TITLE HEADER_HL_OFF);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_DIM(name, flags)				\
	DO_DIM_HIDDEN && (					\
		(								\
			name[0] == '.'				\
			&& strcmp(name, ".") != 0	\
		)								\
		|| (flags & UF_HIDDEN)			\
	)

#define GET_NAME(name) \
	strcmp(name, ".") == 0 ? adjusted_path : name

/* ——————————————————————————————————————————————————————————————————————————— */

#define PRINT_FIELD(field) \
	if (do_##field) { \
		strcpy(fmt_str, fmt_strs_long.field); \
		strcat(fmt_str, FIELD_PAD); \
		printf(fmt_str, (int)field_lengths.field, file.field); \
	}

/* ——————————————————————————————————————————————————————————————————————————— */

#define PRINT_NAME(name, colour, do_hln_hl, flags)						\
	putchar(' '); /* names have an extra space before them */			\
	if (DO_COLOUR) {													\
		if (do_hln_hl) printf("%s", HARDLN_UNDERLINE);					\
		if (DO_DIM(name, flags)) printf("%s", DIM);						\
		printf("%s%s" RESET, file_colour_esc[colour], GET_NAME(name));	\
	} else printf("%s", name)

#define PRINT_TIME_STR() \
	if (DO_COLOUR) { \
		sprintf(fmt_str, "%%s%s" RESET FIELD_PAD, fmt_strs_long.time_str); \
		printf(fmt_str, time_colour_esc[file.time_col], (int)field_lengths.time_str, file.time_str); \
	} else PRINT_FIELD(time_str)

#define PRINT_MODE_STR() if (DO_COLOUR) printModeStr(file.mode_str)				; else PRINT_FIELD(mode_str)
#define PRINT_FLAG_STR() if (DO_COLOUR) printFlagStr(&(file.flags))				; else PRINT_FIELD(flag_str)
#define PRINT_USR_NAME() if (DO_COLOUR) printUsrName(&(file.uid), file.usr_name); else PRINT_FIELD(usr_name)
#define PRINT_GRP_NAME() if (DO_COLOUR) printGrpName(&(file.gid), file.grp_name); else PRINT_FIELD(grp_name)
#define PRINT_SIZE_STR()				printSize(file.size_str, file.size_unit)

#define PRINT_NLINK() \
	if (DO_COLOUR) printNLink(&(file.nlink), &(file.mode), &(file.do_hardlink_hl)); \
	else PRINT_FIELD(nlink)

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

		PRINT_NAME(file.name, file.file_col, file.do_hardlink_hl, file.flags);

		if (do_suffix && file.suffix != '\0') printf("%c", file.suffix);

		if (do_link_to)	{
			printf("%s", file.link_to);
			if (do_suffix && file.ln_suf != '\0') printf("%c", file.ln_suf);
		}

		printf("\n");
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
