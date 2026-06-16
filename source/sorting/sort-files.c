/// @file sorting/sort-files.c

#include <stdlib.h>
#include <string.h>

#include "sort.h"

static inline void toLower(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if ('A' < str[i] && str[i] < 'Z') str[i] = str[i] - ('A' - 'a');
	}
}

static int compare_names(const void *file_1, const void *file_2) {
	const char* name_1 = ((FileInfo *)file_1)->name;
	const char* name_2 = ((FileInfo *)file_2)->name;

	name_t adj_name_1; strcpy(adj_name_1, name_1); toLower(adj_name_1);
	name_t adj_name_2; strcpy(adj_name_2, name_2); toLower(adj_name_2);

	return strcmp(adj_name_1, adj_name_2);
}

void sortFiles(FileInfo *arr, const int *arr_count) {
	qsort(arr, *arr_count, sizeof(FileInfo), compare_names);
}
