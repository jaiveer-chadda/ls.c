/// @file output/headers.c

#include <stdio.h>

#include "form/formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define HDR_FMT_RIGHT "%*s" "%s%s%s"		"%ls"
#define HDR_FMT_LEFT		"%s%s%s" "%*s"	"%ls"

// I really don't know how to simplify this without introducing some ridiculous ternary operators
#define print_header_base(condition, fi_field) do {					\
	if (condition) {												\
		if (fields[fi_field].is_right) {							\
			printf(HDR_FMT_RIGHT,									\
				getLen(fi_field) - fields[fi_field].title_len, "",	\
				HEADER_ANSI, fields[fi_field].title, RESET,			\
				FIELD_PAD											\
			);														\
		} else {													\
			printf(HDR_FMT_LEFT,									\
				HEADER_ANSI, fields[fi_field].title, RESET,			\
				getLen(fi_field) - fields[fi_field].title_len, "",	\
				FIELD_PAD											\
			);														\
		}															\
	} \
} while (0)

#define print_header(field) \
	print_header_base(do_##field(), FI_##field)

#define print_time_header(type)									\
	if (do_time_t(type)) {										\
		print_header_base(do_time(), timeField(type));			\
		print_header_base(do_time_str(), timeFieldStr(type));	\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printHeaders(void) {
	print_header(inum ); print_header(dev_no  );
	print_header(mode ); print_header(mode_str);
	printf("%*s", getLen(FI_xat_acl), "");

	print_header(nlink);
	print_header(size ); print_header(size_str);
	print_header(uid  ); print_header(usr_name);
	print_header(gid  ); print_header(grp_name);
	print_header(flags); print_header(flag_str);

	print_time_header(A_TIME);
	print_time_header(M_TIME);
	print_time_header(C_TIME);
	print_time_header(B_TIME);

	putchar('\n');
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
