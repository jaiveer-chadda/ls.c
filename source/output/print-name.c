/// @file output/print-name.c

#include <stdio.h>
#include <string.h>

#include "../info/info.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

#include "output.h"

typedef unsigned char u_char;

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

#define DELETE 0x7F
#define IS_UNPRINTABLE(chr) ((0x0 <= (u_char)chr && (u_char)chr <= 0x1F) || chr == DELETE)

void printName(const name_t name, const FileColour *colour, const bool *do_hln_hl, const flag_t *flags) {
	putchar(' '); // names have an extra space before them

	const char *raw_name = GET_NAME(name);
	name_t escaped_name;

	int read_idx = 0, write_idx = 0;

	// iterate until we hit the null terminator of the original string
	while (raw_name[read_idx] != '\0') {
		const char chr = raw_name[read_idx];

		if (IS_UNPRINTABLE(chr)) {
			// `sprintf` returns the number of characters written
			write_idx += sprintf(escaped_name + write_idx, "\\x%02x", (u_char)chr);
		} else {
			escaped_name[write_idx++] = chr;
		}
		read_idx++;
	}

	// Properly null-terminate at the *new* total length
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
