/// @file sorting/sort-files.c

#include <stdlib.h>
#include <string.h>

#include "sort.h"

static int compare_names(const void *file_1, const void *file_2) {
	const FileInfo *f1 = (const FileInfo *)file_1;
	const FileInfo *f2 = (const FileInfo *)file_2;

	return strcmp(f1->name, f2->name);
}

void sortFiles(FileInfo *all_files, const int *count) {
	qsort(all_files, *count, sizeof(FileInfo), compare_names);
}
