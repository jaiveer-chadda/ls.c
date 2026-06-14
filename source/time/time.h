/// @file time.h

#ifndef TIME_H_INITIALISED
#define TIME_H_INITIALISED

#include <time.h>

void initTime(void);
void parseTime(char time_str[MAX_TIME_LEN], const time_t file_time);

#endif /* !TIME_H_INITIALISED */
