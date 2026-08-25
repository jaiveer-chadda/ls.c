/// @file model/types.h

#ifndef TYPES_INITIALIASED
#define TYPES_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>
#include <sys/stat.h>

#include "consts.h"

/* ——————————————————————————————————————————————————— */

typedef char*link_t;
typedef char suff_t; /** Can be one of: `/`, `@`, `*`, `=`, `|`, `%` */
typedef char unit_t;
typedef char name_t[MAX_NAME_LEN];
typedef char path_t[MAX_PATH_LEN];
typedef wchar_t icon_t;
typedef unsigned int flag_t;

typedef char modestr[MODE_STR_LEN];
typedef char timestr[MAX_TIME_LEN];
typedef char ugidstr[MAX_UGID_LEN];
typedef char sizestr[MAX_SIZE_LEN];
typedef char flagstr[(MAX_FLAG_LEN + 1) * MAX_FLAG_NUM]; // +1 for the comma that can come after each flag

/* ——————————————————————————————————————————————————— */

typedef enum {
	SB_DEFAULT,
	SB_NONE,

	SB_NAME,
	SB_SIZE,
	SB_TIME,
	SB_INODE,
	SB_DEVNO,
	SB_UID,
	SB_GID,
	SB_NLINK,
	SB_FLAGS,
	SB_MODE,
} SortByField;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !TYPES_INITIALIASED */
