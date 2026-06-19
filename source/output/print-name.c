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

void printName(const name_t name, const FileColour *colour, const bool *do_hln_hl, const flag_t *flags) {
	putchar(' '); // names have an extra space before them

	if (DO_COLOUR) {
		printf("%s%s" "%s%s" "%s",
			GET_HARDLN_UL(), GET_DIM_HL(),
			file_colour_esc[*colour], GET_NAME(name),
			RESET
		);

	} else {
		printf("%s", GET_NAME(name));
	}
}
