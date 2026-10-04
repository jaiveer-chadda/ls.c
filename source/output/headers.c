/// @file output/headers.c

#include <stdio.h>

#include "form/formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define HEADER_FMT_RIGHT "%*s"	"%s%s%s"		"%ls"
#define HEADER_FMT_LEFT			"%s%s%s" "%*s"	"%ls"

// I really don't know how to simplify this without introducing some ridiculous ternary operators
#define PRINT_HEADER_BASE(condition, fi_field) do {					\
	if (condition) {												\
		if (fields[fi_field].is_right) {							\
			printf(HEADER_FMT_RIGHT,								\
				getLen(fi_field) - fields[fi_field].title_len, "",	\
				HEADER_ANSI, fields[fi_field].title, RESET,			\
				FIELD_PAD											\
			);														\
		} else {													\
			printf(HEADER_FMT_LEFT,									\
				HEADER_ANSI, fields[fi_field].title, RESET,			\
				getLen(fi_field) - fields[fi_field].title_len, "",	\
				FIELD_PAD											\
			);														\
		}															\
	} \
} while (0)

#define PRINT_HEADER(field) \
	PRINT_HEADER_BASE(do_##field(), FI_##field)

#define PRINT_TIME_HEADER(type)									\
	if (do_time_t(type)) {										\
		PRINT_HEADER_BASE(do_time(), timeField(type));			\
		PRINT_HEADER_BASE(do_time_str(), timeFieldStr(type));	\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printHeaders(void) {
	PRINT_HEADER(inum ); PRINT_HEADER(dev_no  );
	PRINT_HEADER(mode ); PRINT_HEADER(mode_str);
	printf("%*s", getLen(FI_xat_acl), "");

	PRINT_HEADER(nlink);
	PRINT_HEADER(size ); PRINT_HEADER(size_str);
	PRINT_HEADER(uid  ); PRINT_HEADER(usr_name);
	PRINT_HEADER(gid  ); PRINT_HEADER(grp_name);
	PRINT_HEADER(flags); PRINT_HEADER(flag_str);

	PRINT_TIME_HEADER(A_TIME);
	PRINT_TIME_HEADER(M_TIME);
	PRINT_TIME_HEADER(C_TIME);
	PRINT_TIME_HEADER(B_TIME);

	putchar('\n');
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
