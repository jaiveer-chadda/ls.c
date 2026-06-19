/// @file info/info.h

#include "../model/stat-model.h"

#define CURRENT_DIR "."

DIR* getDirectory(char *target_dir, const int argc, const char *argv[]);

void getAllFileInfo(
	FileInfo dirs[], FileInfo files[],
	int *dir_count, int *file_count,
	DIR *directory, const char *target_dir
);

void getFieldLengths(const FileInfo *all_files, const int *count);
