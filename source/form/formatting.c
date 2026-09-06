/// @file form/formatting.c

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define FMT_left "-"
#define FMT_right ""

#define GET_FMT_S(fmt, lor) "%" FMT_##lor	  #fmt
#define GET_FMT_L(fmt, lor) "%" FMT_##lor "*" #fmt
#define GET_FMT_P(fmt, lor) GET_FMT_L(fmt, lor) "%ls"

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

// these are just here to ease the conversion between different naming conventions
#define st_inum	st_ino
#define st_dev_no st_dev

#define GET_LEN(...) ((size_t)snprintf(NULL, 0, __VA_ARGS__))
#define SET_LEN(field) if (do_##field()) setLen(FI_##field, GET_LEN(fields[FI_##field].fmt_s, pfile->s->st_##field));

// called from `parseFile()`
inline void checkLengths(const FileStat *const pfile, const bool do_basic) {
	// these are the only two fields (which we need to find the lengths of) which don't come from `stat`,
	//	which is why their signatures are slightly different to the rest
	if (do_basic) {
		if (do_inum()) setLen(FI_inum, GET_LEN(fields[FI_inum].fmt_s, pfile->inum));
		if (do_mode()) setLen(FI_mode, GET_LEN(fields[FI_mode].fmt_s, pfile->mode));
		return;
	}

	if (do_dev_no()) {
		setLen(FI_dev_no, DO_DEVNO_MAJMIN()
			? GET_LEN("%d,%d", major(pfile->s->st_dev), minor(pfile->s->st_dev))
			: GET_LEN(fields[FI_inum].fmt_s, pfile->s->st_dev)
		);
	}

	SET_LEN(flags);
	SET_LEN(gid);
	SET_LEN(uid);
	SET_LEN(nlink);
	SET_LEN(size);

	if (do_time()) {
		SET_LEN(atime);
		SET_LEN(mtime);
		SET_LEN(ctime);
		SET_LEN(btime);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DEFAULT_LEN -1

#define CALCULATE_LEN(field)			(do_##field()	  * (getLen(FI_##field)			 + padlen))
#define CALCULATE_LEN_TIME(field)		(do_time_t(field) * (getLen(timeField(field))	 + padlen))
#define CALCULATE_LEN_TIMESTR(field)	(do_time_t(field) * (getLen(timeFieldStr(field)) + padlen))

static int total_len = DEFAULT_LEN;

// yes this is awful - i don't care
int getTotalLen(void) {
	if (total_len != DEFAULT_LEN) return total_len;

	const int padlen = (sizeof(FIELD_PAD) / sizeof(FIELD_PAD[0])) - 1;

	return (total_len = (int)(
		(getLen(FI_xat_acl)) +

		CALCULATE_LEN(inum	) + CALCULATE_LEN(dev_no  ) +
		CALCULATE_LEN(nlink	) +
		CALCULATE_LEN(mode	) + CALCULATE_LEN(mode_str) +
		CALCULATE_LEN(size	) + CALCULATE_LEN(size_str) +
		CALCULATE_LEN(uid	) + CALCULATE_LEN(usr_name) +
		CALCULATE_LEN(gid	) + CALCULATE_LEN(grp_name) +
		CALCULATE_LEN(flags	) + CALCULATE_LEN(flag_str) +

		(do_time()) * (
			CALCULATE_LEN_TIME(A_TIME) +
			CALCULATE_LEN_TIME(M_TIME) +
			CALCULATE_LEN_TIME(C_TIME) +
			CALCULATE_LEN_TIME(B_TIME)
		) +

		(do_time_str()) * (
			CALCULATE_LEN_TIMESTR(A_TIME) +
			CALCULATE_LEN_TIMESTR(M_TIME) +
			CALCULATE_LEN_TIMESTR(C_TIME) +
			CALCULATE_LEN_TIMESTR(B_TIME)
		)
	));
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
