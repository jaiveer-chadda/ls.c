/// @file info/info.h

#ifndef INFO_INITIALISED
#define INFO_INITIALISED

#include "model/stat-model.h"

#define DOTDIR "."

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

DIR* getDirectory(path_t target_dir, const int files_start, const int argc, const char *argv[]);

void getAllFileInfo(
	FileInfo dirs[], FileInfo files[], int *dir_count, int *file_count, DIR *directory, const char *dotdir_path
);

/* ———————————————————————————————————————————————————— */

void getFieldLengths(const FileInfo *all_files, const int *count);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !INFO_INITIALISED */
