/// @file time.h

#include <stdio.h>
#include <string.h>

#include "../model/stat-model.h"
#include "time.h"

#define TIME_FMT "%a %e %b %y  %R"
#define TIME_ERR_STR "-"

void parseTime(const time_t time, char time_str[MAX_TIME_LEN]) {
	const struct tm *pTime = localtime(&time);

	size_t bytes_written = strftime(time_str, MAX_TIME_LEN, TIME_FMT, pTime);
	if (!bytes_written) strcpy(time_str, TIME_ERR_STR);
}
