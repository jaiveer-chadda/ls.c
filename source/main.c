/// @file main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "main.h"

#define MAXPATHLEN __DARWIN_MAXPATHLEN

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
	struct stat info;
	char target_path[MAXPATHLEN];

	while ((entry = readdir(directory)) != NULL) {
		if IS_DOT(entry) continue;

		snprintf(target_path, MAXPATHLEN, "%s/%s", target_dir, entry->d_name);
		stat(target_path, &info);

		printf("\n———————————————————————————\n");
		printf("name    : %s\n",	entry->d_name	); // entry name (up to MAXPATHLEN bytes)
		printf("type    : %s\n",	getType(entry)	); // file type
		printf("ino     : %llu\n",	entry->d_ino	); // file number of entry
		printf("seekoff : %llu\n",	entry->d_seekoff); // seek offset (optional, used by servers)
		printf("reclen  : %d\n",	entry->d_reclen	); // length of this record
		printf("namlen  : %d\n",	entry->d_namlen	); // length of string in d_name
		printf("\n");
		printf("access  : %ld\n",	info.st_atimespec.tv_sec	); // time of last access
		printf("modify  : %ld\n",	info.st_mtimespec.tv_sec	); // time of last data modification
		printf("change  : %ld\n",	info.st_ctimespec.tv_sec	); // time of last status change
		printf("birth   : %ld\n",	info.st_birthtimespec.tv_sec); // time of file creation (birth)
		printf("\n");
		printf("dev     : %d\n",	info.st_dev			); // ID of device containing file
		printf("mode    : %04o\n",	info.st_mode & 0777	); // Mode of file (see below)
		printf("nlink   : %d\n",	info.st_nlink		); // Number of hard links
		printf("ino     : %llu\n",	info.st_ino			); // File serial number
		printf("uid     : %d\n",	info.st_uid			); // User ID of the file
		printf("gid     : %d\n",	info.st_gid			); // Group ID of the file
		printf("rdev    : %d\n",	info.st_rdev		); // Device ID
		printf("size    : %lld\n",	info.st_size		); // file size, in bytes
		printf("blocks  : %lld\n",	info.st_blocks		); // blocks allocated for file
		printf("blksize : %d\n",	info.st_blksize		); // optimal blocksize for I/O
		printf("flags   : %d\n",	info.st_flags		); // user defined flags for file
		printf("gen     : %d\n",	info.st_gen			); // file generation number
	}

	closedir(directory);
	return EXIT_SUCCESS;
}
