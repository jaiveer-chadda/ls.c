/// @file options/options.h

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "model/stat-model.h"

void usage(const int exit_code);
bool doColourAuto(void);
int setOptions(const int argc, const char *argv[]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NSF 0 /// No short flag.
#define MAX_OPT_FLAG_LEN 20
#define MAX_OPT_FLAG_NUM 3

#define BINARY_OPTIONS_TABLE \
	/* when set here, column 2 (↓) marks the default value of each option */\
	X(BO_DO_CLEAR			, false	, false	, 'c', { "clear"									}) \
	X(BO_DO_HEADER			, false	, false	, 'H', { "header"		, "headers"					}) \
	X(BO_DO_DIVIDERS		, true	, false	, '_', { "divider"		, "dividers"				}) \
	X(BO_DO_MOUNTDEV		, true	, false	, 'M', { "mount"		, "mounts"					}) \
	X(BO_DO_DIM_HIDDEN		, true	, false	, '.', { "dim-hidden"	, "dim"						}) \
	X(BO_DIRS_AS_FILES		, false	, false	, 'd', { "dirs-as-files", "treat-dirs-as-files"		}) \
	X(BO_SORT_DIRS_FIRST	, true	, false	, 'D', { "dirs-first"	, "sort-dirs-first"			}) \
	X(BO_DO_REVERSE_SORT	, false	, false	, 'r', { "reverse"		, "rev"						}) \
	\
	X(BO_do_icon			, true	, true	, 'I', { "icon"			, "icons"					}) \
	X(BO_do_suffix			, true	, true	, 'P', { "suffix"		, "mark-type"				}) \
	X(BO_do_link_to			, true	, true	, 'l', { "link-to"		, "symlinks"				}) \
	X(BO_do_nlink			, true	, true	, 'n', { "nlink"									}) \
	X(BO_do_dev_no			, false	, true	, NSF, { "dev-no"		, "device-number"			}) \
	X(BO_do_inum			, false	, true	, 'i', { "inode"		, "ino"			, "inum"	}) \
	X(BO_do_flags			, false	, true	, NSF, { "flags"									}) \
	X(BO_do_flag_str		, true	, true	, NSF, { "flag-str"		, "flags-str"				}) \
	X(BO_do_mode			, false	, true	, NSF, { "mode"										}) \
	X(BO_do_mode_str		, true	, true	, NSF, { "mode-str"									}) \
	X(BO_do_size			, false	, true	, NSF, { "size"										}) \
	X(BO_do_size_str		, true	, true	, NSF, { "size-str"									}) \
	X(BO_do_uid				, false	, true	, 'u', { "uid"										}) \
	X(BO_do_usr_name		, true	, true	, 'U', { "uid-str"		, "usr-name"	, "user"	}) \
	X(BO_do_gid				, false	, true	, 'g', { "gid"										}) \
	X(BO_do_grp_name		, true	, true	, 'G', { "gid-str"		, "grp-name"	, "group"	}) \
	X(BO_do_time			, false	, true	, NSF, { "time"										}) \
	X(BO_do_time_str		, true	, true	, NSF, { "time-str"									}) \
	\
	X(BO_do_atime			, false	, true	, NSF, { "atime"									}) \
	X(BO_do_mtime			, true	, true	, NSF, { "mtime"									}) \
	X(BO_do_ctime			, false	, true	, NSF, { "ctime"									}) \
	X(BO_do_btime			, false	, true	, NSF, { "btime"									})

#define X(name, ...) name,
typedef enum { BINARY_OPTIONS_TABLE BINOPT_COUNT } BinOptIdx;
#undef X

typedef struct {
	bool value;
	bool is_field;
	char short_flag;
	char long_flags[MAX_OPT_FLAG_NUM][MAX_OPT_FLAG_LEN];
} BinaryOption;

typedef char test_flag_t[MAX_OPT_FLAG_LEN + 5];

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define MAX_DEPTH O__DEPTH()

/* —————————————————————————————————————————————————————————————— */

SortByField SORT_BY (void);
uint8_t O__DEPTH	(void);
bool DO_REVERSE_SORT(void);
bool DO_COLOUR		(void);
bool DO_TINY_FLAGS	(void);
bool DO_SHORT_FLAGS	(void);

bool DO_CLEAR		(void);
bool DO_HEADER		(void);
bool DO_DIVIDERS	(void);
bool DO_MOUNTDEV	(void);
bool DO_DIM_HIDDEN	(void);
bool DIRS_AS_FILES	(void);
bool SORT_DIRS_FIRST(void);

/* —————————————————————————————————————————————————————————————— */

bool do_suffix	(void);		bool do_icon(void);
bool do_link_to	(void);

bool do_nlink	(void);
bool do_dev_no	(void);
bool do_inum	(void);

bool do_flags	(void);		bool do_flag_str(void);
bool do_mode	(void);		bool do_mode_str(void);
bool do_size	(void);		bool do_size_str(void);
bool do_uid		(void);		bool do_usr_name(void);
bool do_gid		(void);		bool do_grp_name(void);
bool do_time	(void);		bool do_time_str(void);

bool do_time_t(TimeType type);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !OPTIONS_INITIALIASED */
