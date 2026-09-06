/// @file options/options.h

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "model/stat-model.h"

bool doColourAuto(void);
void usage(const int exit_code);
int setOptions(const int argc, char *argv[]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NSF '\0' /// No short flag.
#define MAX_OPT_FLAG_LEN 20 /// The maximum length that an option's long flag can be (exc. `--`, but including `\0`).
#define MAX_OPT_FLAG_NUM 3 /// The maximum number of long flags that an option can have.

#define BINARY_OPTIONS_TABLE \
	/*│ Name			│default│ is	│short │ long flags								   │*/ \
	/*│					│ value	│ field	│ flag │										   │*/ \
	X(DO_PATH			, false	, false	, NSF, { "path"			, "full-path"				}) \
	X(DO_CLEAR			, false	, false	, 'c', { "clear"									}) \
	X(DO_HEADER			, false	, false	, 'H', { "header"		, "headers"					}) \
	X(DO_DIVIDERS		, true	, false	, '_', { "divider"		, "dividers"				}) \
	X(DO_MOUNTDEV		, true	, false	, 'M', { "mount"		, "mounts"					}) \
	X(DIRS_AS_FILES		, false	, false	, 'd', { "dirs-as-files", "no-recurse-dirs"			}) \
	X(DO_DIM_HIDDEN		, true	, false	, '.', { "dim-hidden"	, "dim"						}) \
	X(DO_DEVNO_MAJMIN	, true	, false	, NSF, { "devno-majmin"	, "majmin-devno"			}) \
	X(DO_REVERSE_SORT	, false	, false	, 'r', { "reverse"		, "rev"						}) \
	X(SORT_DIRS_FIRST	, true	, false	, 'D', { "dirs-first"	, "sort-dirs-first"			}) \
	\
	X(do_icon			, true	, true	, 'I', { "icon"			, "icons"					}) \
	X(do_suffix			, true	, true	, 'P', { "suffix"		, "mark-type"				}) \
	X(do_link_to	/**/, false	, true	, 'L', { "link-to"		, "symlinks"				}) \
	X(do_nlink			, true	, true	, 'n', { "nlink"									}) \
	X(do_dev_no		/**/, true	, true	, NSF, { "dev-no"		, "device-number"			}) \
	X(do_inum		/**/, true	, true	, 'i', { "inode"		, "ino"			, "inum"	}) \
	X(do_flags		/**/, true	, true	, NSF, { "flags"									}) \
	X(do_flag_str		, true	, true	, NSF, { "flag-str"		, "flags-str"				}) \
	X(do_mode		/**/, true	, true	, NSF, { "mode"										}) \
	X(do_mode_str		, true	, true	, NSF, { "mode-str"									}) \
	X(do_size		/**/, true	, true	, NSF, { "size"										}) \
	X(do_size_str		, true	, true	, NSF, { "size-str"									}) \
	X(do_uid		/**/, true	, true	, 'u', { "uid"										}) \
	X(do_usr_name		, true	, true	, 'U', { "uid-str"		, "usr-name"	, "user"	}) \
	X(do_gid		/**/, true	, true	, 'g', { "gid"										}) \
	X(do_grp_name		, true	, true	, 'G', { "gid-str"		, "grp-name"	, "group"	}) \
	\
	X(do_time		/**/, true	, true	, NSF, { "time"										}) \
	X(do_time_str		, true	, true	, NSF, { "time-str"									}) \
	\
	X(do_atime			, false	, true	, NSF, { "atime"									}) \
	X(do_mtime			, true	, true	, NSF, { "mtime"									}) \
	X(do_ctime			, false	, true	, NSF, { "ctime"									}) \
	X(do_btime			, false	, true	, NSF, { "btime"									}) \
/**/

#define X(name, ...) BO_ ## name,
typedef enum { BINARY_OPTIONS_TABLE BINOPT_COUNT } BinOptIdx;
#undef X

typedef struct {
	bool value;
	bool is_field;
	char short_flag;
	char long_flags[MAX_OPT_FLAG_NUM][MAX_OPT_FLAG_LEN];
} BinaryOption;

typedef char CLIFlag_t[MAX_OPT_FLAG_LEN + sizeof("--do-")];

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define MAX_DEPTH O__DEPTH()

/* —————————————————————————————————————————————————————————————— */

SortByField SORT_BY (void);
uint8_t O__DEPTH	(void);
bool DO_COLOUR		(void);
bool DO_TINY_FLAGS	(void);
bool DO_SHORT_FLAGS	(void);

bool do_time_t(TimeType type);

#define X(name, ...) bool name(void);
BINARY_OPTIONS_TABLE
#undef X

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !OPTIONS_INITIALIASED */
