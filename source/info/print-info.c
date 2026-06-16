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

static inline void printModeStr(const modestr str) {
	if (!do_mode_str) return;

	char output[128] = "";

	FileColour type = -1;

	switch (str[0]) {
		case '|': type = PIPE		; break;
		case 'c': type = CHR_DEV	; break;
		case 'd': type = DIRECT		; break;
		case 'b': type = BLK_DEV	; break;
		case '.': type = REGULAR	; break;
		case 'l': type = SYMLINK	; break;
		case '=': type = SOCKET		; break;
		case '%': type = WHITEOUT	; break;
	}

	strcat(output, file_colour_esc[type]);
	
	output[strlen(output)] = str[0];
	output[strlen(output) + 1] = '\0';

	PermColour esc = -1, last_esc;

	for (int i = 1; i < MAX_MODE_LEN - 1; i++) {
		last_esc = esc;

		switch (str[i]) {
			case '-': esc = NONE; break;
			case 'r': esc = READ; break;
			case 't': esc = STICKY_X; break;
			case 'T': esc = STICKY_N; break;
			case 's': esc = i == 3 ? SUID_X : SGID_X; break;
			case 'S': esc = i == 3 ? SUID_N : SGID_N; break;
			case 'w': esc = i == 8 ? W_OTHER : W_USRGRP; break;
			case 'x': esc = str[0] == '.' ? X_REG : X_NREG; break;
		}

		if (last_esc != esc) strcat(output, perm_colour_esc[esc]);

		output[strlen(output)] = str[i];
		output[strlen(output) + 1] = '\0';
	}

	printf("%s%s  ", output, RESET);
}


#define PRINT_FIELD(field) \
	if (do_##field) { \
		strcpy(fmt_str, fmt_strs_long.field); \
		strcat(fmt_str, INTERFIELD_PADDING); \
		printf(fmt_str, (int)field_lengths.field, file.field); \
	}

#define PRINT_NAME(name, colour) \
	if (DO_COLOUR && colour != REGULAR) { \
		printf("%s%s" RESET, file_colour_esc[colour], name); \
	} else printf("%s", name)

void printFields(const FileInfo *all_files, const int *count) {
	char fmt_str[8];

	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];

		PRINT_FIELD(inode);	PRINT_FIELD(dev_no);
		PRINT_FIELD(mode);

		if (DO_COLOUR) printModeStr(file.mode_str);
		else PRINT_FIELD(mode_str);

		PRINT_FIELD(nlink);
		PRINT_FIELD(size);	PRINT_FIELD(size_str);
		PRINT_FIELD(uid);	PRINT_FIELD(usr_name);
		PRINT_FIELD(gid);	PRINT_FIELD(grp_name);
		PRINT_FIELD(flags);	PRINT_FIELD(flag_str);
		PRINT_FIELD(time);	PRINT_FIELD(time_str);

		putchar(' ');
		PRINT_NAME(file.name, file.file_col);

		if (do_suffix)	printf("%c", file.suffix);

		if (do_link_to)	{
			printf("%s", file.link_to);
			if (do_suffix) printf("%c", file.ln_suf);
		}

		printf("\n");
	}
}
