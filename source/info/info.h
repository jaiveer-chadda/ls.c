/// @file info/info.h

#ifndef INFO_INITIALISED
#define INFO_INITIALISED

#include "model/stat-model.h"

#define DOTDIR "."

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getAllFileInfo(
	FileInfo dirs[], FileInfo files[], int *dir_count, int *file_count, const DIR *dir_obj, const char *dotdir_path
);

/* ———————————————————————————————————————————————————— */

void getFieldLengths(const FileInfo *all_files, const int *count);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !INFO_INITIALISED */
