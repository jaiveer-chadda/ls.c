/// @file features/mode/mode.c

#include <stdio.h>
#include <string.h>

#include <sys/acl.h>
#include <sys/xattr.h>

#include "features.h"
#include "form/formatting.h"
#include "options/options.h"
#include "graphics/graphics.h"

static inline FileColour getTypeColour(const char type_char); /** @todo move */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define EXT_MASK 0007000	/// A mask to get the extended bits (4,2,1 = uid, gid, sticky) from octal permissions.
#define USR_MASK S_IRWXU	/// A mask to get the user  octal permissions.
#define GRP_MASK S_IRWXG	/// A mask to get the group octal permissions.
#define OTH_MASK S_IRWXO	/// A mask to get the other octal permissions.

#define UGO_RWX_MASK	(S_IRWXU | S_IRWXG | S_IRWXO)

#define S_IFSOC S_IFSOCK
#define LOG2_8 3 /** `log_2(8) = 3` (i.e., log base 2 of 8) */

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
		case S_IFIFO: return PIPE_CHAR		; // named pipe		'|' / 'p'
		case S_IFCHR: return CHRDEV_CHAR	; // char device	'c'
		case S_IFDIR: return DIR_CHAR		; // directory		'/'
		case S_IFBLK: return BLKDEV_CHAR	; // block device	'b'
		case S_IFREG: return REGULAR_CHAR	; // regular file	'.' / '-'
		case S_IFLNK: return SYMLINK_CHAR	; // symbolic link	'l'
		case S_IFSOC: return SOCKET_CHAR	; // socket			'=' / 's'
		case S_IFWHT: return WHITEOUT_CHAR	; // whiteout		'%' / 'w'
		default:	  return UNKNOWN_CHAR	; // unknown		'?'
	}
}

/* ———————————————————————————————————————————————————————————————————————————————— */

inline char getTypeSuffix(const mode_t mode) {
	switch (mode & TYPE_MASK) {
		case S_IFLNK: return SYMLINK_SUFFIX	; // symlink	'@'
		case S_IFDIR: return DIR_SUFFIX		; // directory	'/'
		case S_IFIFO: return PIPE_CHAR		; // named pipe	'|'
		case S_IFSOC: return SOCKET_CHAR	; // socket		'='
		case S_IFWHT: return WHITEOUT_CHAR	; // whiteout	'%'
	}
	if (mode & EXEC_MASK) return EXEC_SUFFIX; // executable '*'
	return '\0';							  // other/unknown
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getMode(modestr mode_str, const mode_t oct_mode) {
	// separate oct_mode by bit shifting it, leaving just one digit from 0-7 in each var
	const mode_t
		ext_oct = (oct_mode & EXT_MASK) >> (LOG2_8 * 3), // `d--s--s--t` == `7000`
		usr_oct = (oct_mode & USR_MASK) >> (LOG2_8 * 2), // `drwx------` == `0700`
		grp_oct = (oct_mode & GRP_MASK) >> (LOG2_8 * 1), // `d---rwx---` == `0070`
		oth_oct = (oct_mode & OTH_MASK) >> (LOG2_8 * 0); // `d------rwx` == `0007`

	char usr_str[4], grp_str[4], oth_str[4];

	PARSE_PERM(usr, 04, SUID_X_BIT_CHAR);
	PARSE_PERM(grp, 02, SGID_X_BIT_CHAR);
	PARSE_PERM(oth, 01, STIC_X_BIT_CHAR);

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
	return listxattr(path, NULL, 0, XATTR_NOFOLLOW | XATTR_NOFOLLOW_ANY) > 0;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define R S_IROTH
#define W S_IWOTH
#define X S_IXOTH

static inline PermColour getDigColour(const mode_t mode_dig, const bool is_oth, const bool is_reg) {
	switch (mode_dig) {
		case 0|0|0: return PC_NONE;

		case 0|0|X: return is_reg ? PC_X_REG : PC_X_NRG;
		case 0|W|0: return PC_W_UG;
		case R|0|0: return PC_READ;

		case 0|W|X: return PC_WRT_EXE;
		case R|0|X: return PC_REA_EXE;
		case R|W|0: return PC_REA_WRT;
		case R|W|X: return PC_RWX_ALL;
	}

	if ((mode_dig & (0|W|0)) && is_oth)
		return PC_W_OTH;

	return PC_NONE;
}

#undef R
#undef W
#undef X

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline PermColour getExtColour(const mode_t mode) {
	if (mode & S_ISUID) return S_IXUSR & mode ? PC_SUID_X : PC_SUID_N;
	if (mode & S_ISGID) return S_IXGRP & mode ? PC_SGID_X : PC_SGID_N;
	if (mode & S_ISVTX) return S_IXOTH & mode ? PC_STIC_X : PC_STIC_N;
	/**/				return PC_NONE;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DIG_TO_CHR(dig) ((char)('0' + (unsigned)(dig)))

#define ADD_COLOUR(src, dst_ptr) do {						\
	uint8_t col_len = 0;									\
	const char *const colour = getcollen((src), &col_len);	\
	memcpy((dst_ptr), colour, col_len);						\
	(dst_ptr) += col_len;									\
} while (0)

/* ————————————————————————————————————————————————— */

void print_mode(const FileStat *const pFS) {
	if (!DO_COLOUR()) {
		printf("%06o%ls", pFS->mode, FIELD_PAD);
		return;
	}

	const mode_t
		type = (pFS->mode & TYPE_MASK) >> (LOG2_8 * 4), /** The two octal digits representing the file's type. */
		ext	 = (pFS->mode & EXT_MASK ) >> (LOG2_8 * 3); /** The digit representing the file's extended permissions. */

	const FileColour file_col = getTypeColour(getModeType(pFS->mode));
	const PermColour ext_col  = getExtColour(pFS->mode);

	char output[96] = {0};
	char *out_ptr = output;

	ADD_COLOUR(file_colour_esc[file_col], out_ptr);
	// split the type section into two bits, and assign those to `out_ptr` directly
	*out_ptr++ = DIG_TO_CHR((type & 010) >> LOG2_8);
	*out_ptr++ = DIG_TO_CHR((type & 007));

	ADD_COLOUR(perm_colour_esc[ext_col], out_ptr);
	*out_ptr++ = DIG_TO_CHR(ext);

	for (int i = 0; i < 3; i++) {
		// shift each section of the mode over, so that the part we want to analyse is the least significant digit.
		//	then apply a mask so only the least significant digit is left, and `mode_dig` is `0o00 <= mode_dig <= 0o07`
		const mode_t mode_dig = (pFS->mode >> (LOG2_8 * (2 - i))) & S_IRWXO;
		const PermColour dig_col = getDigColour(mode_dig, /*is_oth*/(i == 2), /*is_reg*/(pFS->mode & S_IFREG));

		ADD_COLOUR(perm_colour_esc[dig_col], out_ptr);
		*out_ptr++ = DIG_TO_CHR(mode_dig);
	}

	printf("%s%s%ls", output, getcol(RESET_ALL), FIELD_PAD);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
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
		case WRIT_BIT_CHAR: return IS_OWR() ? PC_W_OTH : PC_W_UG ; // make the `OW` bit a distinct colour
		case EXEC_BIT_CHAR: return IS_REG() ? PC_X_REG : PC_X_NRG; // reg files and other files have separate exec cols
		// colour the UID and GID bits based on whether they're executable or not
		//	`IS_UID()` determines if we're currently looking at the usr or group bit
		case SUGI_X_BIT_CHAR: return IS_UID() ? PC_SUID_X : PC_SGID_X;
		case SUGI_N_BIT_CHAR: return IS_UID() ? PC_SUID_N : PC_SGID_N;
		// colour the sticky bit based on whether the files are executables or not
		case STIC_X_BIT_CHAR: return PC_STIC_X;
		case STIC_N_BIT_CHAR: return PC_STIC_N;
	}

	return PC_NONE;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_mode_str(const FileStat *const pFS) {
	char xa_buf[32] = {0};
	char *xab_ptr = xa_buf;

	if (!DO_COLOUR()) {
		// fill the buffer with the xat/acl chars, and keep track of the length
		if (pFS->has_xat) *xab_ptr++ = XATTR_CHAR;
		if (pFS->has_acl) *xab_ptr++ = ACL_CHAR;

		printf("%s" "%-*s" "%ls", pFS->mode_str, getLen(FI_xat_acl), xa_buf, FIELD_PAD);
		return;
	}

	/* ————————————————————————————————————————————————— */

	char output[256] = {0};
	char *out_ptr = output;

	// firstly, add the type's colour & character to the output string
	ADD_COLOUR(file_colour_esc[getTypeColour(pFS->mode_str[0])], out_ptr);
	*out_ptr++ = pFS->mode_str[0];

	/* ————————————————————————————————————————————————— */

	// iterate through the permissions portion of the string, and add a colour & char for each of those
	PermColour last_esc = PC_COUNT, esc;
	for (int i = 1; i < 1 + (3 * 3); i++) {
		// get this char's colour
		esc = getPermColour(pFS->mode_str, i);
		// only add a colour if the last colour wasn't also the same
		if (esc != last_esc) ADD_COLOUR(perm_colour_esc[esc], out_ptr);

		*out_ptr++ = pFS->mode_str[i];
		last_esc = esc;
	}

	/* ————————————————————————————————————————————————— */

	// finally, find and add the xattr and acl colours/chars, if they exist
	if (pFS->has_xat) { ADD_COLOUR(XATTR_COLOUR, xab_ptr); *xab_ptr++ = XATTR_CHAR; }
	if (pFS->has_acl) { ADD_COLOUR(ACL_COLOUR  , xab_ptr); *xab_ptr++ = ACL_CHAR  ; }

	const int pure_xa_len = pFS->has_xat + pFS->has_acl;
	// only print a final reset sequence if there were no extra characters, and the final perm colour had a background
	const bool do_reset = pure_xa_len == 0 && has_bg(perm_colour_esc[esc]);

	printf("%s%s" "%s%*s" "%ls",
		output, do_reset ? getcol(RESET_ALL) : "",
		// print the xattr & acl chars, and pad appropriately
		xa_buf, getLen(FI_xat_acl) - pure_xa_len, "", 
		FIELD_PAD
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore ifsoc
