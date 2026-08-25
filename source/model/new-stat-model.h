/// @file model/new-stat-model.h

#ifndef NEW_STAT_MODEL_INITIALISED
#define NEW_STAT_MODEL_INITIALISED

#include "types.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

extern path_t G_DOTDIR_PATH;
extern const char *argv0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	// ————————————— custom fields ——————————————————————
	struct FileStatFields* f; // 128 /** Fields which can only be derived if the file was successfully `stat`ted. */

	// ————————————— `struct stat*` —————————————————————
	struct stat* s			; // 8 /** Pointer to the struct returned when this file was `stat`ted. */

	// ————————————— from `struct dirent` ———————————————
	// these are all fields which can be derived from `struct dirent`, and don't come from `struct stat`.
	char*		name		; // 8 /** The name of this file, as it will be displayed. */
	uint16_t	name_len	; // 2 (dirent.d_namlen) /** The length of the string pointed to by the `name` field. */
	uint8_t		type		; // 1 (dirent.d_type) /** The raw type & permissions of the file. */
	uint64_t	inum		; // 8 (dirent.d_ino / (stat.st_ino)
} FileStat;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct { TimeColour colour; timestr time_str;		} TimeInfo;
typedef enum   { A_TIME, M_TIME, C_TIME, B_TIME, TIME_COUNT	} TimeType;

struct FileStatFields {
	// TODO: amalgamate `do_link_hl` into `file_col`
	bool		do_link_hl	; // 1 /** Whether this file is a hardlink, and should be highlghted as such. */
	bool		is_mount	; // 1 /** Whether this file is a mount point or not. */
	bool		has_xattr	; // 1 /** Whether this file has extended attributes. */
	bool		has_acl		; // 1 /** Whether this file has an access control list. */

	char		size_unit	; // 1 /** The unit of a file's size. Also indicates if size is in `maj,min` format. */
	char		suffix		; // 1 /** The symbol to be shown after a filename. From: `/` `@` `*` `=` `|` `%` */

	wchar_t		icon		; // 4 /** The icon to be shown before a filename. */
	FileColour	file_col	; // 4
	TargetInfo*	target		; // 16 /** Information about the target of a link, if one exists. */

	char		size_str[10]; // 10 /** A string repr of the filesize. */
	char		mode_str[11]; // 11 /** A string repr of the file's mode (type & permissions). */
	char		usr_name[32]; // 32 /** The name of the file's owner. */
	char		grp_name[32]; // 32 /** The name of the file's group. */

	char*		flag_str	; // 8 /** A string repr of the file's user-defined flags. `NULL` if file has no flags. */
	FileStat*	children	; // 8 /** If this file is a dir, then `children` points to an array of `FileStat`s */

	TimeInfo* times[TIME_COUNT]; // 32
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	char*		path		; // 8 /** The absolute path to the target file. */

	FileColour	colour		; // 4 /** The colour that the file should be displayed in. */
	bool		is_apple	; // 1 /** Whether the link that pointed to this target was an apple alias (or a symlink). */
	char		suffix		; // 1 /** The symbol to be shown after the target's name. */
} TargetInfo;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !NEW_STAT_MODEL_INITIALISED */
