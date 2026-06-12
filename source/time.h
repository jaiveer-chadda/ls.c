/// @file time.h

#ifndef MAX_TIME_LEN

#include <time.h>
#define MAX_TIME_LEN 1 << 5

void parseTime(const time_t time, char time_str[MAX_TIME_LEN]);

#endif /* !MAX_TIME_LEN */
