/// @file features/time/time.c

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "time.h"
#include "debugging.h"
#include "form/formatting.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Constants ———————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef enum DayOTWeek {
	DOTW_SUN, DOTW_MON, DOTW_TUE, DOTW_WED, DOTW_THU, DOTW_FRI, DOTW_SAT,
	DAYS_IN_WEEK
} DayOTWeek;

/// @todo implement an option to control the `FIRST_DAY_OTW` constant
static const DayOTWeek FIRST_DAY_OTW = DOTW_MON;

#define SECS_IN_1MIN 60
#define MINS_IN_HOUR 60
#define HOURS_IN_DAY 24

#define SECS 1
#define MINS (SECS_IN_1MIN * SECS) /** Number of seconds in 1 minute.	*/
#define HOUR (MINS_IN_HOUR * MINS) /** Number of seconds in 1 hour.		*/
#define DAYS (HOURS_IN_DAY * HOUR) /** Number of seconds in 1 day.		*/
#define WEEK (DAYS_IN_WEEK * DAYS) /** Number of seconds in 1 week.		*/

/* —— Conversion Macros ———————————————————————————————————————————————————————————————————————————————————————————— */

/// Convert a numerical day of the week from the `Sunday = 0` format to a `FIRST_DAY_OTW = 0` format.
#define DAY_OF_THE_WEEK(day) \
	((((day) - FIRST_DAY_OTW) + DAYS_IN_WEEK) % DAYS_IN_WEEK)

#define GET_TIME_FMT() ( \
	(t_diff < diff_midn + 0 * DAYS)	? TODAY_FMT		 :	\
	(t_diff < diff_midn + 1 * DAYS)	? YESTERDAY_FMT	 :	\
	(t_diff < diff_midn + 2 * DAYS)	? DAY_BEFORE_FMT :	\
	/**/							  DATETIME_FMT		\
)

/* —— Relative Time Checking ———————————————————————————————————— */

/// Test if a specified `tm_##field` of the current time and the file's time are equal.
#define TIMES_EQ(field) \
	((curr_tm.tm_##field) == (file_tm->tm_##field))

/* —————————————————————————————————————————————————————————————— */

#define FILE_TIME_IS_THIS_HOUR() ( \
	TIMES_EQ(year) && \
	TIMES_EQ(yday) && \
	TIMES_EQ(hour)	  \
)

#define FILE_TIME_IS_PREV_HOUR() (			 \
	file_tm->tm_year == prev_hour.tm_year && \
	file_tm->tm_yday == prev_hour.tm_yday && \
	file_tm->tm_hour == prev_hour.tm_hour	 \
)

/* —————————————————————————————————————————————————————————————— */

#define FILE_TIME_IS_THIS_WEEK() (this_week_secs <= file_time_secs && file_time_secs < next_week_secs)
#define FILE_TIME_IS_LAST_WEEK() (last_week_secs <= file_time_secs && file_time_secs < this_week_secs)

/* —————————————————————————————————————————————————————————————— */

#define FILE_TIME_IS_LAST_MONTH() (				\
	file_tm->tm_year == prev_month.tm_year &&	\
	file_tm->tm_mon	 == prev_month.tm_mon		\
)

#define FILE_TIME_IS_LAST_YEAR() (file_tm->tm_year == curr_tm.tm_year - 1)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Function-Like Macros ————————————————————————————————————————————————————————————————————————————————————————— */

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
#define SET_RELATIVE(u,	t, c) SET_DT(c, snprintf(time_info->str, sizeof(timestr), ( "%ld " t ), (long)(t_diff/(u))	))
#define SET_DATETIME(	t, c) SET_DT(c, strftime(time_info->str, sizeof(timestr), (t), file_tm						))
#define SET_TIME_TXT(	t, c) SET_DT(c, (sizeof(t) - 1), strncpy(time_info->str , (t), sizeof(timestr)				))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Static Runtime Constants ————————————————————————————————————————————————————————————————————————————————————— */

// Note: all of these values are constant after they are set by `initTime()`.

static time_t diff_midn		; /** Number of seconds since midnight. */
static time_t diff_month	; /** Number of seconds since midnight on the 1ˢᵗ of the month. */
static time_t diff_year		; /** Number of seconds since midnight on the 1ˢᵗ of January this year. */
static time_t curr_time_secs; /** Number of seconds since midnight on the 1ˢᵗ of January 1970. */

static time_t this_week_secs; /** Number of seconds since the epoch that this week began. */
static time_t last_week_secs; /** Number of seconds since the epoch that last week began. */
static time_t next_week_secs; /** Number of seconds since the epoch that next week will begin. */

static struct tm curr_tm	; /** A `struct tm` object representing the current time. */
static struct tm prev_hour	; /** A `struct tm` object representing the time one hour ago. */
static struct tm prev_month	; /** A `struct tm` object representing the time one month ago. */

/* —— initTime() ——————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool initTime(void) {
	static bool time_initialised  = false;
	static bool time_init_success = false;

	// if the we've already initialised the time, then simlpy return whether it was a success or not.
	if (time_initialised) return time_init_success;
	time_initialised = true;

	/* —————————————————————————————————————————————————————————————————————— */

	curr_time_secs = time(NULL);
	if (curr_time_secs == -1l) return ( time_init_success = false );

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

	diff_month = diff_midn + (curr_tm.tm_mday - 1) * DAYS; // `mday` is 1-indexed, so needs to be adjusted
	diff_year  = diff_midn +  curr_tm.tm_yday	   * DAYS;

	/* —————————————————————————————————————————————————————————————————————— */

	// copy the current time object
	prev_hour = curr_tm;

	prev_hour.tm_hour -=  1; // then decrement the hour,
	prev_hour.tm_min   =  0; // and reset all fields < an hour to 0
	prev_hour.tm_sec   =  0; //	 so `mktime` can set them itself
	prev_hour.tm_isdst = -1; // also let `mktime` determine daylight savings

	// then fill in all the fields we reset
	//	if it fails, set everything to 0, which should make any comparison fail
	if (mktime(&prev_hour) == -1l) memset(&prev_hour, 0, sizeof(struct tm));

	/* ——————————————————————————————————— */

	prev_month = curr_tm;

	// decrement the month as before
	// but we also need to set `tm_mday` to 1, to prevent issues with month boundaries, e.g., for the 31ˢᵗ of march:
	// - `prev_month.tm_mon` becomes february
	// - `prev_month.tm_mday` stays 31
	// - the 31ˢᵗ of feb doesn't exist, so `mktime()` converts this to the 2ⁿᵈ or 3ʳᵈ of march
	// therefore, it would conclude that march is the previous month
	// if we set the day of the month to 1, then it'll calculate the difference correctly
	prev_month.tm_mon -= 1;
	prev_month.tm_mday = 1;
	prev_month.tm_hour = 0, prev_month.tm_min = 0, prev_month.tm_sec = 0, prev_month.tm_isdst = -1;

	if (mktime(&prev_month) == -1l) memset(&prev_month, 0, sizeof(struct tm));

	/* ——————————————————————————————————— */

	// calculate the start of this week (FIRST_DAY_OTW at 00:00)
	struct tm this_wk_start = curr_tm;

	// find the start of the week based on whichever date is defined as `FIRST_DAY_OTW`
	this_wk_start.tm_mday -= DAY_OF_THE_WEEK(this_wk_start.tm_wday);
	// reset all less significant times, as above
	this_wk_start.tm_hour = 0, this_wk_start.tm_min = 0, this_wk_start.tm_sec = 0, this_wk_start.tm_isdst = -1;

	// calculate the start of next week and last week
	struct tm next_wk_start = this_wk_start, last_wk_start = this_wk_start;
	next_wk_start.tm_isdst = last_wk_start.tm_isdst = -1;

	// add / subtract a week from next / last week
	next_wk_start.tm_mday += DAYS_IN_WEEK;
	last_wk_start.tm_mday -= DAYS_IN_WEEK;

	// convert this week, next week, and last week into seconds
	this_week_secs = mktime(&this_wk_start);
	next_week_secs = mktime(&next_wk_start);
	last_week_secs = mktime(&last_wk_start);

	/* —————————————————————————————————————————————————————————————————————— */

	return ( time_init_success = true );
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— parseTime() —————————————————————————————————————————————————————————————————————————————————————————————————— */

TimeInfo *parseTime(TimeInfo *const time_info, const time_t file_time_secs, size_t *const bytes_written) {
	if (file_time_secs == -1) RETURN_ZERO(TC_ERROR); // a short circuit for if there was an error in getting the time
	if (file_time_secs ==  0) RETURN_ZERO(TC_EPOCH); // a short circuit for if the file's time is 0
	if (!initTime())		  RETURN_ZERO(TC_ERROR); // if time initialisation fails (or has failed), return an error

	const time_t t_diff = (curr_time_secs - file_time_secs); /** How many seconds ago the file was modified. */
	const struct tm *const file_tm = localtime(&file_time_secs);

	*bytes_written = 0;

	if		(t_diff < -2 * SECS)			SET_DATETIME(DATETIME_FMT	, TC_FUTURE	 ); // future		- \e[31m
	else if	(t_diff <  5 * SECS)			SET_TIME_TXT("Now"			, TC_NOW	 ); // now			- \e[97m
	else if	(t_diff <  1 * MINS)			SET_RELATIVE(SECS,"secs"	, TC_SEC	 ); // secs			- (230 235 254)
	else if	(t_diff <  2 * MINS)			SET_TIME_TXT("1 " "min. ago", TC_MIN	 ); // mins (1)		- (212 218 250)
	else if	(t_diff < 11 * MINS)			SET_RELATIVE(MINS,"mins ago", TC_MIN	 ); // mins			- (212 218 250)

	else if	(FILE_TIME_IS_THIS_HOUR())		SET_DATETIME(TODAY_FMT		, TC_THIS_HR ); // this hour	- (194 202 245)
	else if	(FILE_TIME_IS_PREV_HOUR())		SET_DATETIME(GET_TIME_FMT()	, TC_LAST_HR ); // last hour	- (184 194 243)
	else if	(t_diff < diff_midn			  )	SET_DATETIME(TODAY_FMT		, TC_TODAY	 ); // today		- (166 179 238)
	else if	(t_diff < diff_midn + 1 * DAYS)	SET_DATETIME(YESTERDAY_FMT	, TC_YESTD	 ); // yesterday	- (150 164 232)
	else if	(t_diff < diff_midn + 2 * DAYS)	SET_DATETIME(DAY_BEFORE_FMT , TC_2DAYS	 ); // 2 days ago	- (140 155 230)

	else if	(FILE_TIME_IS_THIS_WEEK())		SET_DATETIME(DATETIME_FMT	, TC_THIS_WK ); // this week	- (124 142 224)
	else if	(FILE_TIME_IS_LAST_WEEK())		SET_DATETIME(DATETIME_FMT	, TC_LAST_WK ); // last week	- (106 127 219)
	else if	(t_diff < diff_month)			SET_DATETIME(DATETIME_FMT	, TC_THIS_MO ); // this month	- ( 90 113 214)
	else if	(FILE_TIME_IS_LAST_MONTH())		SET_DATETIME(DATETIME_FMT	, TC_LAST_MO ); // last month	- ( 67  99 214)
	else if	(t_diff < diff_year)			SET_DATETIME(DATETIME_FMT	, TC_THIS_YR ); // this year	- ( 43  84 216)
	else if	(FILE_TIME_IS_LAST_YEAR())		SET_DATETIME(DATETIME_FMT	, TC_LAST_YR ); // last year	- ( 18  68 185)
	else									SET_DATETIME(DATETIME_FMT	, TC_OLDER	 ); // older		- (  8  48 128)

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
