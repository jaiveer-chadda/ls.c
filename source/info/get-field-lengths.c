/// @file info/get-field-lengths.c

#include <stdio.h>
#include <string.h>

#include "info.h"
#include "form/formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_IGNORE_UNIT(unit) ((unit) == UNIT_BYTE || (unit) == UNIT_ZERO || (unit) == UNIT_MAJ_MIN)
#define GET_SIZE_FMT() (file.rdev == 0 ? fmt_strs_short.size : fmt_strs_short.majmin)

/* ———————————————————————————————————————————————————————————————————————— */

/// A macro that gets the maximum lengths of (most) fields, with a few exceptions.
#define GET_LEN(field)													\
	if (do_ ## field()) {												\
		sprintf(elem_as_str, (fmt_strs_short.field), (file.field));		\
		len = strlen(elem_as_str);										\
		if (len > (field_lengths.field)) (field_lengths.field) = len;	\
	}

/* ———————————————————————————————————————————————————————————————————————— */

// `mode_str` is an exception cos of the fact that it might have xattr/acl markers
#define GET_MODESTR_LEN()												\
	if (do_mode_str()) {												\
		sprintf(elem_as_str, fmt_strs_short.mode_str, file.mode_str);	\
		len = strlen(elem_as_str)										\
			+ (file.has_xattr	? 1 : 0)								\
			+ (file.has_acl		? 1 : 0);								\
		if (len > field_lengths.mode_str) field_lengths.mode_str = len;	\
	}

// `size` is an exception since it could be either a regular size, or a majmin size
#define GET_SIZE_LEN()											\
	if (do_size()) {											\
		sprintf(elem_as_str, GET_SIZE_FMT(), file.size);		\
		len = strlen(elem_as_str);								\
		if (len > field_lengths.size) field_lengths.size = len;	\
	}

// same as above, except, additionally, `size_str`s under 1kb don't print units
#define GET_SIZESTR_LEN()														\
	if (do_size_str()) {														\
		sprintf(elem_as_str, fmt_strs_short.size_str, file.size_str);			\
		len = strlen(elem_as_str) + (DO_IGNORE_UNIT(file.size_unit) ? 0 : 1);	\
		if (len > field_lengths.size_str) field_lengths.size_str = len;			\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

inline void getFieldLengths(const FileInfo *all_files, const int *count) {
	size_t len;
	// No field (except the name & link) should ever be loonger than 64 chars.
	char elem_as_str[64];

	// TODO: change this so that length is calculated when the elements are first created (at least for the strings)
	// run through all the files' fields and calculate their maximum lengths
	for (int i = 0; i < *count; i++) {
		const FileInfo file = all_files[i];

		GET_LEN(nlink);
		GET_LEN(inode);	GET_LEN(dev_no);
		GET_LEN(flags);	GET_LEN(flag_str);
		GET_LEN(mode);	GET_MODESTR_LEN();
		GET_SIZE_LEN();	GET_SIZESTR_LEN();
		GET_LEN(uid);	GET_LEN(usr_name);
		GET_LEN(gid);	GET_LEN(grp_name);
		GET_LEN(time);	GET_LEN(time_str);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
