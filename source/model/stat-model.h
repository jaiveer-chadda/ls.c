/// @file model/stat-model.h

#ifndef STAT_MODEL_INITIALISED
#define STAT_MODEL_INITIALISED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>

/* ———————————————————————————————————————————————————————————————————————————————— */

#define FIELD_COUNT 17

#define OCT_MODE_LEN 6

/// The maximum length a filename can be on Darwin (MacOS/some BSD) machines.
#define MAX_NAME_LEN MAXNAMLEN

/// The maximum length a path can be on Darwin (MacOS/some BSD) machines.
#define MAX_PATH_LEN 255 // __DARWIN_MAXPATHLEN

/// The maximum number of possible user and super user flags on MacOS.
#define MAX_FLAG_NUM 14
/// The longest flag name on MacOS ("uimmutable") + 1.
#define MAX_FLAG_LEN 11

/// The length of the human-readable mode string +1 (e.g. `drwxr-xr-x`).
#define MAX_MODE_LEN 11

/// An arbitrary upper bound on how many file's we're going to accept.
#define MAX_FILES_IN_DIR 1 << 12

/**
 * Given that the maximum filesize on MacOS is `( 1 << ( ( 1 << 6 ) - 1 ) ) - 1` == `2^63 - 1`,
 *  the longest string would be "9,223,372,036,854,775,806 b" (27 chars) + 1.
 * I'm not going to keep it that long though, so 10 bytes should be plenty.
 */
#define MAX_SIZE_LEN 10

/**
 * This also doesn't hit the theoretical max (2^8), but nothing's ever gonna be that long,
 *  and MacOS' GUI only allows you to create usernames of length 2^5 anyways.
 */
#define MAX_UGID_LEN 1 << 5

/// The maximum size an evaluated time format string is allowed to be.
#define MAX_TIME_LEN 1 << 5

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef char type_t;
typedef char name_t[MAX_NAME_LEN];
typedef char path_t[MAX_PATH_LEN];
typedef unsigned int flag_t;

typedef char modestr[MAX_MODE_LEN];
typedef char timestr[MAX_TIME_LEN];
typedef char ugidstr[MAX_UGID_LEN];
typedef char sizestr[MAX_SIZE_LEN];
typedef char flagstr[MAX_FLAG_LEN * MAX_FLAG_NUM];

/* ———————————————————————————————————————————————————————————————————————————————— */

// use the macro `X`, on the expectation that it'll be defined later
#define FILE_COLOUR_TABLE \
	X(REGULAR,	""				) /* \e[37m */ \
	X(DIRECT,	"\33[1;36m"		) /* \e[36m */ \
	X(SYMLINK,	"\33[35m"		) /* \e[35m */ \
	X(EXEC,		"\33[31m"		) /* \e[31m */ \
	X(PIPE,		"\33[33m"		) /* \e[33m */ \
	X(SOCKET,	"\33[32m"		) /* \e[32m */ \
	X(MOUNT,	"\33[34m"		) /* \e[34m */ \
	X(CHR_DEV,	"\33[1;30;43m"	) /* \e[43m */ \
	X(BLK_DEV,	"\33[1;30;46m"	) /* \e[46m */ \
	X(OW_DIR,	"\33[1;30;42m"	) /* \e[42m */ \
	X(SUID,		"\33[1;30;41m"	) /* \e[41m */ \
	X(SGID,		"\33[1;30;45m"	) /* \e[45m */ \
	X(STICKY,	"\33[1;30;44m"	) /* \e[44m */ \
	X(DATALESS,	"\33[1;30;47m"	) /* \e[47m */ \
	X(WHITEOUT, "\33[1;30;107m"	) /*\e[107m */

typedef enum {
	#define X(name, esc) name,	// only unpack the names
	FILE_COLOUR_TABLE
	#undef X
	FILE_COLOUR_COUNT	// a final element so we can figure out how many enum entires there were
} FileColour;

extern const char *const file_colour_esc[FILE_COLOUR_COUNT];

/* ———————————————————————————————————————————————————————————————————————————————— */

#define PERM_COLOUR_TABLE \
	X(NONE		, "\33[;90m"		) \
	X(READ		, "\33[;92m"		) \
	X(W_USRGRP	, "\33[;93m"		) \
	X(W_OTHER	, "\33[;1;30;42m"	) \
	X(X_REG		, "\33[;1;31m"		) \
	X(X_NREG	, "\33[;91m"		) \
	X(SUID_X	, "\33[;1;30;41m"	) \
	X(SUID_N	, "\33[;1;30;101m"	) \
	X(SGID_X	, "\33[;1;30;45m"	) \
	X(SGID_N	, "\33[;1;30;105m"	) \
	X(STICKY_X	, "\33[;1;30;44m"	) \
	X(STICKY_N	, "\33[;1;30;104m"	)

typedef enum {
	#define X(name, esc) name,
	PERM_COLOUR_TABLE
	#undef X
	PERM_COLOUR_COUNT
} PermColour;

extern const char *const perm_colour_esc[PERM_COLOUR_COUNT];

/* ———————————————————————————————————————————————————————————————————————————————— */

#define NLINK_COL_DIR		"\33[96m"
#define NLINK_COL_REG_1		"\33[36m"
#define NLINK_COL_REG_MORE	"\33[1;30;105m"

/* ———————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	name_t	name	;
	type_t	suffix	;

	path_t	link_to ;
	type_t	ln_suf	;

	nlink_t	nlink	;
	dev_t	dev_no	;	ino_t	inode	;

	flag_t	flags	;	flagstr flag_str;
	mode_t	mode	;	modestr mode_str;
	off_t	size	;	sizestr size_str;

	uid_t	uid		;	ugidstr usr_name;
	gid_t	gid		;	ugidstr grp_name;

	time_t	time	;	timestr time_str;

	FileColour file_col;
	bool do_hardlink_hl;
} FileInfo;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STAT_MODEL_INITIALISED */
