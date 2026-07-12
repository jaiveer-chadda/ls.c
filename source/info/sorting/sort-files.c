/// @file info/sorting/sort-files.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "../info.h"
#include "../../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SORT_FILES_BY(field) qsort(arr, *arr_count, sizeof(FileInfo), (compare_##field##s))

/* ——————————————————————————————————————————————— */

#define GET_ATTR(num, field) (((const FileInfo *)file_##num)->field)
#define GET_ORDERING(field) ((GET_ATTR(1, field) > GET_ATTR(2, field)) - (GET_ATTR(1, field) < GET_ATTR(2, field)))

#define DEFINE_COMPARE_FUNCTION(field) \
	static inline int compare_##field##s(const void *file_1, const void *file_2) {	\
		/* make sure `.` is always the first file sorted - no matter what */		\
		if (strcmp(GET_ATTR(1, name), DOTDIR) == 0) return -1;						\
		if (strcmp(GET_ATTR(2, name), DOTDIR) == 0) return  1;						\
		\
		const int result = GET_ORDERING(field) * (DO_REVERSE_SORT() ? -1 : 1);		\
		if (result != 0) return result;												\
		return compare_names(file_1, file_2); /* names act as the tiebreaker */		\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IS_UPPER(chr) ('A' <= (chr) && (chr) <= 'Z')
#define IS_DIGIT(chr) ('0' <= (chr) && (chr) <= '9')

/* ——————————————————————————————————————————————— */

static inline void toLower(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if IS_UPPER(str[i]) str[i] += ('a' - 'A');
	}
}

static inline int compare_names(const void *file_1, const void *file_2) {
	const char* name_1 = GET_ATTR(1, name);
	const char* name_2 = GET_ATTR(2, name);
	const int  reverse = DO_REVERSE_SORT() ? -1 : 1;

	name_t adj_name_1; strcpy(adj_name_1, name_1); toLower(adj_name_1);
	name_t adj_name_2; strcpy(adj_name_2, name_2); toLower(adj_name_2);

	// make sure `.` is always the first file sorted - no matter what
	if (strcmp(adj_name_1, DOTDIR) == 0) return -1;
	if (strcmp(adj_name_2, DOTDIR) == 0) return  1;

	int i = 0, j = 0;

	while (adj_name_1[i] != '\0' && adj_name_2[j] != '\0') {
		// make sure dotfiles always sort above non-dotfiles
		if (adj_name_1[i] != adj_name_2[j]) {
			if (adj_name_1[i] == '.') return -1 * reverse;
			if (adj_name_2[j] == '.') return  1 * reverse;
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

			if (num_1 != num_2) return (num_1 < num_2 ? -1 : 1) * reverse;

		} else { // if both characters aren't digits, just return their regular, alphabetical sorts
			if (adj_name_1[i] != adj_name_2[j]) return (adj_name_1[i] < adj_name_2[j] ? -1 : 1) * reverse;
			i++; j++;
		}
	}

	if (adj_name_1[i] == '\0' && adj_name_2[j] == '\0') return 0;
	return (adj_name_1[i] == '\0' ? -1 : 1) * reverse;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

DEFINE_COMPARE_FUNCTION(size  )
DEFINE_COMPARE_FUNCTION(time  )
DEFINE_COMPARE_FUNCTION(inode )
DEFINE_COMPARE_FUNCTION(dev_no)
DEFINE_COMPARE_FUNCTION(uid	  )
DEFINE_COMPARE_FUNCTION(gid	  )
DEFINE_COMPARE_FUNCTION(nlink )
DEFINE_COMPARE_FUNCTION(flags )
DEFINE_COMPARE_FUNCTION(mode  )

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void sortFiles(FileInfo arr[], const int *arr_count) {
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wimplicit-fallthrough"
	switch (SORT_BY()) {
		case SB_DEFAULT:
		case SB_NAME : SORT_FILES_BY(name); return;

		case SB_SIZE : SORT_FILES_BY(size)	; return;
		case SB_TIME : SORT_FILES_BY(time)	; return;
		case SB_INODE: SORT_FILES_BY(inode)	; return;
		case SB_DEVNO: SORT_FILES_BY(dev_no); return;
		case SB_UID  : SORT_FILES_BY(uid)	; return;
		case SB_GID  : SORT_FILES_BY(gid)	; return;
		case SB_NLINK: SORT_FILES_BY(nlink)	; return;
		case SB_FLAGS: SORT_FILES_BY(flags)	; return;
		case SB_MODE : SORT_FILES_BY(mode)	; return;

		case SB_NONE : return;
	}
	#pragma clang diagnostic pop
}
