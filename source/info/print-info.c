/// @file info/print-info.c

#include <stdio.h>
#include <string.h>

#include "info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

#define INTERFIELD_PADDING " "

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

void printHeader(void) {
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

#define PRINT_FIELD(field) \
	if (do_##field) { \
		strcpy(fmt_str, fmt_strs_long.field); \
		strcat(fmt_str, INTERFIELD_PADDING); \
		printf(fmt_str, (int)field_lengths.field, file.field); \
	}

#define COLOUR_NAME(output, name, colour) \
	if (DO_COLOUR && colour != NORMAL) { \
		sprintf(output, "\33[%sm%s" RESET, file_colour_esc[colour], name); \
	} else strcpy(coloured_name, name)

void printFields(const FileInfo *all_files, const int *count) {
	char fmt_str[8];
	name_t coloured_name;

	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];

		PRINT_FIELD(inode);	PRINT_FIELD(dev_no);
		PRINT_FIELD(mode);	PRINT_FIELD(mode_str);
		PRINT_FIELD(nlink);
		PRINT_FIELD(size);	PRINT_FIELD(size_str);
		PRINT_FIELD(uid);	PRINT_FIELD(usr_name);
		PRINT_FIELD(gid);	PRINT_FIELD(grp_name);
		PRINT_FIELD(flags);	PRINT_FIELD(flag_str);
		PRINT_FIELD(time);	PRINT_FIELD(time_str);

		COLOUR_NAME(coloured_name, file.name, file.file_col);

		printf(" %s", coloured_name);
		if (do_suffix)	printf("%c", file.suffix);

		if (do_link_to)	{
			printf("%s", file.link_to);
			if (do_suffix) printf("%c", file.ln_suf);
		}

		printf("\n");
	}
}
