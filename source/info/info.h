/// @file info/info.h

#include "../model/stat-model.h"

// get-directory.c

DIR* getDirectory(char *target_dir, const int argc, const char *argv[]);

// get-file-info.c

void getAllFileInfo(FileInfo *all_files, int *count, DIR *directory, const char *target_dir);

// parse-info.c

void getFieldLengths(const FileInfo *all_files, const int *count);

void printHeader(void);

void printFields(const FileInfo *all_files, const int *count);
