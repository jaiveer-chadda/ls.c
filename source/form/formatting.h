/// @file form/formatting.h

void initFormatting(void);

#ifndef FORMATTING_INITIALIASED
#define FORMATTING_INITIALIASED

#include "../model/stat-model.h"

/* ——————————————————————————————————————————————————————— */

typedef struct {
	size_t	nlink	;
	size_t	dev_no	;	size_t	inode  ;

	size_t	flags	;	size_t flag_str;
	size_t	mode	;	size_t mode_str;
	size_t	size	;	size_t size_str;
	size_t	uid		;	size_t usr_name;
	size_t	gid		;	size_t grp_name;
	size_t	time	;	size_t time_str;
} Lengths;

extern Lengths field_lengths;

/* ——————————————————————————————————————————————————————— */

typedef char fmt_spec[6];

typedef struct {
	fmt_spec nlink	;
	fmt_spec dev_no	;	fmt_spec inode	;

	fmt_spec flags	;	fmt_spec flag_str;
	fmt_spec mode	;	fmt_spec mode_str;
	fmt_spec size	;	fmt_spec size_str;
	fmt_spec majmin	;
	fmt_spec uid	;	fmt_spec usr_name;
	fmt_spec gid	;	fmt_spec grp_name;
	fmt_spec time	;	fmt_spec time_str;
} FmtStrs;

extern FmtStrs fmt_strs_short, fmt_strs_long;

/* ——————————————————————————————————————————————————————— */

extern const bool
	NAME_MIN_LEN,
	SUFFIX_MIN_LEN,
	LINK_TO_MIN_LEN,

	NLINK_MIN_LEN,
	DEV_NO_MIN_LEN,
	INODE_MIN_LEN,

	FLAGS_MIN_LEN,	FLAG_STR_MIN_LEN,
	MODE_MIN_LEN,	MODE_STR_MIN_LEN,
	SIZE_MIN_LEN,	SIZE_STR_MIN_LEN,
	UID_MIN_LEN,	USR_NAME_MIN_LEN,
	GID_MIN_LEN,	GRP_NAME_MIN_LEN,
	TIME_MIN_LEN,	TIME_STR_MIN_LEN;

/* ——————————————————————————————————————————————————————— */

#define name_TITLE		"Name"

#define nlink_TITLE		"Links"
#define dev_no_TITLE	"Dev No"
#define inode_TITLE		"Inode"

#define flags_TITLE		"Flags"
#define flag_str_TITLE	"Flags"

#define mode_TITLE		"Mode"
#define mode_str_TITLE	"Perms"

#define size_TITLE		"Size"
#define size_str_TITLE	"Size"

#define uid_TITLE		"UID"
#define usr_name_TITLE	"User"

#define gid_TITLE		"GID"
#define grp_name_TITLE	"Group"

#define time_TITLE		"MTime"
#define time_str_TITLE	"Modified"

/* ——————————————————————————————————————————————————————— */

#endif /* !FORMATTING_INITIALIASED */
