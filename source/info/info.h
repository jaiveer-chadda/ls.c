/// @file info/info.h

#include "../model/stat-model.h"

// get-directory.c

DIR* getDirectory(char *target_dir, const int argc, const char *argv[]);

// get-file-info.c

void getAllFileInfo(
	FileInfo *dirs, FileInfo *files,
	int *dir_count, int *file_count,
	DIR *directory, const char *target_dir
);

// parse-info.c

void getFieldLengths(const FileInfo *all_files, const int *count);
