/// @file output/print-header.c

#include <stdio.h>
#include <string.h>

#include "form/formatting.h"
#include "options/options.h"
#include "graphics/graphics.h"

#include "output.h"

#define IF_COLOUR(yes, no) DO_COLOUR() ? (yes) : (no)

#define SHOULD_ALIGN_RIGHT(field)		 \
	(  strcmp((#field), "flags"	  ) == 0 \
	|| strcmp((#field), "inode"	  ) == 0 \
	|| strcmp((#field), "dev_no"  ) == 0 \
	|| strcmp((#field), "size"	  ) == 0 \
	|| strcmp((#field), "size_str") == 0 \
	|| strcmp((#field), "time_str") == 0 )

#define PRINT_HEADER(field)													\
	if ((do_ ## field()))	{												\
		printf(SHOULD_ALIGN_RIGHT(field) ? "%*s%s" : "%-*s%s",				\
			(int)((field_lengths.field) + hl_len),							\
			IF_COLOUR(ANSI(HEADER_HL) field##_TITLE RESET, field##_TITLE),	\
			FIELD_PAD														\
		);																	\
	}

inline void printHeader(void) {
	const size_t hl_len = IF_COLOUR(strlen(ANSI(HEADER_HL) RESET), 0);

	PRINT_HEADER(inode)	;	PRINT_HEADER(dev_no)  ;
	PRINT_HEADER(mode)	;	PRINT_HEADER(mode_str);
	PRINT_HEADER(nlink)	;
	PRINT_HEADER(size)	;	PRINT_HEADER(size_str);
	PRINT_HEADER(uid)	;	PRINT_HEADER(usr_name);
	PRINT_HEADER(gid)	;	PRINT_HEADER(grp_name);
	PRINT_HEADER(flags)	;	PRINT_HEADER(flag_str);
	PRINT_HEADER(time)	;	PRINT_HEADER(time_str);

	printf("%s%s" "%s" "%s\n",
		PRE_NAME_PAD, IF_COLOUR(ANSI(HEADER_HL), NO_COLOUR),
		name_TITLE,
		IF_COLOUR(RESET, NO_COLOUR)
	);
}
