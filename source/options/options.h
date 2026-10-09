/// @file options/options.h

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "model/stat-model.h"

bool doColourAuto(void);
void usage(const int exit_code);
int	 setOptions(const int argc, char *const *const argv);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NSF '\0' /** No short flag. */

#define BINARY_OPTIONS_TABLE \
   /*┌──────────────────┬───────┬───────┬───────┬───────────────────────────────────────────┐*/	\
   /*│ option name		│default│ is	│ short	│ long flags								│*/	\
   /*│					│ value	│ field	│ flag	│											│*/	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(DO_PATH			, false	, false	, NSF,	{ "path"			, "full-path"			})	\
	X(DO_CLEAR			, false	, false	, 'c',	{ "clear"									})	\
	X(DO_HEADER			, false	, false	, 'H',	{ "header"			, "headers"				})	\
	X(DO_DOTFILES		, true	, false	, 'A',	{ "all"				, "almost-all"			})	\
	X(DO_DIVIDERS		, true	, false	, '_',	{ "divider"			, "dividers"			})	\
	X(DO_MOUNTDEV		, true	, false	, 'M',	{ "mount"			, "mounts"				})	\
	X(DO_FIRMLINKS		, true	, false	, NSF,	{ "firmlinks"		, "check-firmlinks"		})	\
	X(DIRS_AS_FILES		, false	, false	, 'd',	{ "dirs-as-files"	, "no-recurse-dirs"		})	\
	X(DO_DIM_HIDDEN		, true	, false	, '.',	{ "dim-hidden"		, "dim"					})	\
	X(DO_MOUNT_OWNER	, false	, false	, NSF,	{ "mount-owner"								})	\
	X(DO_SORT_INPUTS	, false	, false	, NSF,	{ "sort-input"		, "sort-inputs"			})	\
	X(DO_DEVNO_MAJMIN	, true	, false	, NSF,	{ "devno-majmin"	, "majmin-devno"		})	\
	X(DO_REVERSE_SORT	, false	, false	, 'r',	{ "reverse"			, "rev"					})	\
	X(SORT_DIRS_FIRST	, true	, false	, 'D',	{ "dirs-first"		, "sort-dirs-first"		})	\
	X(SORT_CASE_SENSIT	, false	, false	, NSF,	{ "sort-case-sensitive"						})	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(do_icon			, true	, true	, 'I',	{ "icon"			, "icons"				})	\
	X(do_suffix			, true	, true	, 'P',	{ "suffix"			, "mark-type"			})	\
	X(do_link_to		, true	, true	, 'L',	{ "link-to"			, "symlinks"			})	\
	X(do_nlink			, true	, true	, 'n',	{ "nlink"									})	\
	X(do_dev_no			, false	, true	, NSF,	{ "dev-no"			, "device-number"		})	\
	X(do_inum			, false	, true	, 'i',	{ "inode"			, "ino"		, "inum"	})	\
	X(do_flags			, false	, true	, NSF,	{ "flags"									})	\
	X(do_flag_str		, true	, true	, NSF,	{ "flag-str"		, "flags-str"			})	\
	X(do_mode			, false	, true	, NSF,	{ "mode"									})	\
	X(do_mode_str		, true	, true	, NSF,	{ "mode-str"								})	\
	X(do_size			, false	, true	, NSF,	{ "size"									})	\
	X(do_size_str		, true	, true	, NSF,	{ "size-str"								})	\
	X(do_uid			, false	, true	, 'u',	{ "uid"										})	\
	X(do_usr_name		, true	, true	, 'U',	{ "uid-str"			, "usr-name", "user"	})	\
	X(do_gid			, false	, true	, 'g',	{ "gid"										})	\
	X(do_grp_name		, true	, true	, 'G',	{ "gid-str"			, "grp-name", "group"	})	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(do_time			, false	, true	, NSF,	{ "time"									})	\
	X(do_time_str		, true	, true	, NSF,	{ "time-str"								})	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(do_atime			, false	, true	, NSF,	{ "atime"									})	\
	X(do_mtime			, true	, true	, NSF,	{ "mtime"									})	\
	X(do_ctime			, false	, true	, NSF,	{ "ctime"									})	\
	X(do_btime			, false	, true	, NSF,	{ "btime"									})	\
   /*└──────────────────┴───────┴───────┴───────┴───────────────────────────────────────────┘*/

#define SORT_BY_CHR_FLAG 's'
#define DEPTH_CHR_FLAG	 'L'

// options which take an argument
//							   default	│ short	│ long				│ options
//							  ──────────┼───────┼───────────────────┼──────────────────────────
SortByField SORT_BY (void);	// name		│ 's'	│ "sort"  "sort-by"	│ [see `SortByField`]
uint8_t O__DEPTH	(void);	// 1		│ 'L'	│ "depth" "level"	│ 0 -> 16
bool DO_COLOUR		(void);	// auto		│ NSF	│ "color" "colour"	│ "", "always", "never"
// funcs handled by `--flags`  short	│ NSF	│ "flags"			│ "long", "tiny", "short"
bool DO_TINY_FLAGS	(void);
bool DO_SHORT_FLAGS	(void);

#define MAX_DEPTH O__DEPTH()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define X(name, ...) BO_##name,
	typedef enum BinOptIdx { BINARY_OPTIONS_TABLE BINOPT_COUNT } BinOptIdx;
#undef X

/**
 * @struct BinaryOption
 *
 * @note For some reason, if I put the `long_flags` field first, it results in an error:
 *
 *	`integer conversion resulted in truncation – C/C++(69)`
 */
typedef struct BinaryOption {
	bool value, is_field;
	char short_flag, long_flags[MAX_OPT_FLAG_NUM][MAX_OPT_FLAG_LEN];
} BinaryOption;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define X(name, ...) bool name(void);
	BINARY_OPTIONS_TABLE
#undef X

bool do_time_t(TimeType type);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !OPTIONS_INITIALIASED */
