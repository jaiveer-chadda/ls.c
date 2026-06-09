/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// #include <sys/stat.h>

#include "main.h"

char* getType(const struct dirent *entry) {
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
	// struct stat file_info;

	while ((entry = readdir(directory)) != NULL) {
		if IS_DOT(entry) continue;
		printf("———————————————————————————\n");
		printf("name    : %s\n",	entry->d_name	);
		printf("type    : %s\n",	getType(entry)	);
		printf("ino     : %llu\n",	entry->d_ino	);
		printf("seekoff : %llu\n",	entry->d_seekoff);
		printf("reclen  : %d\n",	entry->d_reclen	);
		printf("namlen  : %d\n",	entry->d_namlen	);
	}

	closedir(directory);
	return EXIT_SUCCESS;
}

/*
st_dev
st_mode
st_nlink
st_ino
st_uid
st_gid
st_rdev
st_size
st_blocks
st_blksize
st_flags
st_gen
st_lspare
st_qspare
*/
