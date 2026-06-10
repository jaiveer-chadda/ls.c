/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include "main.h"

static inline char* getType(const struct dirent *entry) {
	switch (entry->d_type) {
		case DT_UNKNOWN	: return "unknown"			;
		case DT_FIFO	: return "named pipe"		;
		case DT_CHR		: return "character device"	;
		case DT_DIR		: return "directory"		;
		case DT_BLK		: return "block device"		;
		case DT_REG		: return "regular file"		;
		case DT_LNK		: return "symbolic link"	;
		case DT_SOCK	: return "socket"			;
		case DT_WHT		: return "whiteout"			;
		default			: return ""					;
	}
}

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

static inline void getMode(const struct stat info, char mode_str[MAX_MODE_LEN]) {
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

int main(const int argc, const char *argv[]) {
	char target_dir[MAXNAMLEN];

	if (argc < 2) strncpy(target_dir, ".", 2);
	else snprintf(target_dir, MAXNAMLEN, "%s", argv[1]);

	DIR *directory = opendir(target_dir);

	if (directory == NULL) {
		fprintf(stderr, "Unable to read directory `%s`\n", target_dir);
		return EXIT_FAILURE;
	}

	struct dirent *entry;
	struct stat info;
	char target_path[MAXPATHLEN];
	char mode_str[PERMS_LEN];

	printf("%-*snlink\tsize\tuid\tgid\tflags\tmtime\t\ttype\t\tname\n", PERMS_LEN, "mode");

	while ((entry = readdir(directory)) != NULL) {
		if DO_IGNORE_FILE(entry) continue;

		snprintf(target_path, MAXPATHLEN, "%s/%s", target_dir, entry->d_name);
		stat(target_path, &info);

		getMode(info, mode_str);

		printf("%-*s"	, PERMS_LEN, mode_str		); // Mode of file
		printf("%d\t"	, info.st_nlink				); // Number of hard links
		printf("%lld\t"	, info.st_size				); // file size, in bytes
		printf("%d\t"	, info.st_uid				); // User ID of the file
		printf("%d\t"	, info.st_gid				); // Group ID of the file
		printf("%d\t"	, info.st_flags				); // user defined flags for file
		printf("%ld\t"	, info.st_mtimespec.tv_sec	); // time of last data modification
		printf("%s\t"	, getType(entry)			); // file type
		printf("%s\t"	, entry->d_name				); // entry name (up to MAXPATHLEN bytes)

		printf("\n");
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

/*
st_mode		st_nlink	st_size	st_uid	st_gid	st_flags	st_mtimespec.tv_sec		d_name	d_type
drwxr-xr-x@	4			37		jv		staff	hidden		Wed 10 Jun '26 01:15	source	/
*/

// spell:ignoreRegExp /%[-*.\d]*[a-z]\B/gi
