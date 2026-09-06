/// @file output/headers.c

#include <stdio.h>

#include "form/formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define print_header_base(cond, fi_field)						\
	if (cond) {													\
		printf(fields[fi_field].is_right ? "%*s%ls" : "%-*s%ls",\
			getLen(fi_field), fields[fi_field].title,			\
			FIELD_PAD											\
		);														\
	}

#define print_header(field) print_header_base(do_##field(), FI_##field)

#define print_time_header(type)									\
	if (do_time_t(type)) {										\
		print_header_base(do_time(), timeField(type))			\
		print_header_base(do_time_str(), timeFieldStr(type))	\
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
