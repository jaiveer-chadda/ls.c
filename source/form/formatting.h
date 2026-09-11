/// @file form/formatting.h

#ifndef FORMATTING_INITIALIASED
#define FORMATTING_INITIALIASED

#include "model/stat-model.h"

/* ——————————————————————————————————————————————————————— */

typedef struct {
	const char title[12];
	const char fmt_p[12];
	const char fmt_s[8];
	size_t len;
	uint8_t title_len;
	bool is_right;
} field_t;

extern field_t fields[];

/// @brief n/a
#define NA ""

/* note: left is `%-*x`, right is `%*x` */
#define FIELDS_TABLE \
	/* field	  header	  fmt	 fmt+  L/R  */ \
	X(name		, "Name"	, "s"	, NA , left	 ) \
	X(nlink		, "Links"	, "d"	, "'", right ) \
	X(dev_no	, "Dev No"	, "d"	, NA , right ) \
	X(inum		, "Inode No", "llu"	, NA , right ) \
	X(flags		, "Flags"	, "x"	, NA , right ) \
	X(flag_str	, "Flags"	, "s"	, NA , left	 ) \
	X(mode		, "Mode"	, "o"	, "0", right ) \
	X(mode_str	, "Perms"	, "s"	, NA , left	 ) \
	X(size		, "Size"	, "zd"	, "'", right ) \
	X(size_str	, "Size"	, "s"	, NA , right ) \
	X(uid		, "UID"		, "d"	, NA , right ) \
	X(usr_name	, "User"	, "s"	, NA , left	 ) \
	X(gid		, "GID"		, "d"	, NA , right ) \
	X(grp_name	, "Group"	, "s"	, NA , left	 ) \
	\
	X(atime		, "ATime"	, "ld"	, NA , right ) \
	X(mtime		, "MTime"	, "ld"	, NA , right ) \
	X(ctime		, "CTime"	, "ld"	, NA , right ) \
	X(btime		, "BTime"	, "ld"	, NA , right ) \
	X(atime_str	, "Accessed", "s"	, NA , right ) \
	X(mtime_str	, "Modified", "s"	, NA , right ) \
	X(ctime_str	, "Changed"	, "s"	, NA , right ) \
	X(btime_str	, "Birth"	, "s"	, NA , right ) \
	\
	X(xat_acl	, NA		, NA	, NA , left	 ) \
/**/

#define X(fld, hdr, fms, ext, lor) FI_##fld,
typedef enum { FIELDS_TABLE FI_COUNT } FieldIdx;
#undef X

#define FIRST_TIME_FIELD	FI_atime
#define FIRST_TIMESTR_FIELD FI_atime_str

#define timeFieldStr(type)	(FIRST_TIMESTR_FIELD + (type))
#define timeField(type)		(FIRST_TIME_FIELD	 + (type))

/* ——————————————————————————————————————————————————————— */

/// Get the calculated maximum length of the inputted field (`type`).
#define getLen(type) ((int)(fields[(type)].len))

void initFormatting(void);
void checkLengths(const FileStat *const pfile, const bool do_basic);
void setLen(const FieldIdx field, const size_t length);

int getTotalLen(void);

/* ——————————————————————————————————————————————————————— */

#endif /* !FORMATTING_INITIALIASED */
