/// @file info/sorting/sort-files.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "info/info.h"
#include "utils/strings.h"
#include "options/options.h"
#include "features/mode/mode.h"
#include "debugging.h"

/// The multiplier which will be applied to a sort if the `--reverse-sort` option is enabled.
static int REVERSE;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SORT_FILES_BY(field) qsort(arr, *arr_count, sizeof(FileInfo), (compare_ ## field ## s))

/* ——————————————————————————————————————————————— */

/// Get the specified `field` from either file_1 or file_2.
#define GET_ATTR(n, field) (((const FileInfo *)file_ ## n)->field)

/// For all numerical fields, we can find out whether one if above or below another by subtracting boolean values.
#define GET_ORDERING(field) ( \
		(GET_ATTR(1, field) > GET_ATTR(2, field)) -	\
		(GET_ATTR(1, field) < GET_ATTR(2, field))	\
	)

/// Make sure that `.` is always the first file sorted - no matter what.
#define CHECK_DOTDIR_SORT(name_1, name_2) \
	do { \
		if (strcmp(name_1, DOTDIR) == 0) return -1; \
		if (strcmp(name_2, DOTDIR) == 0) return  1; \
	} while (0)

/// Define a function that can be passed into `qsort` by the `SORT_FILES_BY` macro.
#define DEFINE_COMPARE_FUNCTION(field) \
	static inline int compare_ ## field ## s(const void *file_1, const void *file_2) { \
		CHECK_DOTDIR_SORT(GET_ATTR(1, name), GET_ATTR(2, name));\
		\
		const int result = GET_ORDERING(field) * REVERSE;		\
		if (result != 0) return result;							\
		\
		/* in the case of a tie, sort the files by name */		\
		return compare_names(file_1, file_2);					\
	}
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IS_DIGIT(chr) ('0' <= (chr) && (chr) <= '9')

/* ——————————————————————————————————————————————— */

// Note: I know this function's name goes against convention, but I'm doing some macro magic ot make this all easier,
//	so it's been done for a reason (see the `SORT_FILES_BY` macro)
static inline int compare_names(const void *file_1, const void *file_2) {
	const char 
		*name_1 = GET_ATTR(1, name),
		*name_2 = GET_ATTR(2, name);

	CHECK_DOTDIR_SORT(name_1, name_2);

	name_t adj_name_1, adj_name_2;
	toLower(adj_name_1, name_1);
	toLower(adj_name_2, name_2);

	typedef char intbuf_t[32];

	int i = 0, j = 0;
	while (adj_name_1[i] != '\0' && adj_name_2[j] != '\0') {
		// make sure dotfiles always sort above non-dotfiles
		if (adj_name_1[i] != adj_name_2[j]) {
			if (adj_name_1[i] == '.') return -1 * REVERSE;
			if (adj_name_2[j] == '.') return  1 * REVERSE;
		}

		if (IS_DIGIT(adj_name_1[i]) && IS_DIGIT(adj_name_2[j])) {
			intbuf_t int_buf_1, int_buf_2;
			/// The running length of each int buffer.
			int len_1 = 0, len_2 = 0;

			// iterate through the characters, consuming them (i++) as you pass a digit
			while (IS_DIGIT(adj_name_1[i])) { int_buf_1[len_1++] = adj_name_1[i++]; }
			while (IS_DIGIT(adj_name_2[j])) { int_buf_2[len_2++] = adj_name_2[j++]; }

			int_buf_1[len_1] = '\0',
			int_buf_2[len_2] = '\0';

			// now that both int buffers contain strings of purely digits, convert them to integers
			const int // NOLINT(*-err34-c)
				num_1 = atoi(int_buf_1),
				num_2 = atoi(int_buf_2);

			// if the numbers are different from each other, then compare them normally
			if (num_1 != num_2) {
				return (num_1 < num_2 ? -1 : 1) * REVERSE;
			}

		} else { // if either character is a non-digit, just return them in their regular ascii sorting order
			if (adj_name_1[i] != adj_name_2[j]) {
				return (adj_name_1[i] < adj_name_2[j] ? -1 : 1) * REVERSE;
			}
			i++; j++;
		}
	}

	if (adj_name_1[i] == '\0' && adj_name_2[j] == '\0') return 0;
	return (adj_name_1[i] == '\0' ? -1 : 1) * REVERSE;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int compare_modes(const void *file_1, const void *file_2) {
	CHECK_DOTDIR_SORT(GET_ATTR(1, name), GET_ATTR(2, name));

	const mode_t
		mode_1 = GET_ATTR(1, mode) & PERM_MASK,
		mode_2 = GET_ATTR(2, mode) & PERM_MASK;

	const int result = (
		(mode_1 > mode_2) -
		(mode_1 < mode_2)
	) * REVERSE;

	if (result != 0) return result;
	return compare_names(file_1, file_2);
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

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void sortFiles(FileInfo arr[], const int *arr_count) {
	/// The multiplier which will be applied to a sort if the `--reverse-sort` option is enabled.
	REVERSE = DO_REVERSE_SORT() ? -1 : 1;

	switch (SORT_BY()) {

		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wimplicit-fallthrough"

		case SB_DEFAULT:
		case SB_NAME : SORT_FILES_BY(name)	; return; // custom function

		#pragma clang diagnostic pop

		case SB_MODE : SORT_FILES_BY(mode)	; return; // custom function
		case SB_SIZE : SORT_FILES_BY(size)	; return;
		case SB_TIME : SORT_FILES_BY(time)	; return;
		case SB_INODE: SORT_FILES_BY(inode)	; return;
		case SB_DEVNO: SORT_FILES_BY(dev_no); return;
		case SB_UID  : SORT_FILES_BY(uid)	; return;
		case SB_GID  : SORT_FILES_BY(gid)	; return;
		case SB_NLINK: SORT_FILES_BY(nlink)	; return;
		case SB_FLAGS: SORT_FILES_BY(flags)	; return;

		case SB_NONE : ;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
