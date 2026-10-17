/// @file info/sorting/sort-files.c

#include "sort.h"
#include "malloc.h"
#include "strings.h"

#include "options/options.h"
#include "features/features.h"

/// The multiplier which will be applied to a sort if the `--reverse-sort` option is enabled.
static int8_t REVERSE = 0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define FILE_1_FIRST -1
#define FILE_2_FIRST  1

#define ARR_ELEM_SIZE ((depth == 0) ? sizeof(FileStat*) : sizeof(FileStat))

#define SORT_FILES_BY(field) \
	qsort_r(arr, arr_count, ARR_ELEM_SIZE, (void*)&depth, (compare_ ## field ## s)); \

/* ——————————————————————————————————————————————————————————————————— */

#define	 AS_P_FILESTAT(f)	((const FileStat *const		  )(f))
#define	AS_PP_FILESTAT(f) (*((const FileStat *const *const)(f)))

#define AS_PFS(f) AS_P_FILESTAT((*((uint8_t*)depth) == 0) ? AS_PP_FILESTAT(f) : (f))

#define IS_DIR(n) \
	isFSDir(AS_PFS(file_ ## n))

/// Get the specified `field` from either file_1 or file_2.
#define GET_ATTR(n, field) \
	(AS_PFS(file_ ## n)->field)

#define SORT_1_FIRST_IF(condition) \
	(((condition) ? FILE_1_FIRST : FILE_2_FIRST) * REVERSE)

/// For all numerical fields, we can find out whether one is above or below another by subtracting boolean values.
#define GET_ORDERING(field) (( \
		(GET_ATTR(1, field) > GET_ATTR(2, field)) -	\
		(GET_ATTR(1, field) < GET_ATTR(2, field))	\
	) * REVERSE)

#define CHECK_DIRS() \
	if (SORT_DIRS_FIRST()) {															\
		const bool f1_dir = IS_DIR(1), f2_dir = IS_DIR(2);								\
		/* if one file is a directory and the other isn't, sort the directory first */	\
		/*	note: we don't reverse the ordering of this sort - dirs are always first */	\
		if ( f1_dir && !f2_dir) return FILE_1_FIRST;									\
		if (!f1_dir &&  f2_dir) return FILE_2_FIRST;									\
	}

#define CHECK_VALID_STAT() do {											\
	const bool f1_nul = GET_ATTR(1,s) == NULL;							\
	const bool f2_nul = GET_ATTR(2,s) == NULL;							\
	if (f1_nul || f2_nul) return (f1_nul > f2_nul) - (f1_nul < f2_nul);	\
} while (0)

/* ——————————————————————————————————————————————————————————————————— */

#define QSORT_PROTOTYPE(funcname) \
	static inline int compare_ ## funcname ## s(void *depth, const void *file_1, const void *file_2)

/// Define a function that can be passed into `qsort_r` (by the `SORT_FILES_BY` macro).
#define DEFINE_COMPARE_FUNCTION(field)														\
	QSORT_PROTOTYPE(field) {																\
		/* firstly, check that `FileStat::s` isn't `NULL`. if it is, then return early */	\
		CHECK_VALID_STAT();																	\
		/* then, if we have to sort dirs first, check whether one of them is a dir */		\
		CHECK_DIRS();																		\
		const int8_t result = GET_ORDERING(s->st_##field);									\
		/* in the case of a tie, sort the files by name */									\
		return result ? result : compare_names(depth, file_1, file_2);						\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IS_DIGIT(chr) ('0' <= (chr) && (chr) <= '9')

/* ——————————————————————————————————————————————————————————————————— */

QSORT_PROTOTYPE(name) {
	CHECK_DIRS(); // check for dir sorting

	const char *name_1 = GET_ATTR(1, name), *name_2 = GET_ATTR(2, name);
	name_t lname_1, lname_2;

	if (!SORT_CASE_SENSIT()) {
		toLower(lname_1, name_1), toLower(lname_2, name_2);
		name_1 = lname_1, name_2 = lname_2;
	}

	namlen_t i = 0, j = 0;
	while (name_1[i] != '\0' && name_2[j] != '\0') {
		// make sure dotfiles always sort above non-dotfiles
		if (name_1[i] != name_2[j]) {
			if (name_1[i] == '.') return FILE_1_FIRST * REVERSE;
			if (name_2[j] == '.') return FILE_2_FIRST * REVERSE;
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
			if (num_1 != num_2) return SORT_1_FIRST_IF(num_1 < num_2);

			// if the numbers are equal, keep checking

		// if either character is a non-digit, return them in their regular ascii sorting order
		} else if (name_1[i] != name_2[j]) {
			return SORT_1_FIRST_IF(name_1[i] < name_2[j]);

		// if both characters are the same, move onto the next character
		} else i++, j++;
	}

	// if one of the names is a prefix of the other, sort the shorter name first
	return SORT_1_FIRST_IF(name_1[i] == '\0');
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int compare_modes_or_types(void *depth, const void *file_1, const void *file_2, const uint16_t mask) {
	CHECK_DIRS();

	const mode_t // get rid of the type info, and keep just the permissions
		mode_1 = (GET_ATTR(1, mode) & mask),
		mode_2 = (GET_ATTR(2, mode) & mask);

	const int result = (
		(mode_1 > mode_2) -
		(mode_1 < mode_2)
	) * REVERSE;

	// in the case of a tie, sort the files by name
	return result ? result : compare_names(depth, file_1, file_2);
}

QSORT_PROTOTYPE(mode) { return compare_modes_or_types(depth, file_1, file_2, PERM_MASK); }
QSORT_PROTOTYPE(type) { return compare_modes_or_types(depth, file_1, file_2, TYPE_MASK); }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

QSORT_PROTOTYPE(inode) {
	CHECK_DIRS();

	const int8_t result = GET_ORDERING(inum);
	return result ? result : compare_names(depth, file_1, file_2);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

DEFINE_COMPARE_FUNCTION(size )
DEFINE_COMPARE_FUNCTION(dev	 )
DEFINE_COMPARE_FUNCTION(uid	 )
DEFINE_COMPARE_FUNCTION(gid	 )
DEFINE_COMPARE_FUNCTION(nlink)
DEFINE_COMPARE_FUNCTION(flags)
DEFINE_COMPARE_FUNCTION(mtime) /** @todo make this work for other times too */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void sortFiles(const uint8_t depth, void *const arr, const int arr_count) {
	/// The multiplier which will be applied to a sort if the `--reverse-sort` option is enabled.
	if (REVERSE == 0) REVERSE = DO_REVERSE_SORT() ? -1 : 1;

	/* —————————————————————————————————————————————————— */

	/* Note re: the `arr` parameter
	 * ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
	 * When receiving the `arr` parameter, there are two types of arrays that we could get:
	 *
	 *	1. in most cases (when `depth != 0`), the array will be `FileStat *arr`
	 *		- in this case, we don't have to do anything special - just sort the files as usual and return
	 *
	 *	2. if, however, we're sorting command line inputs (`depth == 0`), the array will be `FileStat **arr`
	 *		- (i.e., an array of pointers to `FileStat`s)
	 *		- in this case, we need to convert `FileStat **arr` into `FileStat *arr`
	 *			- this is done by the `AS_PFS` / `AS_PP_FILESTAT` macros
	 */

	/* —————————————————————————————————————————————————— */

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

	switch (SORT_BY()) {
		case SB_DEFAULT	: /* sort by name by default */
		#if __STDC_VERSION__ >= 202300L
			[[fallthrough]];
		#endif
		case SB_NAME	: SORT_FILES_BY(name ); break;
		case SB_MODE	: SORT_FILES_BY(mode ); break;
		case SB_TYPE	: SORT_FILES_BY(type ); break;
		case SB_INODE	: SORT_FILES_BY(inode); break;

		case SB_SIZE	: SORT_FILES_BY(size ); break;
		case SB_DEVNO	: SORT_FILES_BY(dev	 ); break;
		case SB_UID		: SORT_FILES_BY(uid	 ); break;
		case SB_GID		: SORT_FILES_BY(gid	 ); break;
		case SB_NLINK	: SORT_FILES_BY(nlink); break;
		case SB_FLAGS	: SORT_FILES_BY(flags); break;
		case SB_TIME	: SORT_FILES_BY(mtime); break; // note: not fully implemented

		case SB_NONE	: return; // if we're not sorting this file, then we're not sorting any of its children either
	}

	#pragma GCC diagnostic pop

	/* —————————————————————————————————————————————————— */

	// this is a special case, since the decision to sort inputs is taken seperately to whether to sort children
	if (depth == 0) return;
	if (depth >= MAX_DEPTH) return;

	// recursively sort this file's children
	for (int i = 0; i < arr_count; i++) SORT_CHILDREN((FileStat*)(arr) + i, depth + 1);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
