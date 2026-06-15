/// @file options/options.h

void initLengths(void);

#ifndef FLAGS_INITIALIASED
#define FLAGS_INITIALIASED

#include <stdbool.h>
#include "../model/stat-model.h"

extern const bool DO_SHORT_FLAGS;
extern const bool DO_HEADER;

/* ——————————————————————————————————————————————————————— */

typedef struct {
	size_t	name	;
	size_t	suffix	;
	size_t	link_to	;

	size_t	nlink	;
	size_t	dev_no	;	size_t	inode	;

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
	fmt_spec name	;
	fmt_spec suffix	;
	fmt_spec link_to;

	fmt_spec nlink	;
	fmt_spec dev_no	;	fmt_spec inode	;

	fmt_spec flags	;	fmt_spec flag_str;
	fmt_spec mode	;	fmt_spec mode_str;
	fmt_spec size	;	fmt_spec size_str;
	fmt_spec uid	;	fmt_spec usr_name;
	fmt_spec gid	;	fmt_spec grp_name;
	fmt_spec time	;	fmt_spec time_str;
} FmtStrs;

extern FmtStrs fmt_strs_short, fmt_strs_long;

/* ——————————————————————————————————————————————————————— */

extern const bool
	do_name,
	do_suffix,
	do_link_to,

	do_nlink,
	do_dev_no,
	do_inode,

	do_flags,	do_flag_str,
	do_mode,	do_mode_str,
	do_size,	do_size_str,
	do_uid,		do_usr_name,
	do_gid,		do_grp_name,
	do_time,	do_time_str;

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
#define suffix_TITLE	""
#define link_to_TITLE	""

#define nlink_TITLE		"Links"
#define dev_no_TITLE	"Device No."
#define inode_TITLE		"Inode"

#define flags_TITLE		"Flags"
#define flag_str_TITLE	"Flags"

#define mode_TITLE		"Mode"
#define mode_str_TITLE	"Permissions"

#define size_TITLE		"Size"
#define size_str_TITLE	"Size"

#define uid_TITLE		"UID"
#define usr_name_TITLE	"User"

#define gid_TITLE		"GID"
#define grp_name_TITLE	"Group"

#define time_TITLE		"MTime"
#define time_str_TITLE	"Modified"

#endif
