/// @file options/options.h

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "../model/stat-model.h"

void usage(const int exit_code);
int setOptions(const int argc, const char *argv[]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

SortByField SORT_BY (void);

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
