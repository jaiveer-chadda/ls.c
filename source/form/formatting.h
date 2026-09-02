/// @file form/formatting.h

#ifndef FORMATTING_INITIALIASED
#define FORMATTING_INITIALIASED

#include "model/stat-model.h"

/* ——————————————————————————————————————————————————————— */

typedef struct {
	const char title[12];
	const char fmt_s[6];
	const char fmt_l[6];
	size_t len;
} field_t;

extern field_t fields[];

#define FIELDS_TABLE \
	/* field	 header		 fmt  L/R	*/\
	X(name		, "Name"	, s	, left	) \
	X(nlink		, "Links"	, d	, right	) \
	X(dev_no	, "Dev No"	, d	, right	) \
	X(inum		, "Inode No", llu,right	) \
	X(flags		, "Flags"	, x	, right	) \
	X(flag_str	, "Flags"	, s	, left	) \
	X(mode		, "Mode"	, o	, right	) \
	X(mode_str	, "Perms"	, s	, left	) \
	X(size		, "Size"	, zd, right	) \
	X(size_str	, "Size"	, s	, right	) \
	X(uid		, "UID"		, d	, right	) \
	X(usr_name	, "User"	, s	, left	) \
	X(gid		, "GID"		, d	, right	) \
	X(grp_name	, "Group"	, s	, left	) \
	\
	X(atime		, "ATime"	, ld, right	) \
	X(mtime		, "MTime"	, ld, right	) \
	X(ctime		, "CTime"	, ld, right	) \
	X(btime		, "BTime"	, ld, right	) \
	X(atime_str	, "Accessed", s	, right	) \
	X(mtime_str	, "Modified", s	, right	) \
	X(ctime_str	, "Changed"	, s	, right	) \
	X(btime_str	, "Birth"	, s	, right	) \
/**/

#define X(fld, hdr, fms, lor) FI_##fld,
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
void checkLengths(const FileStat *const pfile);
void setLen(const FieldIdx field, const size_t length);

/* ——————————————————————————————————————————————————————— */

#endif /* !FORMATTING_INITIALIASED */
