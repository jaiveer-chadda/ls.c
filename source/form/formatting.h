/// @file form/formatting.h

#ifndef FORMATTING_INITIALIASED
#define FORMATTING_INITIALIASED

#include "model/stat-model.h"

/* ——————————————————————————————————————————————————————— */

typedef struct {
	const char title[10];
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
	X(FI_majmin		, "Size"	, "%#x"	, "%#*x"	) \
	\
	X(FI_atime		, "ATime"	, "%ld"	, "%*ld"	) \
	X(FI_mtime		, "MTime"	, "%ld"	, "%*ld"	) \
	X(FI_ctime		, "CTime"	, "%ld"	, "%*ld"	) \
	X(FI_btime		, "BTime"	, "%ld"	, "%*ld"	) \
	X(FI_atime_str	, "Accessed", "%s"	, "%*s"		) \
	X(FI_mtime_str	, "Modified", "%s"	, "%*s"		) \
	X(FI_ctime_str	, "Changed"	, "%s"	, "%*s"		) \
	X(FI_btime_str	, "Birth"	, "%s"	, "%*s"		) \

#define X(field, title, fmt_s, fmt_l) field,
typedef enum { FIELDS_TABLE FI_COUNT } FieldIdx;
#undef X

#define FIRST_TIME_FIELD	FI_atime
#define FIRST_TIMESTR_FIELD FI_atime_str

#define timeFieldStr(type)	(FIRST_TIMESTR_FIELD + (type))
#define timeField(type)		(FIRST_TIME_FIELD	 + (type))

/// Get the calculated maximum length of the inputted field (`type`).
#define getLen(type) ((int)(fields[(FI_##type)].len))

/* ——————————————————————————————————————————————————————— */

void initFormatting(void);
void setLen(const FieldIdx field, const size_t length);

/* ——————————————————————————————————————————————————————— */

#endif /* !FORMATTING_INITIALIASED */
