/// @file form/formatting.h

#ifndef FORMATTING_INITIALIASED
#define FORMATTING_INITIALIASED

#include "model/stat-model.h"

/* ——————————————————————————————————————————————————————— */

typedef struct {
	const char title[8];
	const char fmt_s[6];
	const char fmt_l[6];
	size_t len;
} field_t;

extern field_t fields[];

#define FIELDS_TABLE \
	/* field		  title		  fmt_s	  fmt_l	   */ \
	X(FI_name		, "Name"	, "%s"	, "%*s"		) \
	X(FI_nlink		, "Links"	, "%d"	, "%*d"		) \
	X(FI_dev_no		, "Dev No"	, "%d"	, "%*d"		) \
	X(FI_inode		, "Inode"	, "%llu", "%*llu"	) \
	X(FI_flags		, "Flags"	, "%x"	, "%*x"		) \
	X(FI_flag_str	, "Flags"	, "%s"	, "%-*s"	) \
	X(FI_mode		, "Mode"	, "%o"	, "%0*o"	) \
	X(FI_mode_str	, "Perms"	, "%s"	, "%-*s"	) \
	X(FI_size		, "Size"	, "%zd"	, "%*zd"	) \
	X(FI_size_str	, "Size"	, "%s"	, "%*s"		) \
	X(FI_uid		, "UID"		, "%d"	, "%*d"		) \
	X(FI_usr_name	, "User"	, "%s"	, "%-*s"	) \
	X(FI_gid		, "GID"		, "%d"	, "%*d"		) \
	X(FI_grp_name	, "Group"	, "%s"	, "%-*s"	) \
	X(FI_time		, "Time"	, "%ld"	, "%*ld"	) \
	X(FI_time_str	, "Time"	, "%s"	, "%*s"		) \
	X(FI_majmin		, "Size"	, "%#x"	, "%#*x"	) \

#define X(field, title, fmt_s, fmt_l) field,
typedef enum { FIELDS_TABLE FI_COUNT } FieldIdx;
#undef X

/* ——————————————————————————————————————————————————————— */

void initFormatting(void);
void setLen(const FieldIdx field, const size_t length);

/* ——————————————————————————————————————————————————————— */

#endif /* !FORMATTING_INITIALIASED */
