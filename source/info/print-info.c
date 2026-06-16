/// @file info/print-info.c

#include <stdio.h>
#include <string.h>

#include "info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"
#include "../features/mode/mode.h"

#define HEADER_HL		UNDER	BOLD
#define HEADER_HL_OFF	NOUNDER	NOBOLD

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SHOULD_ALIGN_RIGHT(field) \
	(strcmp(field##_TITLE, "Size") == 0 || strcmp(field##_TITLE, time_str_TITLE) == 0)

#define PRINT_HEADER(field) \
	if (do_##field)	{ \
		printf( \
			SHOULD_ALIGN_RIGHT(field) ? "%*s" : "%-*s", \
			(int)field_lengths.field + GRAPHICS_LEN, \
			HEADER_HL field##_TITLE HEADER_HL_OFF INTERFIELD_PADDING \
		); \
	}

inline void printHeader(void) {
	const int GRAPHICS_LEN = (int)strlen(HEADER_HL HEADER_HL_OFF INTERFIELD_PADDING);

	PRINT_HEADER(inode);	PRINT_HEADER(dev_no);
	PRINT_HEADER(mode);		PRINT_HEADER(mode_str);
	PRINT_HEADER(nlink);
	PRINT_HEADER(size);		PRINT_HEADER(size_str);
	PRINT_HEADER(uid);		PRINT_HEADER(usr_name);
	PRINT_HEADER(gid);		PRINT_HEADER(grp_name);
	PRINT_HEADER(flags);	PRINT_HEADER(flag_str);
	PRINT_HEADER(time);		PRINT_HEADER(time_str);

	if (do_name) printf("%s", HEADER_HL name_TITLE HEADER_HL_OFF);
	printf("\n");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_DIM(name, flags) \
	(DO_DIM_HIDDEN && (name[0] == '.' || flags & UF_HIDDEN))

#define PRINT_FIELD(field) \
	if (do_##field) { \
		strcpy(fmt_str, fmt_strs_long.field); \
		strcat(fmt_str, INTERFIELD_PADDING); \
		printf(fmt_str, (int)field_lengths.field, file.field); \
	}

#define PRINT_NAME(name, colour, do_hln_hl, flags) \
	putchar(' '); \
	if (DO_COLOUR) { \
		if (do_hln_hl) printf("%s", HARDLN_UNDERLINE); \
		if (DO_DIM(name, flags)) printf("%s", DIM); \
		printf("%s%s" RESET, file_colour_esc[colour], name); \
	} else printf("%s", name)

#define PRINT_TIME_STR() \
	if (DO_COLOUR) { \
		sprintf(fmt_str, "%%s%s" RESET INTERFIELD_PADDING, fmt_strs_long.time_str); \
		printf(fmt_str, time_colour_esc[file.time_col], (int)field_lengths.time_str, file.time_str); \
	} else PRINT_FIELD(time_str)

#define PRINT_MODE_STR() \
	if (DO_COLOUR) printModeStr(file.mode_str); \
	else PRINT_FIELD(mode_str)

#define PRINT_NLINK() \
	if (DO_COLOUR) printNLink(&(file.nlink), &(file.mode), &(file.do_hardlink_hl)); \
	else PRINT_FIELD(nlink)

inline void printFields(const FileInfo *all_files, const int *count) {
	char fmt_str[16];

	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];

		PRINT_FIELD(inode);	PRINT_FIELD(dev_no);
		PRINT_FIELD(mode);	PRINT_MODE_STR();

		PRINT_NLINK();
		PRINT_FIELD(size);	PRINT_FIELD(size_str);
		PRINT_FIELD(uid);	PRINT_FIELD(usr_name);
		PRINT_FIELD(gid);	PRINT_FIELD(grp_name);
		PRINT_FIELD(flags);	PRINT_FIELD(flag_str);
		PRINT_FIELD(time);	PRINT_TIME_STR();

		PRINT_NAME(file.name, file.file_col, file.do_hardlink_hl, file.flags);

		if (do_suffix)	printf("%c", file.suffix);

		if (do_link_to)	{
			printf("%s", file.link_to);
			if (do_suffix) printf("%c", file.ln_suf);
		}

		printf("\n");
	}
}
