/// @file model/types.h

#ifndef TYPES_INITIALIASED
#define TYPES_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <stdbool.h>
#include <sys/stat.h>

#include "consts.h"

/* ——————————————————————————————————————————————————— */

typedef char type_t;
typedef char name_t[MAX_NAME_LEN];
typedef char path_t[MAX_PATH_LEN];
typedef unsigned int flag_t;

typedef char modestr[MODE_STR_LEN];
typedef char timestr[MAX_TIME_LEN];
typedef char ugidstr[MAX_UGID_LEN];
typedef char sizestr[MAX_SIZE_LEN];
typedef char flagstr[MAX_FLAG_LEN * MAX_FLAG_NUM];

/* ——————————————————————————————————————————————————— */

typedef enum {
	SB_DEFAULT,
	SB_NONE,

	SB_NAME,
	SB_SIZE,
	SB_TIME,
	SB_INUM,
	SB_USER,
	SB_GROUP,
} SortByField;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !TYPES_INITIALIASED */
