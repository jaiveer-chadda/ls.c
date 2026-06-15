/// @file features/time/time.h

#include <stdio.h>
#include <string.h>

#include "../../model/stat-model.h"

#include "time.h"

#define DATE_FMT "%a %e %b %y"
#define TIME_FMT "  %R"
#define TIME_ERR_STR "-"

#define MIN  60
#define HOUR 60 * MIN
#define DAY  24 * HOUR

static time_t current_time;
static time_t diff_midn;	/// Number of seconds since midnight.

void initTime(void) {
	current_time = time(NULL);
	const struct tm *cur_time_tm = localtime(&current_time);

	diff_midn =
		(cur_time_tm->tm_hour * HOUR) +
		(cur_time_tm->tm_min  * MIN)  +
		(cur_time_tm->tm_sec);
}

void parseTime(char time_str[MAX_TIME_LEN], const time_t file_time) {
	/// How many seconds ago the file was modified.
	const time_t t_diff = current_time - file_time;
	const struct tm *pTime = localtime(&file_time);

	size_t b_writ = -1;	// (bytes written)

	if		(t_diff <	  MIN) strcpy(time_str, "Now");
	else if	(t_diff < 2 * MIN) strcpy(time_str, "1 min. ago");
	else if	(t_diff < 3 * MIN) strcpy(time_str, "2 mins ago");
	else if	(t_diff < 4 * MIN) strcpy(time_str, "3 mins ago");
	else if	(t_diff < diff_midn			) b_writ = strftime(time_str, MAX_TIME_LEN, "Today"		TIME_FMT, pTime);
	else if	(t_diff < diff_midn +	DAY	) b_writ = strftime(time_str, MAX_TIME_LEN, "Yesterday"	TIME_FMT, pTime);
	else if	(t_diff < diff_midn + 2*DAY	) b_writ = strftime(time_str, MAX_TIME_LEN, "2 Days Ago"TIME_FMT, pTime);
	else								  b_writ = strftime(time_str, MAX_TIME_LEN, DATE_FMT	TIME_FMT, pTime);

	if (!b_writ) strcpy(time_str, TIME_ERR_STR);
}

#undef MIN
#undef HOUR
#undef DAY

// spell:word midn
