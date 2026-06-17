/// @file sorting/sort-files.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#define IS_UPPER(chr) ('A' <= chr && chr <= 'Z')
#define IS_DIGIT(chr) ('0' <= chr && chr <= '9')

static inline void toLower(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if IS_UPPER(str[i]) str[i] -= ('A' - 'a');
	}
}

static inline int compareNames(const void *file_1, const void *file_2) {
	const char* name_1 = ((FileInfo *)file_1)->name;
	const char* name_2 = ((FileInfo *)file_2)->name;

	name_t adj_name_1; strcpy(adj_name_1, name_1); toLower(adj_name_1);
	name_t adj_name_2; strcpy(adj_name_2, name_2); toLower(adj_name_2);

	int  i = 0, j = 0;
	int  len_1, len_2;
	long num_1, num_2;

	while (adj_name_1[i] != '\0' && adj_name_2[j] != '\0') {
		if (IS_DIGIT(adj_name_1[i]) && IS_DIGIT(adj_name_2[j])) {
			char int_buf_1[32], int_buf_2[32];
			len_1 = 0, len_2 = 0;

			while IS_DIGIT(adj_name_1[i]) int_buf_1[len_1++] = adj_name_1[i++];
			while IS_DIGIT(adj_name_2[j]) int_buf_2[len_2++] = adj_name_2[j++];

			int_buf_1[len_1] = '\0';
			int_buf_2[len_2] = '\0';

			num_1 = strtol(int_buf_1, NULL, 10);
			num_2 = strtol(int_buf_2, NULL, 10);

			if (num_1 != num_2) return num_1 < num_2 ? -1 : 1;

			continue;
		}

		// if neither characters are digits, just return their regular sorts
		if (adj_name_1[i] != adj_name_2[j]) return adj_name_1[i] < adj_name_2[j] ? -1 : 1;
		i++; j++;
	}

	if (adj_name_1[i] == '\0' && adj_name_2[j] == '\0') return 0;
	return adj_name_1[i] == '\0' ? -1 : 1;
}

void sortFiles(FileInfo arr[], const int *arr_count) {
	qsort(arr, *arr_count, sizeof(FileInfo), compareNames);
}
