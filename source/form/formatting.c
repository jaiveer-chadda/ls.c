/// @file form/formatting.c

#include <stdio.h>
#include <string.h>

#include "formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define FMT_left "-"
#define FMT_right ""

#define GET_FMT_S(fmt, lor) "%" FMT_##lor	  #fmt
#define GET_FMT_L(fmt, lor) "%" FMT_##lor "*" #fmt
#define GET_FMT_P(fmt, lor) GET_FMT_L(fmt, lor) "%s"

/* initialise the array, and set all the elements' lengths to 0 */
#define X(fld, hdr, fmt, lor)			\
	[FI_##fld] = (field_t){				\
		.title = hdr,					\
		.fmt_s = GET_FMT_S(fmt, lor),	\
		.fmt_l = GET_FMT_L(fmt, lor),	\
		.fmt_p = GET_FMT_P(fmt, lor),	\
		.len   = 0						\
	},

field_t fields[FI_COUNT] = { FIELDS_TABLE };
#undef X

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// called from `main()`
inline void initFormatting(void) {
	if (DO_HEADER()) {
		// if we're printing a header, then set all field lengths to the lengths of their header strings
		#define X(fld, hdr, fmt, lor) \
			fields[FI_##fld].len = sizeof(hdr) - 1;

		FIELDS_TABLE
		#undef X
	}
}

// this is honestly just a helper function - I could do the logic inline, but this adds a nice level of abstraction
inline void setLen(const FieldIdx field, const size_t length) {
	// if the inputted length is longer than the current max, replace it
	if (length > fields[field].len) {
		fields[field].len = length;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define st_dev_no st_dev

#define GET_LEN(field, var) ((size_t)snprintf(NULL, 0, fields[field].fmt_s, (var)))
#define SET_LEN(field, cond) if (cond) setLen(FI_##field, GET_LEN(FI_##field, pfile->s->st_##field))

#define CHECK_STAT_LEN(field)		SET_LEN(field, do_ ## field())
#define CHECK_TIME_LEN(field, idx)	SET_LEN(field, do_time_t(idx))

// called from `parseFile()`
void checkLengths(const FileStat *const pfile, const bool do_basic) {
	if (do_basic) {
		if (do_inum()) setLen(FI_inum, GET_LEN(FI_inum, pfile->inum));
		if (do_mode()) setLen(FI_mode, GET_LEN(FI_mode, pfile->mode));
		return;
	}

	CHECK_STAT_LEN(dev_no);
	CHECK_STAT_LEN(flags);
	CHECK_STAT_LEN(gid);
	CHECK_STAT_LEN(uid);
	CHECK_STAT_LEN(nlink);
	CHECK_STAT_LEN(size);

	if (do_time()) {
		CHECK_TIME_LEN(atime, A_TIME);
		CHECK_TIME_LEN(mtime, M_TIME);
		CHECK_TIME_LEN(ctime, C_TIME);
		CHECK_TIME_LEN(btime, B_TIME);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static int total_len = 0;

// yes this is awful - i don't care
int getTotalLen(void) {
	if (total_len != 0) return total_len;

	const int padlen = (int)(sizeof(FIELD_PAD) - 1);

	return (total_len = (int)(
		(getLen(FI_xat)) +
		(getLen(FI_acl)) +

		(do_nlink	() * (getLen(FI_nlink	) + padlen)) +
		(do_dev_no	() * (getLen(FI_dev_no	) + padlen)) +
		(do_inum	() * (getLen(FI_inum	) + padlen)) +
		(do_flags	() * (getLen(FI_flags	) + padlen)) +
		(do_flag_str() * (getLen(FI_flag_str) + padlen)) +
		(do_mode	() * (getLen(FI_mode	) + padlen)) +
		(do_mode_str() * (getLen(FI_mode_str) + padlen)) +
		(do_size	() * (getLen(FI_size	) + padlen)) +
		(do_size_str() * (getLen(FI_size_str) + padlen)) +
		(do_uid		() * (getLen(FI_uid		) + padlen)) +
		(do_usr_name() * (getLen(FI_usr_name) + padlen)) +
		(do_gid		() * (getLen(FI_gid		) + padlen)) +
		(do_grp_name() * (getLen(FI_grp_name) + padlen)) +

		(do_time()) * (
			(do_time_t(A_TIME) * (getLen(FI_atime) + padlen)) +
			(do_time_t(M_TIME) * (getLen(FI_mtime) + padlen)) +
			(do_time_t(C_TIME) * (getLen(FI_ctime) + padlen)) +
			(do_time_t(B_TIME) * (getLen(FI_btime) + padlen))
		) +

		(do_time_str()) * (
			(do_time_t(A_TIME) * (getLen(FI_atime_str) + padlen)) +
			(do_time_t(M_TIME) * (getLen(FI_mtime_str) + padlen)) +
			(do_time_t(C_TIME) * (getLen(FI_ctime_str) + padlen)) +
			(do_time_t(B_TIME) * (getLen(FI_btime_str) + padlen))
		)
	));
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
