/// @file info/parse-info.c

#include <stdio.h>
#include <string.h>

#include "info.h"
#include "../options/options.h"

#define INTERFIELD_PADDING " "

#define PRINT_HEADER(field) \
	if (do_##field)	{ \
		if (strcmp(field##_TITLE, "Size") == 0 || strcmp(field##_TITLE, time_str_TITLE) == 0) \
			printf("%*s"  INTERFIELD_PADDING, (int)field_lengths.field, field##_TITLE); \
		else \
			printf("%-*s" INTERFIELD_PADDING, (int)field_lengths.field, field##_TITLE); \
	}

void printHeader(void) {
	PRINT_HEADER(inode);	PRINT_HEADER(dev_no);
	PRINT_HEADER(mode);		PRINT_HEADER(mode_str);
	PRINT_HEADER(nlink);
	PRINT_HEADER(size);		PRINT_HEADER(size_str);
	PRINT_HEADER(uid);		PRINT_HEADER(usr_name);
	PRINT_HEADER(gid);		PRINT_HEADER(grp_name);
	PRINT_HEADER(flags);	PRINT_HEADER(flag_str);
	PRINT_HEADER(time);		PRINT_HEADER(time_str);

	if (do_name) printf("%s", name_TITLE);
	printf("\n");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PRINT_FIELD(field) \
	if (do_##field) { \
		strcpy(fmt_str, fmt_strs_long.field); \
		strcat(fmt_str, INTERFIELD_PADDING); \
		printf(fmt_str, (int)field_lengths.field, file.field); \
	}

void printFields(const FileInfo *all_files, const int *count) {
	char fmt_str[8];

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

		if (do_name)	printf(" %s", file.name);
		if (do_suffix)	printf("%c", file.suffix);

		if (do_link_to)	{
			printf("%s", file.link_to);
			if (do_suffix) printf("%c", file.ln_suf);
		}

		printf("\n");
	}

}
