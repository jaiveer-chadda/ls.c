/// @file info/sorting/sort-files.c

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "strings.h"

#include "options/options.h"
#include "features/features.h"

/// The multiplier which will be applied to a sort if the `--reverse-sort` option is enabled.
static int8_t REVERSE;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SORT_FILES_BY(field) \
	qsort(arr, *arr_count, sizeof(FileStat), (compare_ ## field ## s))

/* ——————————————————————————————————————————————————————————————————— */

#define IS_DIR(n) S_ISDIR(GET_ATTR(n, mode))

/// Get the specified `field` from either file_1 or file_2.
#define GET_ATTR(n, field) \
	(((const FileStat *const)file_ ## n)->field)

/// For all numerical fields, we can find out whether one if above or below another by subtracting boolean values.
#define GET_ORDERING(field) ( \
		(GET_ATTR(1, field) > GET_ATTR(2, field)) -	\
		(GET_ATTR(1, field) < GET_ATTR(2, field))	\
	)

/* ——————————————————————————————————————————————————————————————————— */

/// Define a function that can be passed into `qsort` (by the `SORT_FILES_BY` macro).
#define DEFINE_COMPARE_FUNCTION(funcname, field) \
	static inline int compare_ ## funcname ## s(const void *file_1, const void *file_2) {	\
		if (SORT_DIRS_FIRST()) {															\
			/* if one file is a directory and the other isn't, sort the directory first */	\
			/*	note: we don't reverse the ordering of this sort - dirs are always first */	\
			if (IS_DIR(1) && !IS_DIR(2)) return -1;											\
			if (IS_DIR(2) && !IS_DIR(1)) return	 1;											\
		}																					\
		const int8_t result = GET_ORDERING(field) * REVERSE;								\
		/**/																				\
		/* in the case of a tie, sort the files by name */									\
		return result != 0 ? result : compare_names(file_1, file_2);						\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IS_DIGIT(chr) ('0' <= (chr) && (chr) <= '9')
#define xor !=

/* ——————————————————————————————————————————————————————————————————— */

// Note: I know this function's name goes against convention, but I'm doing some macro magic ot make this all easier,
//	so it's been done for a reason (see the `SORT_FILES_BY` macro)
static inline int compare_names(const void *file_1, const void *file_2) {
	if (SORT_DIRS_FIRST()) {
		if (IS_DIR(1) && !IS_DIR(2)) return -1;
		if (IS_DIR(2) && !IS_DIR(1)) return	 1;
	}

	const char *const inp_name_1 = GET_ATTR(1, name);
	const char *const inp_name_2 = GET_ATTR(2, name);

	/// @todo implement an option to turn case-sensitivity on/off
	name_t name_1, name_2;
	toLower(name_1, inp_name_1);
	toLower(name_2, inp_name_2);

	namlen_t i = 0, j = 0;
	while (name_1[i] != '\0' && name_2[j] != '\0') {
		// make sure dotfiles always sort above non-dotfiles
		if (name_1[i] != name_2[j]) {
			if (name_1[i] == '.') return -1 * REVERSE;
			if (name_2[j] == '.') return  1 * REVERSE;
		}

		// if both characters are digits
		if (IS_DIGIT(name_1[i]) && IS_DIGIT(name_2[j])) {
			char buf_1[32], buf_2[32];
			int	 len_1 = 0, len_2 = 0;

			// iterate through the characters, consuming them ([ij]++) as you pass a digit
			while (IS_DIGIT(name_1[i])) buf_1[len_1++] = name_1[i++];
			while (IS_DIGIT(name_2[j])) buf_2[len_2++] = name_2[j++];
			// by now, both buffers should have a string containing the entire number that begins at this index

			// null termination is needed for `atoi`
			buf_1[len_1] = '\0', buf_2[len_2] = '\0';

			// now that both int buffers contain strings of purely digits, convert them to integers
			//	I would usually use `strtol` instead of `atoi`, but since I know for sure that the strings will only
			//	contain digits, this should be fine
			const int // NOLINT(*-err34-c)
				num_1 = atoi(buf_1),
				num_2 = atoi(buf_2);

			// if the numbers differ, compare them, and sort the smaller one first
			if (num_1 != num_2) return (num_1 < num_2 ? -1 : 1) * REVERSE;

			// if the numbers are equal, keep checking

		// if either character is a non-digit, return them in their regular ascii sorting order
		} else if (name_1[i] != name_2[j]) {
			return (name_1[i] < name_2[j] ? -1 : 1) * REVERSE;

		// if both characters are the same, then move onto the next character
		} else i++; j++;
	}

	// we should have reached the end of one of the strings, but not both
	assert((name_1[i] != '\0') xor (name_2[j] != '\0'));
	// if one of the names is a prefix of the other, sort the shorter name first
	return (name_1[i] == '\0' ? -1 : 1) * REVERSE;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int compare_modes(const void *file_1, const void *file_2) {
	const mode_t // get rid of the type info, and keep just the permissions
		mode_1 = GET_ATTR(1, mode) & PERM_MASK,
		mode_2 = GET_ATTR(2, mode) & PERM_MASK;

	const int result = (
		(mode_1 > mode_2) -
		(mode_1 < mode_2)
	) * REVERSE;

	if (result != 0) return result;
	// if the modes are the same, sort by name as backup
	return compare_names(file_1, file_2);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// @todo add checks for if `file->s == NULL`
DEFINE_COMPARE_FUNCTION(inode, inum			)
DEFINE_COMPARE_FUNCTION(size , s->st_size	)
DEFINE_COMPARE_FUNCTION(devno, s->st_dev	)
DEFINE_COMPARE_FUNCTION(uid	 , s->st_uid	)
DEFINE_COMPARE_FUNCTION(gid	 , s->st_gid	)
DEFINE_COMPARE_FUNCTION(nlink, s->st_nlink	)
DEFINE_COMPARE_FUNCTION(flags, s->st_flags	)
DEFINE_COMPARE_FUNCTION(time , s->st_mtime	) /** @todo make this work for other times too */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void sortFiles(FileStat arr[], const int *const arr_count) {
	/// The multiplier which will be applied to a sort if the `--reverse-sort` option is enabled.
	REVERSE = DO_REVERSE_SORT() ? -1 : 1;

	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wimplicit-fallthrough"

	switch (SORT_BY()) {
		case SB_DEFAULT	: /* sort by name by default*/
		case SB_NAME	: SORT_FILES_BY(name ); return;
		case SB_MODE	: SORT_FILES_BY(mode ); return;
		case SB_SIZE	: SORT_FILES_BY(size ); return;
		case SB_INODE	: SORT_FILES_BY(inode); return;
		case SB_DEVNO	: SORT_FILES_BY(devno); return;
		case SB_UID		: SORT_FILES_BY(uid	 ); return;
		case SB_GID		: SORT_FILES_BY(gid	 ); return;
		case SB_NLINK	: SORT_FILES_BY(nlink); return;
		case SB_FLAGS	: SORT_FILES_BY(flags); return;
		case SB_TIME	: SORT_FILES_BY(time ); return; // note: not fully implemented
		case SB_NONE	: ;
	}

	#pragma clang diagnostic pop
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
