/// @file features/time/time.h

#ifndef TIME_INITIALISED
#define TIME_INITIALISED

#include "model/stat-model.h"

TimeInfo *parseTime(TimeInfo *const timeobj, const time_t file_time, size_t *const b_writ);

#endif /* !TIME_INITIALISED */
