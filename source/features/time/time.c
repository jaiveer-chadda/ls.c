/// @file features/time/time.h

#include <stdio.h>
#include <string.h>

#include "../../model/stat-model.h"
#include "time.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DATE_FMT "%a %e %b %y"
#define TIME_FMT "  %R"
#define TIME_ERR_STR "-"

#define MIN  60
#define HOUR 60 * MIN
#define DAY  24 * HOUR

#define SET_DATE_TEXT(text) b_writ = strftime(time_str, MAX_TIME_LEN, text TIME_FMT, pTime)
#define SET_TIME_TEXT(text) strcpy(time_str, text)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

time_t current_time;
time_t diff_midn;	/// Number of seconds since midnight.
time_t diff_month;	/// Number of seconds since midnight on the 1ˢᵗ of the month.
time_t diff_year;	/// Number of seconds since midnight on the 1ˢᵗ of January this year.

inline void initTime(void) {
	current_time = time(NULL);
	const struct tm *cur_time_tm = localtime(&current_time);

	diff_midn =
		(cur_time_tm->tm_hour * HOUR) +
		(cur_time_tm->tm_min  * MIN	) +
		(cur_time_tm->tm_sec		);

	diff_month	= diff_midn + ((cur_time_tm->tm_mday - 1) * DAY);
	diff_year	= diff_midn + ((cur_time_tm->tm_yday - 1) * DAY);
}

inline void parseTime(timestr time_str, const time_t file_time, TimeColour *time_col) {
	/// How many seconds ago the file was modified.
	const time_t t_diff = current_time - file_time;
	const struct tm *pTime = localtime(&file_time);

	size_t b_writ = -1;	// (bytes written)

	if		(t_diff <	  MIN)				{ SET_TIME_TEXT("Now"		); *time_col = TC_NOW	 ; }
	else if	(t_diff < 2 * MIN)				{ SET_TIME_TEXT("1 min. ago"); *time_col = TC_MIN	 ; }
	else if	(t_diff < 3 * MIN)				{ SET_TIME_TEXT("2 mins ago"); *time_col = TC_MIN	 ; }
	else if	(t_diff < 4 * MIN)				{ SET_TIME_TEXT("3 mins ago"); *time_col = TC_MIN	 ; }
	else if	(t_diff < diff_midn			 )	{ SET_DATE_TEXT("Today"		); *time_col = TC_TODAY	 ; }
	else if	(t_diff < diff_midn +	  DAY)	{ SET_DATE_TEXT("Yesterday"	); *time_col = TC_YESTD	 ; }
	else if	(t_diff < diff_midn + 2 * DAY)	{ SET_DATE_TEXT("2 Days Ago"); *time_col = TC_2DAYS	 ; }
	else if	(t_diff < diff_month)			{ SET_DATE_TEXT(DATE_FMT	); *time_col = TC_THIS_MO; }
	else if	(t_diff < diff_year	)			{ SET_DATE_TEXT(DATE_FMT	); *time_col = TC_THIS_YR; }
	else								 	{ SET_DATE_TEXT(DATE_FMT	); *time_col = TC_OTHER	 ; }

	if (!b_writ || file_time == 0) strcpy(time_str, TIME_ERR_STR);
}

#undef MIN
#undef HOUR
#undef DAY

// spell:word midn
