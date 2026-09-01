/// @file model/consts.h

#ifndef CONSTS_H
#define CONSTS_H

// Includes all the `MAX...LEN` constants, but also the `DIR` struct
#include <dirent.h>
#include <limits.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PROGRAM_NAME "lk"
#define DOTDIR "."
#define BASE_10 10

/* —————————————————————————————————————————————————————— */

/// @brief The maximum number of levels the program is allowed to recuse.
#define RECURSION_LIMIT 16

/// @brief How many children of a directory to allocate memory for, before we know the final child count.
#define INIT_CHILD_COUNT 2

/**
 * @brief The maximum number of files that APFS will allow in a single folder.
 *
 * `MAX_CHILD_COUNT` = `INT32_MAX` = `(1 << ((1 << 5) - 1)) - 1` = `2,147,483,647 files` ≈ `2.1 G`
 */
#define MAX_CHILD_COUNT ((signed int)((1l << ((1l << 5) - 1)) - 2))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// @brief The maximum length a filename can be on Darwin (macOS/some BSD) machines (255 b).
#define MAX_NAME_LEN MAXNAMLEN

/// @brief The maximum length a path can be on Darwin (macOS/some BSD) machines (1024 b).
#define MAX_PATH_LEN __DARWIN_MAXPATHLEN

/// @brief The maximum number of possible user and superuser flags on macOS.
#define MAX_FLAG_NUM 14

/// @brief The longest flag name on macOS ("uimmutable") + 1.
#define MAX_FLAG_LEN 11

/* —————————————————————————————————————————————————————— */

/// @brief The length of the mode (including type) when written in octal (e.g. `040755`).
#define OCT_MODE_LEN 6

/// @brief The length of the human-readable mode string +1 (e.g. `drwxr-xr-x`).
#define MODE_STR_LEN 11

/**
 * @brief The length of the string displaying a file's size.
 *
 * The longest size string possible (not including the unit) is `999.9` (5 + 1 = 6 bytes).
 */
#define MAX_SIZE_LEN 16

/**
 * @brief The maximum length of a user or group name.
 *
 * This also doesn't hit the theoretical max (2^8), but nothing's ever gonna be that long,
 *  and macOS' GUI only allows you to create usernames of length 2^5 (32) anyways.
 */
#define MAX_UGID_LEN (1 << 5)

/**
 * @brief The maximum size an evaluated time string is allowed to be.
 *
 * Set to an arbitrary length of `2^5` = `32`.
 *
 * @todo You could theoretically go over with a string like `Wednesday 19 September 26  02:41 pm` (35 + 1 = 36),
 *		but I'll handle that when I implement custom time format strings.
 */
#define MAX_TIME_LEN (1 << 5)

/* ———————————————————————————————————————————————————————————————————————————————— */

#endif /* !CONSTS_H */
