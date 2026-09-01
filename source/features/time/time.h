/// @file features/time/time.h

#ifndef TIME_INITIALISED
#define TIME_INITIALISED

#include "model/stat-model.h"
#include "model/new-stat-model.h"

TimeInfo *parseTime(TimeInfo *const timeobj, const time_t file_time);

#endif /* !TIME_INITIALISED */
