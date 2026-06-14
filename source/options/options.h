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

	size_t	nlink	;
	size_t	dev_no	;	size_t	inode	;

	size_t	flags	;	size_t flag_str;
	size_t	mode	;	size_t mode_str;
	size_t	size	;	size_t size_str;
	size_t	uid		;	size_t usr_name;
	size_t	gid		;	size_t grp_name;
	size_t	time	;	size_t time_str;
} Lengths;

/* ——————————————————————————————————————————————————————— */

extern Lengths field_lengths;

extern const bool
	do_name,
	do_suffix,

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

#define NAME_TITLE		"Name"
#define SUFFIX_TITLE	""

#define NLINK_TITLE		"Links"
#define DEV_NO_TITLE	"Device No."
#define INODE_TITLE		"Inode"

#define FLAGS_TITLE		"Flags"
#define FLAG_STR_TITLE	"Flags"

#define MODE_TITLE		"Mode"
#define MODE_STR_TITLE	"Permissions"

#define SIZE_TITLE		"Size"
#define SIZE_STR_TITLE	"Size"

#define UID_TITLE		"UID"
#define USR_NAME_TITLE	"User"

#define GID_TITLE		"GID"
#define GRP_NAME_TITLE	"Group"

#define TIME_TITLE		"MTime"
#define TIME_STR_TITLE	"Modified"

#endif
