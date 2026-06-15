/// @file sorting/sort-files.c

#include <stdlib.h>
#include <string.h>

#include "sort.h"

static int compare_names(const void *file_1, const void *file_2) {
	const FileInfo *f1 = (const FileInfo *)file_1;
	const FileInfo *f2 = (const FileInfo *)file_2;

	return strcmp(f1->name, f2->name);
}

void sortFiles(FileInfo *dirs, FileInfo *files, const int *dir_count, const int *file_count) {
	qsort( dirs,  *dir_count, sizeof(FileInfo), compare_names);
	qsort(files, *file_count, sizeof(FileInfo), compare_names);
}
