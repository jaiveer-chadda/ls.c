/// @file model/consts.h

#ifndef CONSTS_INITIALIASED
#define CONSTS_INITIALIASED

#include <dirent.h>

/* ———————————————————————————————————————————————————————————————————————————————— */

#define PROGRAM_NAME "lk"
#define ERROR		 PROGRAM_NAME ": "

/* ———————————————————————————————————————————————————————————————————————————————— */

/// The maximum length a filename can be on Darwin (macOS/some BSD) machines.
#define MAX_NAME_LEN MAXNAMLEN

/// The maximum length a path can be on Darwin (macOS/some BSD) machines.
#define MAX_PATH_LEN __DARWIN_MAXPATHLEN

/// The maximum number of possible user and superuser flags on macOS.
#define MAX_FLAG_NUM 14
/// The longest flag name on macOS ("uimmutable") + 1.
#define MAX_FLAG_LEN 11

/**
 * An arbitrary upper bound on how many files we're going to accept.
 * The actual maximum number of files is `1 << 31`, which is ~ 2.1 billion.
 */
#define MAX_FILES_IN_DIR (1 << 12)

/// The length of the mode when written in octal.
#define OCT_MODE_LEN 6

/// The length of the human-readable mode string +1 (e.g. `drwxr-xr-x`).
#define MODE_STR_LEN 11

/**
 * Given that the maximum filesize on macOS is `( 1 << ( ( 1 << 6 ) - 1 ) ) - 1` == `2^63 - 1`,
 *  the longest string would be "9,223,372,036,854,775,806 b" (27 chars) + 1.
 * I'm not going to keep it that long though, so 10 bytes should be plenty.
 */
#define MAX_SIZE_LEN 10

/**
 * This also doesn't hit the theoretical max (2^8), but nothing's ever gonna be that long,
 *  and macOS' GUI only allows you to create usernames of length 2^5 anyways.
 */
#define MAX_UGID_LEN (1 << 5)

/// The maximum size an evaluated time format string is allowed to be.
#define MAX_TIME_LEN (1 << 5)

/* ———————————————————————————————————————————————————————————————————————————————— */
#endif /* !CONSTS_INITIALIASED */
