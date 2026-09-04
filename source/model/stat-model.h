/// @file model/stat-model.h

#ifndef NEW_STAT_MODEL_H
#define NEW_STAT_MODEL_H

#include <sys/stat.h>

#include "types.h"
#include "graphics/graphics.h"

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
	FileStat	*parent	; // 8 /** This file's parent directory, if one is known. */

	// these two fields will only point to valid objects if `stat` succeeded on this file.
	struct stat		*s	; // 8 /** Pointer to the struct returned when this file was passed to `stat`. */
	FileStatFields	*f	; // 8 /** Fields which can only be derived if the file was successfully `stat`ted. */

	// the following fields are all copied directly from `struct dirent`.
	char		*name	; // 8 /** The name of this file, as it will be displayed. */
	char		*path	; // 8 /** The absolute path to this file. */
	ino_t		inum	; // 8 /** The inode number for this file. */
	namlen_t	name_len; // 2 /** Length of the string pointed to by the `name` field (exc. `\0`) */
	namlen_t	path_len; // 2
	mode_t		mode	; // 2 /** The filetype and permissions (if `stat` worked) of the file. */

	// the following are fields which can be derived from just the information from `struct dirent`
	bool		has_xat	; // 1 /** Whether this file has extended attributes. */
	bool		has_acl	; // 1 /** Whether this file has an access control list. */

	FileColour	file_col; // 4 /** The colour which the file should be printed in. */
	icon_t		icon	; // 4 /** The icon to be shown before a filename. */

	modestr		mode_str; // 14 /** A string repr of the file's mode (type & permissions). */

	suff_t		suffix	; // 1 /** The symbol to be shown after a filename. From: `/` `@` `*` `=` `|` `%` */
	uint8_t		err_no	; // 1 /** The `errno` of a file if it fails to process for some reason. */
}; // 79 + 1 pad = 80

/* —— FileStatFields ——————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @struct FileStatFields
 * @brief Detailed information about a file, sourced from the `stat`/`lstat` syscalls.
 *
 * Contains more detailed information about a file than can be read from a `dirent` or `stat` object. All the info
 *	stored in this struct is calculated and assigned manually at runtime, by parsers implemented in this project.
 */
struct FileStatFields {
	TimeInfo	*times[TT_COUNT]; // 32 /** Information about the access, mod, change, and birth time of the file. */

	TargetInfo	*target		; // 8 /** Information about the target of a link, if one exists. */

	char		*size_str	; // 8 /** A string repr of the filesize. */
	char		*flag_str	; // 8 /** A string repr of the file's user-defined flags. `NULL` if file has no flags. */
	char		*usr_name	; // 8 /** The name of the file's owner. */
	char		*grp_name	; // 8 /** The name of the file's group. */

	FileStat	*children	; // 8 /** If this file is a dir, then `children` points to an array of `FileStat`s */
	int32_t		child_count	; // 4 /** The number of children that the directory has. If not a directory, then -1. */
	unit_t		size_unit	; // 1 /** The unit of a file's size. Also indicates if size is in `maj,min` format. */

	/// @todo amalgamate `do_link_hl` into `file_col`
	bool		do_link_hl	; // 1 /** Whether this file is a hardlink, and should be highlighted as such. */
	bool		is_mount	; // 1 /** Whether this file is a mount point or not. */
}; // 91 + 5 pad = 96b

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
	char		*path	; // 8 /** The contents of the link (usually the absolute path to the target file). */
	FileColour	colour	; // 4 /** The colour that the file should be displayed in. */
	char		suffix	; // 1 /** The symbol to be shown after the target's name. */
	bool		is_apple; // 1 /** Whether the link that pointed to this target was an apple alias (or a symlink). */
}; // 14 + 2 pad = 16b

/* —— TimeInfo ————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @struct TimeInfo
 * @brief Information about a file's time.
 *
 * Contains the string that should be used to display the time, as well as the colour that that string should be
 * printed in.
 */
struct TimeInfo { timestr str; TimeColour colour; }; // 36 + 0 pad = 36b

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !NEW_STAT_MODEL_H */
