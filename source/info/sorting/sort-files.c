/// @file info/sorting/sort-files.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "../../options/options.h"

#define SORT_FILES_BY(field) qsort(arr, *arr_count, sizeof(FileInfo), (compare_##field##s))

#define IS_UPPER(chr) ('A' <= (chr) && (chr) <= 'Z')
#define IS_DIGIT(chr) ('0' <= (chr) && (chr) <= '9')

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void toLower(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if IS_UPPER(str[i]) str[i] += ('a' - 'A');
	}
}

static inline int compare_names(const void *file_1, const void *file_2) {
	const char* name_1 = ((FileInfo *)file_1)->name;
	const char* name_2 = ((FileInfo *)file_2)->name;

	name_t adj_name_1; strcpy(adj_name_1, name_1); toLower(adj_name_1);
	name_t adj_name_2; strcpy(adj_name_2, name_2); toLower(adj_name_2);

	int i = 0, j = 0;

	while (adj_name_1[i] != '\0' && adj_name_2[j] != '\0') {
		// make sure dotfiles always sort above non-dotfiles
		if (adj_name_1[i] != adj_name_2[j]) {
			if (adj_name_1[i] == '.') return -1;
			if (adj_name_2[j] == '.') return  1;
		}

		if (IS_DIGIT(adj_name_1[i]) && IS_DIGIT(adj_name_2[j])) {
			char int_buf_1[32], int_buf_2[32];
			int len_1 = 0, len_2 = 0;

			while (IS_DIGIT(adj_name_1[i])) { int_buf_1[len_1++] = adj_name_1[i++]; }
			while (IS_DIGIT(adj_name_2[j])) { int_buf_2[len_2++] = adj_name_2[j++]; }

			int_buf_1[len_1] = '\0';
			int_buf_2[len_2] = '\0';

			const int num_1 = atoi(int_buf_1);
			const int num_2 = atoi(int_buf_2);

			if (num_1 != num_2) return num_1 < num_2 ? -1 : 1;

		} else { // if both characters aren't digits, just return their regular, alphabetical sorts
			if (adj_name_1[i] != adj_name_2[j]) return adj_name_1[i] < adj_name_2[j] ? -1 : 1;
			i++; j++;
		}
	}

	if (adj_name_1[i] == '\0' && adj_name_2[j] == '\0') return 0;
	return adj_name_1[i] == '\0' ? -1 : 1;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int compare_sizes (const void *file_1, const void *file_2) { return 1; }
static inline int compare_times (const void *file_1, const void *file_2) { return 1; }
static inline int compare_inums (const void *file_1, const void *file_2) { return 1; }
static inline int compare_users (const void *file_1, const void *file_2) { return 1; }
static inline int compare_groups(const void *file_1, const void *file_2) { return 1; }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void sortFiles(FileInfo arr[], const int *arr_count) {
	SORT_FILES_BY(name);

	switch (SORT_BY()) {
		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wimplicit-fallthrough"
		case SB_DEFAULT:
		#pragma clang diagnostic pop
		case SB_NAME : SORT_FILES_BY(name); return;

		case SB_SIZE : SORT_FILES_BY(size) ; return;
		case SB_TIME : SORT_FILES_BY(time) ; return;
		case SB_INUM : SORT_FILES_BY(inum) ; return;
		case SB_USER : SORT_FILES_BY(user) ; return;
		case SB_GROUP: SORT_FILES_BY(group); return;

		case SB_NONE : return;
	}
}
