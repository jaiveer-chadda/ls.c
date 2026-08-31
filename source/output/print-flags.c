/// @file output/print-flags.c

#include <stdio.h>
#include <string.h>

#include "model/stat-model.h"
#include "form/formatting.h"
#include "options/options.h"

#include "features/flags/flags.h"

void printFlagStr(const flag_t *flags) {
	if (!do_flag_str()) return;

	if (*flags == 0) {
		const int spaces = (int)(field_lengths.flag_str - strlen(NO_FLAG_STR));
		printf("%s%s%s" "%*s" "%s",
			ANSI(PUNCT), NO_FLAG_STR, RESET,
			spaces, "",
			FIELD_PAD
		);
		return;
	}

	flagstr flag_name;
	int chars_printed = 0;
	bool is_first_flag = true;

	for (int i = 0; i < MAX_FLAG_NUM; i++) {
		if (*flags & ALL_FLAGS[i].mask) {
			strcpy(flag_name, GET_FLAG_NAME(ALL_FLAGS[i]));

			if (!is_first_flag) {
				printf("%s%s%s", ANSI(PUNCT), "," /* FLAG_SEP_STR */, RESET);
				chars_printed++;
			}
			is_first_flag = false;

			printf("%s%s%s" "%s%s",
				CSI, ALL_FLAGS[i].colour, END,
				flag_name, RESET
			);
			chars_printed += (int)strlen(flag_name);
		}
	}

	const int spaces = (int)field_lengths.flag_str - chars_printed;
	printf("%*s" "%s", spaces, "", FIELD_PAD);
}
