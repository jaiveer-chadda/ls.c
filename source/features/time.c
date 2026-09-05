/// @file features/time/time.c

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "time.h"
#include "debugging.h"
#include "form/formatting.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define SEC    1
#define MIN   60
#define HOUR (60 * MIN)
#define DAY  (24 * HOUR)

#define SET_DATE_TEXT(text) *b_writ = strftime(timeobj->str, sizeof(timestr), (text TIME_FMT), pTime)
#define SET_TIME_TEXT(text)	*b_writ = sizeof(text); strncpy(timeobj->str, (text), sizeof(timestr))

#define SET_TIME_RELA(unit, text) \
	*b_writ = snprintf(timeobj->str, sizeof(timestr), ("%ld " text), (long)(t_diff/(unit))) /* always round down */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool time_initialised = false;

time_t current_time;
time_t diff_midn;	/// Number of seconds since midnight.
time_t diff_month;	/// Number of seconds since midnight on the 1ˢᵗ of the month.
time_t diff_year;	/// Number of seconds since midnight on the 1ˢᵗ of January this year.

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void initTime(void) {
	time_initialised = true;

	current_time = time(NULL);
	const struct tm *time_tm = localtime(&current_time);

	diff_midn =
		time_tm->tm_hour * HOUR +
		time_tm->tm_min  * MIN +
		time_tm->tm_sec;

	diff_month	= diff_midn + (time_tm->tm_mday - 1) * DAY;
	diff_year	= diff_midn + (time_tm->tm_yday - 1) * DAY;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

TimeInfo *parseTime(TimeInfo *const timeobj, const time_t file_time, size_t *const b_writ) {
	if (!time_initialised) initTime();

	if (file_time == 0) {
		debug(WARNING, "parseTime: %s", strerror(errno));
		memcpy(timeobj->str, TIME_ERR_STR, sizeof(TIME_ERR_STR));
		*b_writ = sizeof(TIME_ERR_STR);

		return timeobj;
	}

	/// How many seconds ago the file was modified.
	const time_t t_diff = current_time - file_time;
	const struct tm *pTime = localtime(&file_time);

	*b_writ = 0; // bytes written

	if		(t_diff <  5 * SEC)				{ SET_TIME_TEXT("Now"			); timeobj->colour = TC_NOW		; }
	else if	(t_diff <  1 * MIN)				{ SET_TIME_RELA(SEC, "secs"		); timeobj->colour = TC_MIN		; }

	else if	(t_diff <  2 * MIN)				{ SET_TIME_TEXT("1 " "min. ago"	); timeobj->colour = TC_MIN		; }
	else if	(t_diff < 11 * MIN)				{ SET_TIME_RELA(MIN, "mins ago"	); timeobj->colour = TC_MIN		; }

	else if	(t_diff < diff_midn			 )	{ SET_DATE_TEXT("Today"			); timeobj->colour = TC_TODAY	; }
	else if	(t_diff < diff_midn + 1 * DAY)	{ SET_DATE_TEXT("Yesterday"		); timeobj->colour = TC_YESTD	; }
	else if	(t_diff < diff_midn + 2 * DAY)	{ SET_DATE_TEXT("2 Days Ago"	); timeobj->colour = TC_2DAYS	; }

	else if	(t_diff < diff_month)			{ SET_DATE_TEXT(DATE_FMT		); timeobj->colour = TC_THIS_MO	; }
	else if	(t_diff < diff_year	)			{ SET_DATE_TEXT(DATE_FMT		); timeobj->colour = TC_THIS_YR	; }
	else									{ SET_DATE_TEXT(DATE_FMT		); timeobj->colour = TC_OTHER	; }

	if ((int)*b_writ == -1 || *b_writ >= sizeof(timestr)) {
		debug(WARNING, "parseTime: %s", strerror(errno));
		memcpy(timeobj->str, TIME_ERR_STR, sizeof(TIME_ERR_STR));
		*b_writ = sizeof(TIME_ERR_STR);
	}

	return timeobj;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_time_raw(const FileStat *const pFS, const TimeType type) {
	const bool valid = pFS->s != NULL;
	const time_t times[TT_COUNT] = {
		[A_TIME] = pFS->s->st_atime,
		[M_TIME] = pFS->s->st_mtime,
		[C_TIME] = pFS->s->st_ctime,
		[B_TIME] = pFS->s->st_btime,
	};

	printf(
		fields[timeField(type)].fmt_p,
		getLen(timeField(type)),
		valid ? times[type] : 0,
		FIELD_PAD
	);
}

void print_time_str(const FileStat *const pFS, const TimeType type) {
	if (pFS->f != NULL && pFS->f->times[type] != NULL) {
		printf("%s" "%*s" "%s",
			getcol(time_colour_esc[pFS->f->times[type]->colour]),
			getLen(timeFieldStr(type)), pFS->f->times[type]->str,
			FIELD_PAD
		);
		return;
	}

	printf("%*s" "%s", getLen(timeFieldStr(type)), TIME_ERR_STR, FIELD_PAD);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:word midn
