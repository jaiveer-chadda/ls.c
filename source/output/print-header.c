/// @file output/print-header.c

#include <stdio.h>
#include <string.h>

#include "../form/formatting.h"
#include "../options/options.h"
#include "../graphics/graphics.h"

#include "output.h"

#define SHOULD_ALIGN_RIGHT(field) \
	(  strcmp(field##_TITLE, size_TITLE		) == 0 \
	|| strcmp(field##_TITLE, time_str_TITLE	) == 0 )

#define PRINT_HEADER(field)														\
	if (do_##field())	{														\
		const int header_len = (int)strlen(HEADER_HL HEADER_HL_OFF FIELD_PAD);	\
		printf(SHOULD_ALIGN_RIGHT(field) ? "%*s%s" : "%-*s%s",					\
			(int)((field_lengths.field + header_len) - strlen(FIELD_PAD)),		\
			HEADER_HL field##_TITLE HEADER_HL_OFF, FIELD_PAD					\
		);																		\
	}

inline void printHeader(void) {
	PRINT_HEADER(inode)	;	PRINT_HEADER(dev_no)  ;
	PRINT_HEADER(mode)	;	PRINT_HEADER(mode_str);
	PRINT_HEADER(nlink)	;
	PRINT_HEADER(size)	;	PRINT_HEADER(size_str);
	PRINT_HEADER(uid)	;	PRINT_HEADER(usr_name);
	PRINT_HEADER(gid)	;	PRINT_HEADER(grp_name);
	PRINT_HEADER(flags)	;	PRINT_HEADER(flag_str);
	PRINT_HEADER(time)	;	PRINT_HEADER(time_str);

	puts(" " HEADER_HL name_TITLE HEADER_HL_OFF);
}
