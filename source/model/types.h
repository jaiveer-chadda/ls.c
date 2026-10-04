/// @file model/types.h

#ifndef TYPES_H
#define TYPES_H

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>

#include <sys/stat.h>
#include <sys/mount.h>

#include "consts.h"

#define st_btimespec st_birthtimespec
#define st_btime	 st_btimespec.tv_sec

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
typedef enum TimeType {
	A_TIME,	 /** [A]ccess time		 - Time a file's contents were last accessed. */
	M_TIME,	 /** [M]odification time - Time the contents of a file were last modified. */
	C_TIME,	 /** [C]reation time	 - Time the inode information of a file was last changed. */
	B_TIME,	 /** [B]irth time		 - Time the file was created (birthed). */
	TT_COUNT
} TimeType;
// spell:ignoreRegexp /(?<=\[[A-Z]\])\w+/g

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
 * @struct MountInfo
 * @brief Holds info about a mount point.
 *
 * Contains as much information as could be needed/wanted by the user to fully describe a mount point and its
 *	associated file system.
 *
 * `MountInfo::flags` is currently unused, as it's a lot of information to pack into a very small space.
 *	@todo implement the displaying of `MountInfo::flags`.
 *
 * @var MountInfo::fromname	Where the filesystem is mounted from (usually in the form `/dev/disk...`).
 * @var MountInfo::typename	String name of the type of filesystem (`devfs`, `autofs`, etc.).
 * @var MountInfo::owneruid	UID of the user that mounted the filesystem.
 * @var MountInfo::flags	Copy of mount-exported flags.
 */
typedef struct MountInfo		MountInfo;
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

typedef uint32_t flag_t	 ; /** The user/system defined flag/flags associated with a file. */
typedef wchar_t	 icon_t	 ; /** A single multibyte character defining the icon printed before a file's name. */
typedef int16_t	 namlen_t; /** The length of a name or path. */
typedef char	*link_t	 ; /** The path held by a symlink. */
typedef char	 suff_t	 ; /** A file's suffix. Can be one of: `/`, `@`, `*`, `=`, `|`, `%` */
typedef char	 unit_t	 ; /** The unit of a file's size. Also used to denote whether a size is zero, or is maj,min. */

typedef char  name_t[MAX_NAME_LEN];		/** `char  name_t[MAX_NAME_LEN]` = 255 */
typedef char  path_t[MAX_PATH_LEN];		/** `char  path_t[MAX_PATH_LEN]` = 1024 */
typedef char sizestr[MAX_SIZE_LEN];		/** `char sizestr[MAX_SIZE_LEN]` = 10 */
typedef char modestr[MODE_STR_LEN];		/** `char modestr[MODE_STR_LEN]` = 12 */
typedef char mttyp_t[MNT_TYPE_LEN];		/** `char mttyp_t[MNT_TYPE_LEN]` = 16 */
typedef char timestr[MAX_TIME_LEN];		/** `char timestr[MAX_TIME_LEN]` = `(1 << 5)` = 32 */
typedef char ugidstr[MAX_UGID_LEN];		/** `char ugidstr[MAX_UGID_LEN]` = `(1 << 5)` = 32 */
typedef bool lines_t[RECURSION_LIMIT];	/** `bool lines_t[RECURSION_LIMIT]` = 16 */
typedef char flagstr[(MAX_FLAG_LEN + 1) * MAX_FLAG_NUM]; /** `char flagstr[(MAX_FLAG_LEN + 1) * MAX_FLAG_NUM]` = 180 */

/** `char CLIFlag_t[MAX_OPT_FLAG_LEN + sizeof("--do-")]` = `20 + 6` = 26 */
typedef char CLIFlag_t[MAX_OPT_FLAG_LEN + sizeof("--do-")];

/* ——————————————————————————————————————————————————— */

/**
 * @enum SortByField
 * @brief The fields by which outputs can be sorted, using the `--sort`/`--sort-by` flag.
 */
typedef enum SortByField {
	SB_DEFAULT,	/** Sort by the default sorting order (usually by name). */
	SB_NONE	,	/** Don't sort files at all - leave them in the order defined by the OS, or by argument order. */

	SB_NAME	, /** Sort lex12ly by a file's name. Dotfiles first, then alphabetically, with all numbers in order. */
	SB_SIZE	, /** Sort by a file's size. */
	SB_TIME	, /** Sort by the time being displayed (modification time by default). */
	SB_INODE, /** Sort by a file's inode number. */
	SB_DEVNO, /** Sort by the device number of the file's filesystem. */
	SB_UID	, /** Sort by a file's owner's UID. */
	SB_GID	, /** Sort by a file's group's GID. */
	SB_NLINK, /** Sort by the number of links a file has. */
	SB_FLAGS, /** Sort by a file's user/super-user defined flags (sorts numerically by the raw hex flags). */
	SB_TYPE	, /** Sort files by their type defined in the first two digits of a file's octal mode. */
	SB_MODE	, /** Sort files by their permissions (sorts numerically by raw hex mode, excluding filetype). */
	/* SB_COUNT */
} SortByField;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !TYPES_H */
