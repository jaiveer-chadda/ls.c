/// @file output/print-flags.c

#include <stdio.h>
#include <string.h>

#include "../model/stat-model.h"
#include "../options/options.h"

#include "../features/flags/flags.h"

void printFlagStr(const flag_t *flags) {
	if (!do_flag_str) return;

	if (*flags == 0) {
		printf("%s%*s",
			PUNCT NO_FLAG_STR RESET FIELD_PAD,
			(int)(field_lengths.flag_str - strlen(NO_FLAG_STR)), ""
		);
		return;
	}

	char flag_name[MAX_FLAG_LEN];
	int chars_printed = 0;
	bool is_first_flag = true;

	for (int i = 0; i < MAX_FLAG_NUM; i++) {
		if (*flags & ALL_FLAGS[i].mask) {
			strcpy(flag_name, GET_FLAG_NAME(ALL_FLAGS[i]));

			if (!is_first_flag) {
				printf("%s", PUNCT "," RESET);
				chars_printed++;
			}

			printf("%s%s" RESET, ALL_FLAGS[i].colour, flag_name);

			chars_printed += (int)strlen(flag_name);
			is_first_flag = false;
		}
	}

	const int max_len = (int)field_lengths.flag_str;
	const int padding = max_len - chars_printed;

	printf("%*s" FIELD_PAD, padding, "");
}
