/// @file options/options.h

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "../model/stat-model.h"

void usage(const int exit_code);
int setOptions(const int argc, const char *argv[]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NSF 0 /// No short flag.

#define BINARY_OPTIONS_TABLE \
	X(BO_DO_CLEAR		, false	, false	, 'c', { "clear"									}) \
	X(BO_DO_HEADER		, false	, false	, 'H', { "header"		, "headers"					}) \
	X(BO_DO_DIVIDERS	, true	, false	, '_', { "divider"		, "dividers"				}) \
	X(BO_DO_MOUNT_DEV	, true	, false	, 'M', { "mount"		, "mounts"					}) \
	X(BO_DO_DIM_HIDDEN	, true	, false	, '.', { "dim-hidden"	, "dim"						}) \
	X(BO_SORT_DIRS_FIRST, true	, false	, 'D', { "dirs-first"	, "sort-dirs-first"			}) \
	X(BO_DO_REVERSE_SORT, false	, false	, 'r', { "reverse"		, "rev"						}) \
	\
	X(BO_DO_SUFFIX		, true	, true	, 'P', { "suffix"		, "mark-type"				}) \
	X(BO_DO_LINK_TO		, true	, true	, 'l', { "link-to"		, "symlinks"				}) \
	X(BO_DO_NLINK		, true	, true	, 'n', { "nlink"									}) \
	X(BO_DO_DEV_NO		, false	, true	, NSF, { "dev-no"		, "device-number"			}) \
	X(BO_DO_INODE		, false	, true	, 'i', { "inode"		, "ino"			, "inum"	}) \
	X(BO_DO_FLAGS		, false	, true	, NSF, { "flags"									}) \
	X(BO_DO_FLAG_STR	, true	, true	, NSF, { "flag-str"		, "flags-str"				}) \
	X(BO_DO_MODE		, false	, true	, NSF, { "mode"										}) \
	X(BO_DO_MODE_STR	, true	, true	, NSF, { "mode-str"									}) \
	X(BO_DO_SIZE		, false	, true	, NSF, { "size"										}) \
	X(BO_DO_SIZE_STR	, true	, true	, NSF, { "size-str"									}) \
	X(BO_DO_UID			, false	, true	, 'u', { "uid"										}) \
	X(BO_DO_USR_NAME	, true	, true	, 'U', { "uid-str"		, "usr-name"	, "user"	}) \
	X(BO_DO_GID			, false	, true	, 'g', { "gid"										}) \
	X(BO_DO_GRP_NAME	, true	, true	, 'G', { "gid-str"		, "grp-name"	, "group"	}) \
	X(BO_DO_TIME		, false	, true	, NSF, { "time"										}) \
	X(BO_DO_TIME_STR	, true	, true	, NSF, { "time-str"									})

#define X(name, ...) name,
typedef enum { BINARY_OPTIONS_TABLE BO_COUNT } BinOptIdx;
#undef X

typedef struct {
	bool value;
	bool is_field;
	char short_flag;
	char long_flags[3][16];
} BinaryOption;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

SortByField SORT_BY (void);
bool DO_REVERSE_SORT(void);

bool DO_CLEAR		(void);
bool DO_COLOUR		(void);
bool DO_HEADER		(void);
bool DO_DIVIDERS	(void);
bool DO_DIM_HIDDEN	(void);
bool DO_MOUNT_DEV	(void);
bool DO_TINY_FLAGS	(void);
bool DO_SHORT_FLAGS	(void);
bool SORT_DIRS_FIRST(void);

/* —————————————————————————————————————————————————————————————— */

bool do_suffix	(void);
bool do_link_to	(void);

bool do_nlink	(void);
bool do_dev_no	(void);
bool do_inode	(void);

bool do_flags	(void);		bool do_flag_str(void);
bool do_mode	(void);		bool do_mode_str(void);
bool do_size	(void);		bool do_size_str(void);
bool do_uid		(void);		bool do_usr_name(void);
bool do_gid		(void);		bool do_grp_name(void);
bool do_time	(void);		bool do_time_str(void);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !OPTIONS_INITIALIASED */
