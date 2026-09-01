/// @file model/types.h

#ifndef TYPES_H
#define TYPES_H

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <stddef.h>
#include <inttypes.h>
#include <sys/stat.h>

#include "consts.h"

#ifndef bool
#	define bool	_Bool
#	define true	1
#	define false 0
#endif

/* ——————————————————————————————————————————————————— */

/**
 * @enum TimeType
 * @brief A lookup table to determine which time type is being referenced.
 *
 * Contains 4 types and a count:
 * - `A_TIME`(0): Access		time: The time the file's contents were last accessed.
 * - `M_TIME`(1): Modification	time: The time the file's contents were last modified.
 * - `C_TIME`(2): Change		time: The time the file's inode information was last changed.
 * - `B_TIME`(3): Birth			time: The time the file was originally created.
 * - `TIME_COUNT`(4): The number of types in the enum.
 */
typedef enum { A_TIME, M_TIME, C_TIME, B_TIME, TT_COUNT } TimeType;

/* ——————————————————————————————————————————————————— */

/**
 * @struct TimeInfo
 * @brief Information about a file's time.
 *
 * Contains the string that should be used to display the time, as well as the colour that that string should be
 * printed in.
 */
typedef struct TimeInfo			TimeInfo;
/**
 * @struct FileStat
 * @brief The primary information about a file.
 *
 * Contains the most essential information about a file, all of which is taken from the file's `dirent` struct.
 *
 * Also contains pointers to two other structs: `stat`, and `FileStatFields`.
 *
 * The `stat` pointer points to the struct which was returned after the `stat`/`lstat` syscall was run on this file.
 * In cases where we are able to get `dirent` information for the file, but not `stat` info (usually due to lack of
 *	permission), then both `stat* s` and `FileStatFields* f` will be set to `NULL`.
 *
 * This is done in order to limit the about of memory allocated for each file, especially when we can't access the
 *	information that would fill that memory.
 */
typedef struct FileStat			FileStat;
/**
 * @struct TargetInfo
 * @brief Basic information about the target of a symlink.
 *
 * Contains just enough information to display a symlink/alias's target after the arrow.
 *	- E.g. `source_link -> /path/to/target_path`
 *
 * The target is being stored as a seperate struct, so that the memory for this information doesn't have to be
 *	allocated for every single file, and will only be allocated when the source file is a link of some sort.
 *
 * @var TargetInfo::path	 The contents of the link - needed to print the basic arrow & path.
 * @var TargetInfo::colour	 The colour with which the file (i.e. the file's basename) should be printed.
 * @var TargetInfo::suffix	 The file suffix which should be printed after the filename (e.g. `/`, `*`, `=`, etc.).
 * @var TargetInfo::is_apple Whether the source of this link is a symbolic link, or an Apple alias file.
 */
typedef struct TargetInfo		TargetInfo;
/**
 * @struct FileStatFields
 * @brief Detailed information about a file, sourced from the `stat`/`lstat` syscalls.
 *
 * Contains more detailed information about a file than can be read from a `dirent` or `stat` object. All the info
 *	stored in this struct is calculated and assigned manually at runtime, by parsers implemented in this project.
 */
typedef struct FileStatFields	FileStatFields;

/* ——————————————————————————————————————————————————— */

// 2,147,483,647 files ≈ 2.1 Gb

typedef int something[]; 

typedef wchar_t icon_t;
typedef uint32_t flag_t;
typedef int16_t namlen_t;

typedef char *link_t;
typedef char  suff_t; /** Can be one of: `/`, `@`, `*`, `=`, `|`, `%` */
typedef char  unit_t;
typedef char  name_t[MAX_NAME_LEN]; // `char[MAX_NAME_LEN] = 255`
typedef char  path_t[MAX_PATH_LEN]; // `char[MAX_PATH_LEN] = 1024`

typedef char sizestr[MAX_SIZE_LEN]; // `char sizestr[MAX_SIZE_LEN]` = 10
typedef char modestr[MODE_STR_LEN]; // `char modestr[MODE_STR_LEN]` = 11
typedef char timestr[MAX_TIME_LEN]; // `char timestr[MAX_TIME_LEN]` = `(1 << 5)` = 32 
typedef char ugidstr[MAX_UGID_LEN]; // `char ugidstr[MAX_UGID_LEN]` = `(1 << 5)` = 32
typedef char flagstr[(MAX_FLAG_LEN + 1) * MAX_FLAG_NUM]; // `(MAX_FLAG_LEN + 1) * MAX_FLAG_NUM` = 168

/* ——————————————————————————————————————————————————— */

/// @brief The fields by which outputs can be sorted, using the `--sort` flag.
typedef enum {
	SB_DEFAULT, SB_NONE,
	SB_NAME, SB_SIZE, SB_TIME, SB_INODE, SB_DEVNO, SB_UID, SB_GID, SB_NLINK, SB_FLAGS, SB_MODE,
	/* SB_COUNT */
} SortByField;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !TYPES_H */
