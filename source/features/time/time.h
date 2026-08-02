/// @file features/time/time.h

#ifndef TIME_INITIALISED
#define TIME_INITIALISED

#include <time.h>
#include "model/stat-model.h"

void initTime(void);
void parseTime(timestr time_str, const time_t file_time, TimeColour *time_col);

#endif /* !TIME_INITIALISED */
