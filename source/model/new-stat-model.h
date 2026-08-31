/// @file model/new-stat-model.h

#ifndef NEW_STAT_MODEL_INITIALISED
#define NEW_STAT_MODEL_INITIALISED

#include <sys/stat.h>

#include "types.h"
#include "graphics/graphics.h"

typedef struct { TimeColour colour; timestr time_str;		} TimeInfo;
typedef enum   { A_TIME, M_TIME, C_TIME, B_TIME, TIME_COUNT	} TimeType;

/* —— FileStat (main) —————————————————————————————————————————————————————————————————————————————————————————————— */

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
struct FileStat {
	struct stat*	s	; // 8 /** Pointer to the struct returned when this file was `stat`ted. */
	FileStatFields*	f	; // ? /** Fields which can only be derived if the file was successfully `stat`ted. */

	// the following are all fields which can be derived from `struct dirent`, and don't come from `struct stat`.
	char*		name	; // 8 /** The name of this file, as it will be displayed. */
	int16_t		name_len; // 2 /** Length of the string pointed to by the `name` field (exc. `\0`) */
	mode_t		mode	; // 2 /** The filetype and permissions (if `stat` worked) of the file. */
	uint64_t	inum	; // 8 /** The inode number for this file. */
	wchar_t		icon	; // 4 /** The icon to be shown before a filename. */
	char		suffix	; // 1 /** The symbol to be shown after a filename. From: `/` `@` `*` `=` `|` `%` */
};

/* —— FileStatFields ——————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @struct FileStatFields
 * @brief Detailed information about a file, sourced from the `stat`/`lstat` syscalls.
 *
 * Contains more detailed information about a file than can be read from a `dirent` or `stat` object. All the info
 *	stored in this struct is calculated and assigned manually at runtime, by parsers implemented in this project.
 */
struct FileStatFields {
	// TODO: amalgamate `do_link_hl` into `file_col`
	bool		do_link_hl	; // 1 /** Whether this file is a hardlink, and should be highlighted as such. */
	bool		is_mount	; // 1 /** Whether this file is a mount point or not. */
	bool		has_xattr	; // 1 /** Whether this file has extended attributes. */
	bool		has_acl		; // 1 /** Whether this file has an access control list. */

	char		size_unit	; // 1 /** The unit of a file's size. Also indicates if size is in `maj,min` format. */
	FileColour	file_col	; // 4
	TargetInfo*	target		; // 16 /** Information about the target of a link, if one exists. */

	char		mode_str[11]; // 11 /** A string repr of the file's mode (type & permissions). */
	char*		size_str	; // 8 /** A string repr of the filesize. */
	char*		flag_str	; // 8 /** A string repr of the file's user-defined flags. `NULL` if file has no flags. */
	char*		usr_name	; // 8 /** The name of the file's owner. */
	char*		grp_name	; // 8 /** The name of the file's group. */

	FileStat*	children	; // 8 /** If this file is a dir, then `children` points to an array of `FileStat`s */
	int32_t		child_count	; // 4 /** The number of children that the directory has. If not a directory, then -1. */

	TimeInfo*	times[TIME_COUNT]; // 32
};

/* —— TargetInfo ——————————————————————————————————————————————————————————————————————————————————————————————————— */

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
struct TargetInfo {
	char*		path	; // 8 /** The contents of the link (usually the absolute path to the target file). */
	FileColour	colour	; // 4 /** The colour that the file should be displayed in. */
	char		suffix	; // 1 /** The symbol to be shown after the target's name. */
	bool		is_apple; // 1 /** Whether the link that pointed to this target was an apple alias (or a symlink). */
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !NEW_STAT_MODEL_INITIALISED */
