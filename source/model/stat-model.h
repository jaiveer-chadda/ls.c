/// @file model/stat-model.h

#ifndef STAT_MODEL_INITIALISED
#define STAT_MODEL_INITIALISED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <dirent.h>
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

} FileInfo;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STAT_MODEL_INITIALISED */
