/// @file features/mode/mode.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../model/stat-model.h"
#include "../../graphics/graphics.h"

#include "mode.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define EXT_MASK 0007000	/// A mask to get the extended bits (4,2,1 = uid, gid, sticky) from octal permissions.
#define USR_MASK S_IRWXU	/// A mask to get the user octal permissions.
#define GRP_MASK S_IRWXG	/// A mask to get the group octal permissions.
#define OTH_MASK S_IRWXO	/// A mask to get the other octal permissions.

/* ———————————————————————————————————————————————————————————————————————————————— */

#define SET_EXT_BIT(str, chr) /* exec == lowercase, non-exec == uppercase */ \
	str[2] = str[2] == 'x' ? chr : chr - ('a' - 'A')

#define PARSE_PERM(location, ext_char, type) do { \
		getPermStr(type##_oct, type##_str); \
		if (ext_oct & location) SET_EXT_BIT(type##_str, ext_char); \
	} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getPermStr(const mode_t oct_digit, char *perm_str) {
	strcpy(perm_str, NO_PERM_STR NO_PERM_STR NO_PERM_STR);

	if (oct_digit & 04) perm_str[0] = 'r';
	if (oct_digit & 02) perm_str[1] = 'w';
	if (oct_digit & 01) perm_str[2] = 'x';
}

/// @brief Gets the character representing the filetype specified by an octal type integer.
static inline char getModeType(const mode_t mode) {
	switch (mode & TYPE_MASK) {
		case S_IFIFO:	return PIPE_CHAR	; // named pipe		('|' or 'p')
		case S_IFCHR:	return CHRDEV_CHAR	; // char device
		case S_IFDIR:	return DIR_CHAR		; // directory
		case S_IFBLK:	return BLKDEV_CHAR	; // block device
		case S_IFREG:	return REGULAR_CHAR	; // regular file	('.' or '-')
		case S_IFLNK:	return SYMLINK_CHAR	; // symbolic link
		case S_IFSOCK:	return SOCKET_CHAR	; // socket			('=' or 's')
		case S_IFWHT:	return WHITEOUT_CHAR; // whiteout		('%' or 'w')
		default:		return ' '; // unknown
	}
}

/* ———————————————————————————————————————————————————————————————————————————————— */

inline char getTypeSuffix(const mode_t mode) {
	switch (mode & TYPE_MASK) {
		case S_IFLNK:	return SYMLINK_SUFFIX;	// symlink
		case S_IFDIR:	return DIR_SUFFIX;		// directory
		case S_IFIFO:	return PIPE_CHAR;		// named pipe
		case S_IFSOCK:	return SOCKET_CHAR;		// socket
		case S_IFWHT:	return WHITEOUT_CHAR;	// whiteout
	}
	if (mode & EXEC_MASK) return EXEC_SUFFIX;	// executable
	return '\0';								// other/unknown
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getMode(modestr mode_str, const mode_t oct_mode) {
	const mode_t // Note: 3 = log2(8)
		ext_oct = (oct_mode & EXT_MASK) >> (3 * 3), // `d--s--s--t` == `7000`
		usr_oct = (oct_mode & USR_MASK) >> (3 * 2), // `drwx------` == `0700`
		grp_oct = (oct_mode & GRP_MASK) >> (3 * 1), // `d---rwx---` == `0070`
		oth_oct = (oct_mode & OTH_MASK) >> (3 * 0); // `d------rwx` == `0007`

	char usr_str[4], grp_str[4], oth_str[4];

	PARSE_PERM(04, 's', usr);
	PARSE_PERM(02, 's', grp);
	PARSE_PERM(01, 't', oth);

	snprintf(mode_str, MAX_MODE_LEN, "%c%s%s%s", getModeType(oct_mode), usr_str, grp_str, oth_str);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
