/// @file info/parse-info.c

#include <stdio.h>
#include <string.h>

#include "info.h"
#include "../options/options.h"

#define PARSE_LEN(field) \
	if (do_##field) { \
		sprintf(elem_as_str, fmt_strs_short.field, file.field);\
		len = strlen(elem_as_str); \
		if (len > field_lengths.field) field_lengths.field = len; \
	}

void getFieldLengths(const FileInfo *all_files, const int *count) {
	size_t len;
	char elem_as_str[64];

	// run through all the files' fields and calculate their maximum lengths
	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];
		PARSE_LEN(nlink);
		PARSE_LEN(inode);	PARSE_LEN(dev_no);
		PARSE_LEN(flags);	PARSE_LEN(flag_str);
		// mode & mode string have constant lengths
		field_lengths.mode = OCT_MODE_LEN; field_lengths.mode_str = MAX_MODE_LEN;
		PARSE_LEN(size);	PARSE_LEN(size_str);
		PARSE_LEN(uid);		PARSE_LEN(usr_name);
		PARSE_LEN(gid);		PARSE_LEN(grp_name);
		PARSE_LEN(time);	PARSE_LEN(time_str);
	}
}
