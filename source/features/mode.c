/// @file features/mode/mode.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/acl.h>
#include <sys/xattr.h>

#include "features.h"
#include "form/formatting.h"
#include "options/options.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define EXT_MASK 0007000	/// A mask to get the extended bits (4,2,1 = uid, gid, sticky) from octal permissions.
#define USR_MASK S_IRWXU	/// A mask to get the user  octal permissions.
#define GRP_MASK S_IRWXG	/// A mask to get the group octal permissions.
#define OTH_MASK S_IRWXO	/// A mask to get the other octal permissions.

#define DO_NOTHING 0

/* ———————————————————————————————————————————————————————————————————————————————— */

#define SET_EXT_BIT(str, chr) /* exec == lowercase, non-exec == uppercase */ \
	((str)[2] = ((str)[2] == EXEC_BIT_CHAR) ? (chr) : (chr) - ('a' - 'A'))

#define PARSE_PERM(type, location, ext_char) do {							\
		getPermStr((type ## _str), (type ## _oct));							\
		if (ext_oct & (location)) SET_EXT_BIT((type ## _str), (ext_char));	\
	} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getPermStr(char *perm_str, const mode_t oct_digit) {
	perm_str[0] = oct_digit & 04 ? READ_BIT_CHAR  : NO_PERM_CHAR;
	perm_str[1] = oct_digit & 02 ? WRITE_BIT_CHAR : NO_PERM_CHAR;
	perm_str[2] = oct_digit & 01 ? EXEC_BIT_CHAR  : NO_PERM_CHAR;
	perm_str[3] = '\0';
}

/// @brief Gets the character representing the filetype specified by an octal type integer.
static inline char getModeType(const mode_t mode) {
	switch (mode & TYPE_MASK) {
		case S_IFIFO:	return PIPE_CHAR	; // named pipe		'|' / 'p'
		case S_IFCHR:	return CHRDEV_CHAR	; // char device	'c'
		case S_IFDIR:	return DIR_CHAR		; // directory		'/'
		case S_IFBLK:	return BLKDEV_CHAR	; // block device	'b'
		case S_IFREG:	return REGULAR_CHAR	; // regular file	'.' / '-'
		case S_IFLNK:	return SYMLINK_CHAR	; // symbolic link	'l'
		case S_IFSOCK:	return SOCKET_CHAR	; // socket			'=' / 's'
		case S_IFWHT:	return WHITEOUT_CHAR; // whiteout		'%' / 'w'
		default:		return UNKNOWN_CHAR	; // unknown		'?'
	}
}

/* ———————————————————————————————————————————————————————————————————————————————— */

inline char getTypeSuffix(const mode_t mode) {
	switch (mode & TYPE_MASK) {
		case S_IFLNK:	return SYMLINK_SUFFIX;	// symlink		 '@'
		case S_IFDIR:	return DIR_SUFFIX;		// directory	 '/'
		case S_IFIFO:	return PIPE_CHAR;		// named pipe	 '|'
		case S_IFSOCK:	return SOCKET_CHAR;		// socket		 '='
		case S_IFWHT:	return WHITEOUT_CHAR;	// whiteout		 '%'
	}
	if (mode & EXEC_MASK) return EXEC_SUFFIX;	// executable	 '*'
	return '\0';								// other/unknown
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getMode(modestr mode_str, const mode_t oct_mode) {
	// separate oct_mode by bit shifting it, leaving just one digit from 0-7 in each var
	const mode_t // Note: 3 = log2(8)
		ext_oct = (oct_mode & EXT_MASK) >> (3 * 3), // `d--s--s--t` == `7000`
		usr_oct = (oct_mode & USR_MASK) >> (3 * 2), // `drwx------` == `0700`
		grp_oct = (oct_mode & GRP_MASK) >> (3 * 1), // `d---rwx---` == `0070`
		oth_oct = (oct_mode & OTH_MASK) >> (3 * 0); // `d------rwx` == `0007`

	char usr_str[4], grp_str[4], oth_str[4];

	PARSE_PERM(usr, 04,	  SUID_X_BIT_CHAR);
	PARSE_PERM(grp, 02,	  SGID_X_BIT_CHAR);
	PARSE_PERM(oth, 01,	STICKY_X_BIT_CHAR);

	setLen(FI_mode_str,
		snprintf(mode_str, sizeof(modestr), "%c%s%s%s", getModeType(oct_mode), usr_str, grp_str, oth_str)
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool checkACL(const path_t path) {
	acl_t const p_acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	acl_free(p_acl);

	return p_acl != NULL;
}

bool checkXattr(const path_t path) {
	return listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_mode(const FileStat *const pFS) {
	printf("%0*o%s", getLen(FI_mode), pFS->mode, FIELD_PAD);
}

void print_mode_str(const FileStat *const pFS) {
	if (!DO_COLOUR() /* for debugging */ || true /**/) {
		char xa_buf[3] = {0};
		uint8_t xa_len = 0;

		if (pFS->has_xat) xa_buf[xa_len++] = XATTR_CHAR;
		if (pFS->has_acl) xa_buf[xa_len	 ] = ACL_CHAR;

		printf("%s" "%-*s" "%s", pFS->mode_str, getLen(FI_xat_acl), xa_buf, FIELD_PAD);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
