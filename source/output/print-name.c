/// @file output/print-name.c

#include <stdio.h>
#include <string.h>

#include "../info/info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

#include "output.h"

#define DO_DIM(name, flags)						\
	DO_DIM_HIDDEN && (							\
		(										\
			name[0] == '.'						\
			&& strcmp(name, CURRENT_DIR) != 0	\
		)										\
		|| (flags & UF_HIDDEN)					\
	)

#define GET_NAME(name)	(strcmp(name, CURRENT_DIR) == 0 ? adjusted_path : name)
#define GET_DIM_HL()	(DO_DIM(name, *flags) ? DIM : "")
#define GET_HARDLN_UL()	(*do_hln_hl ? HARDLN_UNDERLINE : "")

typedef unsigned char u_char;
typedef unsigned int  u_int;

bool getEscSequence(char *esc_seq, const char orig_char) {
	u_char chr = (u_char)orig_char;
	switch (chr) {
		case '\\'	: strcpy(esc_seq, "\\\\");	return true;
		case '\a'	: strcpy(esc_seq, "\\a");	return true;
		case '\b'	: strcpy(esc_seq, "\\b");	return true;
		case '\t'	: strcpy(esc_seq, "\\t");	return true;
		case '\n'	: strcpy(esc_seq, "\\n");	return true;
		case '\v'	: strcpy(esc_seq, "\\v");	return true;
		case '\f'	: strcpy(esc_seq, "\\f");	return true;
		case '\r'	: strcpy(esc_seq, "\\r");	return true;
		case '\x1b'	: strcpy(esc_seq, "\\e");	return true;
	}

	if (0 <= chr && chr <= 7)					{ sprintf(esc_seq, "\\%u", (u_int)chr); return true; }
	if ((7 < chr && chr <= 31) || chr == 127)	{ sprintf(esc_seq, "\\x%02x",	  chr); return true; }

	return false;
}

void printName(const name_t name, const FileColour *colour, const bool *do_hln_hl, const flag_t *flags) {
	putchar(' '); // names have an extra space before them

	name_t escaped_name;
	const char *raw_name = GET_NAME(name);
	int read_idx = 0, write_idx = 0;

	while (raw_name[read_idx] != '\0') {
		const char chr = raw_name[read_idx++];
		char esc_seq[6]; // big enough for \xNN + null byte

		if (getEscSequence(esc_seq, chr)) {
			const int esc_len = strlen(esc_seq);
			strcpy(escaped_name + write_idx, esc_seq);
			write_idx += esc_len;

		} else {
			escaped_name[write_idx++] = chr;
		}
	}

	escaped_name[write_idx] = '\0';

	if (DO_COLOUR) {
		printf("%s%s" "%s%s" "%s",
			GET_HARDLN_UL(), GET_DIM_HL(),
			file_colour_esc[*colour], escaped_name,
			RESET
		);

	} else {
		printf("%s", escaped_name);
	}
}
