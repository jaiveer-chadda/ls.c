/// @file mode.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include "mode.h"

#define EXT_MASK 0007000	/// A mask to get the extended bits (4,2,1 = uid, gid, sticky) from octal permissions.
#define USR_MASK S_IRWXU	/// A mask to get the user octal permissions.
#define GRP_MASK S_IRWXG	/// A mask to get the group octal permissions.
#define OTH_MASK S_IRWXO	/// A mask to get the other octal permissions.

/// A mask to keep just the type information from the Unix octal permissions - (0o170000).
#define TYPE_MASK S_IFMT

#define SET_EXT_BIT(str, chr) /* exec == lowercase, non-exec == uppercase */ \
	str[2] = str[2] == 'x' ? chr : chr - ('a' - 'A')

#define PARSE_PERM(location, ext_char, type) \
	get_perm_str(type##_oct, type##_str); \
	if (ext_oct & location) SET_EXT_BIT(type##_str, ext_char)

/// @brief Gets the character representing the filetype specified by an octal type integer.
static inline char get_type_char(const mode_t mode) {
	switch (mode & TYPE_MASK) {
		case S_IFIFO:	return '|'; /* named pipe	('|' or 'p')	*/
		case S_IFCHR:	return 'c'; /* char device					*/
		case S_IFDIR:	return 'd'; /* directory					*/
		case S_IFBLK:	return 'b'; /* block device					*/
		case S_IFREG:	return '.'; /* regular file	('.' or '-')	*/
		case S_IFLNK:	return 'l'; /* symbolic link				*/
		case S_IFSOCK:	return 's'; /* socket						*/
		case S_IFWHT:	return '%'; /* whiteout		('%' or 'w')	*/
		default:		return ' '; /* unknown						*/
	}
}

static inline void get_perm_str(const mode_t oct_digit, char *perm_str) {
	strcpy(perm_str, "---");

	if (oct_digit & 04) perm_str[0] = 'r';
	if (oct_digit & 02) perm_str[1] = 'w';
	if (oct_digit & 01) perm_str[2] = 'x';
}

void getMode(const struct stat info, char mode_str[MAX_MODE_LEN]) {
	const mode_t oct_mode = info.st_mode;

	char usr_str[4], grp_str[4], oth_str[4];
	const mode_t // Note: 3 = log2(8)
		ext_oct = (oct_mode & EXT_MASK) >> (3 * 3), // `d--s--s--t` == `7000`
		usr_oct = (oct_mode & USR_MASK) >> (3 * 2), // `drwx------` == `0700`
		grp_oct = (oct_mode & GRP_MASK) >> (3 * 1), // `d---rwx---` == `0070`
		oth_oct = (oct_mode & OTH_MASK) >> (3 * 0); // `d------rwx` == `0007`

	PARSE_PERM(04, 's', usr);
	PARSE_PERM(02, 's', grp);
	PARSE_PERM(01, 't', oth);

	snprintf(
		mode_str, MAX_MODE_LEN,
		"%c%s%s%s", get_type_char(oct_mode), usr_str, grp_str, oth_str
	);
}
