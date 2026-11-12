/// @file features/time/time.c

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "time.h"
#include "debugging.h"
#include "form/formatting.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Constants ———————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SECS_IN_1MIN  60
#define MINS_IN_HOUR  60
#define HOURS_IN_DAY  24
#define DAYS_IN_WEEK   7
#define DAYS_IN_YEAR 366

#define SECS 1
#define MINS (SECS * SECS_IN_1MIN) /** Number of seconds in 1 minute.	*/
#define HOUR (MINS * MINS_IN_HOUR) /** Number of seconds in 1 hour.		*/
#define DAYS (HOUR * HOURS_IN_DAY) /** Number of seconds in 1 day.		*/
#define WEEK (DAYS * DAYS_IN_WEEK) /** Number of seconds in 1 week.		*/
#define YEAR (DAYS * DAYS_IN_YEAR) /** Number of seconds in 1 year.		*/

/* —— Function-Like Macros ————————————————————————————————————————————————————————————————————————————————————————— */

/// Convert a numerical day of the week from the Sunday=0 format to the Monday=0 format.
#define SUN_TO_MON(day) \
	((((day) - 1) + DAYS_IN_WEEK) % DAYS_IN_WEEK)

/// Test if a specified `tm_##field` of the current time and the file's time are equal.
#define TIMES_EQ(field) \
	((curr_tm.tm_##field) == (file_tm->tm_##field))

/* —————————————————————————————————————————————————————————————— */

/// Set the file's time string to the error string, and return early.
#define RETURN_ZERO(col) do {									\
	memcpy(time_info->str, TIME_ERR_STR, sizeof(TIME_ERR_STR));	\
	time_info->colour = (col);									\
	\
	*bytes_written = sizeof(TIME_ERR_STR) - 1;					\
	return time_info;											\
} while (0)

/* —————————————————————————————————————————————————————————————— */

/// Set the date & time strings, the string's colour, and the length of the datetime string.
#define SET_DT(col, size, ...) do {	\
	time_info->colour = (col);		\
	*bytes_written = (size);		\
	__VA_OPT__((__VA_ARGS__);)		\
} while (0)

// u = unit, t = text, c = colour
#define SET_TIME_RELA(u, t, c) SET_DT(c, snprintf(time_info->str, sizeof(timestr), ( "%ld " t ), (long)(t_diff/(u))	))
#define SET_DATE_TEXT(	 t, c) SET_DT(c, strftime(time_info->str, sizeof(timestr), (t TIME_FMT), file_tm			))
#define SET_TIME_TEXT(	 t, c) SET_DT(c, (sizeof(t) - 1), strncpy(time_info->str , (t), sizeof(timestr)				))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Static Runtime Constants ————————————————————————————————————————————————————————————————————————————————————— */

// Note: all of these values are constant after they are set by `initTime()`.

static time_t diff_midn		; /** Number of seconds since midnight. */
static time_t diff_month	; /** Number of seconds since midnight on the 1ˢᵗ of the month. */
static time_t diff_year		; /** Number of seconds since midnight on the 1ˢᵗ of January this year. */
static time_t curr_time_secs; /** Number of seconds since midnight on the 1ˢᵗ of January 1970. */

static struct tm curr_tm	; /** A copy of the `struct tm` object referencing the current time. */

/* —— initTime() ——————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool initTime(void) {
	static bool time_initialised  = false;
	static bool time_init_success = false;

	// if the we've already initialised the time, then simlpy return whether it was a success or not.
	if (time_initialised) return time_init_success;
	time_initialised = true;

	/* ——————————————————————————————————— */

	curr_time_secs = time(NULL);
	if (curr_time_secs == -1) return ( time_init_success = false );

	const struct tm *const current_tm_obj = localtime(&curr_time_secs);
	if (current_tm_obj == NULL) return ( time_init_success = false );

	// `localtime` uses the same static memory on every call,
	//	so we have to create a local copy of the struct if we want to reuse it
	curr_tm = *current_tm_obj;

	/* ——————————————————————————————————— */

	diff_midn = (
		curr_tm.tm_hour * HOUR +
		curr_tm.tm_min	* MINS +
		curr_tm.tm_sec	* SECS
	);

	diff_month	= diff_midn + (curr_tm.tm_mday - 1) * DAYS;
	diff_year	= diff_midn + (curr_tm.tm_yday - 1) * DAYS;

	return ( time_init_success = true );
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— parseTime() —————————————————————————————————————————————————————————————————————————————————————————————————— */

TimeInfo *parseTime(TimeInfo *const time_info, const time_t file_time_secs, size_t *const bytes_written) {
	if (file_time_secs == 0) RETURN_ZERO(TC_EPOCH); // a short circuit for if the file's time is 0
	// initialise the current time, seconds since midnight, etc.
	if (!initTime()) RETURN_ZERO(TC_ERROR); // if it fails (or has failed), then return an error

	const time_t t_diff = (curr_time_secs - file_time_secs); /** How many seconds ago the file was modified. */
	const struct tm *const file_tm = localtime(&file_time_secs);

	*bytes_written = 0;

	if		(t_diff < -2 * SECS)			SET_DATE_TEXT(DATE_FMT		 , TC_FUTURE	); // future	  (243 139 168)

	else if	(t_diff <  5 * SECS)			SET_TIME_TEXT("Now"			 , TC_NOW		); // now		  (203 210 242)

	else if	(t_diff <  1 * MINS)			SET_TIME_RELA(SECS,"secs"	 , TC_MIN		); // secs		  (200 208 241)
	else if	(t_diff <  2 * MINS)			SET_TIME_TEXT("1 " "min. ago", TC_MIN		); // mins (1)	  (200 208 241)
	else if	(t_diff < 11 * MINS)			SET_TIME_RELA(MINS,"mins ago", TC_MIN		); // mins		  (200 208 241)

	else if	(false)							SET_DATE_TEXT("Today"		 , TC_THIS_HR	); // this hour
	else if	(false)							SET_DATE_TEXT("Today"		 , TC_LAST_HR	); // last hour

	else if	(t_diff < diff_midn			  )	SET_DATE_TEXT("Today"		 , TC_TODAY		); // today		  (165 183 236)
	else if	(t_diff < diff_midn + 1 * DAYS)	SET_DATE_TEXT("Yesterday"	 , TC_YESTD		); // yesterday	  (133 161 228)
	else if	(t_diff < diff_midn + 2 * DAYS)	SET_DATE_TEXT("2 Days Ago"	 , TC_2DAYS		); // day before  (100 145 225)

	else if	(false)							SET_DATE_TEXT(DATE_FMT		 , TC_THIS_WK	); // this week
	else if	(false)							SET_DATE_TEXT(DATE_FMT		 , TC_LAST_WK	); // last week

	else if	(t_diff < diff_month)			SET_DATE_TEXT(DATE_FMT		 , TC_THIS_MO	); // this month  ( 70 132 230)
	else if	(false)							SET_DATE_TEXT(DATE_FMT		 , TC_LAST_MO	); // last month

	else if	(t_diff < diff_year	)			SET_DATE_TEXT(DATE_FMT		 , TC_THIS_YR	); // this year	  ( 35 106 204)
	else if	(false)							SET_DATE_TEXT(DATE_FMT		 , TC_LAST_YR	); // last year

	else									SET_DATE_TEXT(DATE_FMT		 , TC_OLDER		); // older		  (  4  65 145)

	// check that the various datetime-setting macros above, actually returned a valid string
	if ((int)*bytes_written <= 0 || *bytes_written >= sizeof(timestr)) RETURN_ZERO(TC_ERROR);
	return time_info;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— print_time_raw() ————————————————————————————————————————————————————————————————————————————————————————————— */

void print_time_raw(const FileStat *const pFS, const TimeType type) {
	if (pFS->s == NULL) {
		printf("%s" "%*c" "%ls", getcol(PUNCT), getLen(timeField(type)), '-', FIELD_PAD);
		return;
	}

	const time_t times[TT_COUNT] = {
		[A_TIME] = pFS->s->st_atime, [M_TIME] = pFS->s->st_mtime,
		[C_TIME] = pFS->s->st_ctime, [B_TIME] = pFS->s->st_btime,
	};

	printf("%s" "%*ld" "%ls",
		getcol(time_colour_esc[pFS->f->times[type]->colour]),
		getLen(timeField(type)), times[type],
		FIELD_PAD
	);
}

/* —— print_time_str() —————————————————————————————————————————— */

void print_time_str(const FileStat *const pFS, const TimeType type) {
	if (pFS->f == NULL || pFS->f->times[type] == NULL) {
		printf("%s" "%*s" "%ls", getcol(PUNCT), getLen(timeFieldStr(type)), TIME_ERR_STR, FIELD_PAD);
		return;
	}

	printf("%s" "%*s" "%ls",
		getcol(time_colour_esc[pFS->f->times[type]->colour]),
		getLen(timeFieldStr(type)), pFS->f->times[type]->str,
		FIELD_PAD
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:word midn
