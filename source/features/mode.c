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

/* ———————————————————————————————————————————————————————————————————————————————— */

#define SET_EXT_BIT(str, chr) /* exec == lowercase, non-exec == uppercase */ \
	((str)[2] = ((str)[2] == EXEC_BIT_CHAR) ? (chr) : (chr) - ('a' - 'A'))

#define PARSE_PERM(type, location, ext_char) do {							\
		getPermStr((type ## _str), (type ## _oct));							\
		if (ext_oct & (location)) SET_EXT_BIT((type ## _str), (ext_char));	\
	} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void getPermStr(char *perm_str, const mode_t oct_digit) {
	perm_str[0] = oct_digit & 04 ? READ_BIT_CHAR : NO_PERM_CHAR;
	perm_str[1] = oct_digit & 02 ? WRIT_BIT_CHAR : NO_PERM_CHAR;
	perm_str[2] = oct_digit & 01 ? EXEC_BIT_CHAR : NO_PERM_CHAR;
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
	printf("%0*o%ls", getLen(FI_mode), pFS->mode, FIELD_PAD);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline FileColour getTypeColour(const char type_char) {
	switch (type_char) {
		case REGULAR_CHAR	: return FC_REGULAR	;
		case DIR_CHAR		: return FC_DIRECT	;
		case SYMLINK_CHAR	: return FC_SYMLINK	;
		case PIPE_CHAR		: return FC_PIPE	;
		case SOCKET_CHAR	: return FC_SOCKET	;
		case CHRDEV_CHAR	: return FC_CHR_DEV	;
		case BLKDEV_CHAR	: return FC_BLK_DEV	;
		case WHITEOUT_CHAR	: return FC_WHITEOUT;
		default				: return FC_REGULAR	;
	}
}

#define IS_REG() (mode_str[0] == REGULAR_CHAR)	/// Whether the file is a regular file or not.
#define IS_UID() (idx == 3) /// `3` is the index of the SUID bit in the mode string.
#define IS_OWR() (idx == 8) /// `8` is the index of the `other-writable` bit in the mode string.

static inline char getPermColour(const char *mode_str, const int idx) {
	switch (mode_str[idx]) {
		case NO_PERM_CHAR: return PC_NONE; // this permission bit isn't set

		case READ_BIT_CHAR: return PC_READ; // any of the 3 `read` bits
		case WRIT_BIT_CHAR: return IS_OWR() ? PC_W_OTHER : PC_W_USRGRP; // make the `OW` bit a distinct colour
		case EXEC_BIT_CHAR: return IS_REG() ? PC_X_REG	 : PC_X_NREG;
		// colour the UID and GID bits based on whether they're executable or not
		//	`IS_UID()` determines if we're currently looking at the usr or group bit
		case SUGID_X_BIT_CHAR: return IS_UID() ? PC_SUID_X : PC_SGID_X;
		case SUGID_N_BIT_CHAR: return IS_UID() ? PC_SUID_N : PC_SGID_N;

		// colour the sticky bit based on whether the files are executables or not
		case STICKY_X_BIT_CHAR: return PC_STICKY_X;
		case STICKY_N_BIT_CHAR: return PC_STICKY_N;
	}

	return PC_NONE;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_mode_str(const FileStat *const pFS) {
	char xa_buf[32] = {0};
	uint8_t xa_len = 0;

	if (!DO_COLOUR()) {
		if (pFS->has_xat) xa_buf[xa_len++] = XATTR_CHAR;
		if (pFS->has_acl) xa_buf[xa_len	 ] = ACL_CHAR;

		printf("%s" "%-*s" "%ls", pFS->mode_str, getLen(FI_xat_acl), xa_buf, FIELD_PAD);
		return;
	}

	char output[256] = {0};
	char *out_ptr = output;
	const char *colour;
	uint8_t col_len = 0;

	colour = getcollen(file_colour_esc[getTypeColour(pFS->mode_str[0])], &col_len);
	memcpy(out_ptr, colour, col_len);
	out_ptr += col_len;

	*out_ptr++ = pFS->mode_str[0];

	PermColour last_esc, esc = PC_COUNT;

	for (int i = 1; i < 1 + (3 * 3); i++) {
		last_esc = esc;
		esc = getPermColour(pFS->mode_str, i);

		if (esc != last_esc) {
			colour = getcollen(perm_colour_esc[esc], &col_len);
			memcpy(out_ptr, colour, col_len);
			out_ptr += col_len;
		}

		*out_ptr++ = pFS->mode_str[i];
	}

	const int pure_xa_len = pFS->has_xat + pFS->has_acl;
	const bool do_reset = pure_xa_len == 0 && perm_colour_esc[esc].has_bg();

	if (pFS->has_xat) {
		colour = getcollen(XATTR_COLOUR, &col_len);
		memcpy(&xa_buf[xa_len], colour, col_len);
		xa_len += col_len;

		xa_buf[xa_len++] = XATTR_CHAR;
	}

	if (pFS->has_acl) {
		colour = getcollen(ACL_COLOUR, &col_len);
		memcpy(&xa_buf[xa_len], colour, col_len);
		xa_len += col_len;

		xa_buf[xa_len++] = ACL_CHAR;
	}

	printf("%s" "%s%*s" "%s" "%ls",
		output,
		xa_buf, getLen(FI_xat_acl) - pure_xa_len, "", 
		do_reset ? getcol(RESET_ALL) : "",
		FIELD_PAD
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
