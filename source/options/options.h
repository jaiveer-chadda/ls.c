/// @file options/options.h

#ifndef OPTIONS_INITIALIASED
#define OPTIONS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "model/stat-model.h"

bool doColourAuto(void);
void usage(const int exit_code);
int	 setOptions(const int argc, char *const *const argv);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* Short Flags
/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾

Note:
I may change many of these short flags later, since, for quite a few of them,
I just assigned flags to them cos there was one available - not cos I want it to stay that way

————————————————————————————————————————————————————————

-_	DO_DIVIDERS				-/
-,							-%
-:							-+
-.	DO_DIM_HIDDEN			-=
-@							-~

-A	DO_DOTFILES				-a
-B							-b
-C	SORT_CASE_SENSIT		-c	DO_CLEAR
-D	SORT_DIRS_FIRST			-d	DIRS_AS_FILES
-E	do_mode_str				-e	do_mode
-F	do_flag_str				-f	do_flags
-G	do_grp_name				-g	do_gid
-H	DO_HEADER				-h
-I	do_icon					-i	do_inum
-J							-j
-K							-k	do_link_to
-L	DEPTH					-l
-M	DO_MOUNTDEV				-m	DO_DEVNO_MAJMIN
-N	do_dev_no				-n	do_nlink
-O	DO_MOUNT_OWNER			-o
-P	do_suffix				-p	DO_PATH
-Q							-q
-R							-r	DO_REVERSE_SORT
-S	DO_SORT_INPUTS			-s	SORT_BY
-T	do_time_str				-t	do_time
-U	do_usr_name				-u	do_uid
-V							-v
-W							-w
-X	DO_FIRMLINKS			-x
-Y							-y
-Z	do_size_str				-z	do_size

*/

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NSF '\0' /** No short flag. */

#define BINARY_OPTIONS_TABLE \
   /*┌──────────────────┬───────┬───────┬───────┬───────────────────────────────────────────┐*/	\
   /*│ option name		│default│ is	│ short	│ long flags								│*/	\
   /*│					│ value	│ field	│ flag	│											│*/	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(DO_PATH			, false	, false	, 'p',	{ "path"			, "full-path"			})	\
	X(DO_CLEAR			, false	, false	, 'c',	{ "clear"									})	\
	X(DO_HEADER			, false	, false	, 'H',	{ "header"			, "headers"				})	\
	X(DO_DOTFILES		, true	, false	, 'A',	{ "almost-all"								})	\
	X(DO_DIVIDERS		, true	, false	, '_',	{ "divider"			, "dividers"			})	\
	X(DO_MOUNTDEV		, true	, false	, 'M',	{ "mount"			, "mounts"				})	\
	X(DO_FIRMLINKS		, true	, false	, 'X',	{ "firmlinks"		, "check-firmlinks"		})	\
	X(DIRS_AS_FILES		, false	, false	, 'd',	{ "dirs-as-files"	, "no-recurse-dirs"		})	\
	X(DO_DIM_HIDDEN		, true	, false	, '.',	{ "dim-hidden"		, "dim"					})	\
	X(DO_MOUNT_OWNER	, true	, false	, 'O',	{ "mount-owner"								})	\
	X(DO_SORT_INPUTS	, false	, false	, 'S',	{ "sort-input"		, "sort-inputs"			})	\
	X(DO_DEVNO_MAJMIN	, true	, false	, 'm',	{ "devno-majmin"	, "majmin-devno"		})	\
	X(DO_REVERSE_SORT	, false	, false	, 'r',	{ "reverse"			, "rev"					})	\
	X(SORT_DIRS_FIRST	, true	, false	, 'D',	{ "dirs-first"		, "sort-dirs-first"		})	\
	X(SORT_CASE_SENSIT	, false	, false	, 'C',	{ "sort-case-sensitive"						})	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(do_icon			, true	, true	, 'I',	{ "icon"			, "icons"				})	\
	X(do_suffix			, true	, true	, 'P',	{ "suffix"			, "mark-type"			})	\
	X(do_link_to		, true	, true	, 'k',	{ "link-to"			, "symlinks"			})	\
	X(do_nlink			, true	, true	, 'n',	{ "nlink"									})	\
	X(do_dev_no			, false	, true	, 'N',	{ "dev-no"			, "device-number"		})	\
	X(do_inum			, false	, true	, 'i',	{ "inode"			, "ino"		, "inum"	})	\
	X(do_flags			, false	, true	, 'f',	{ "flags"									})	\
	X(do_flag_str		, true	, true	, 'F',	{ "flag-str"		, "flags-str"			})	\
	X(do_mode			, false	, true	, 'e',	{ "mode"									})	\
	X(do_mode_str		, true	, true	, 'E',	{ "mode-str"								})	\
	X(do_size			, false	, true	, 'z',	{ "size"									})	\
	X(do_size_str		, true	, true	, 'Z',	{ "size-str"								})	\
	X(do_uid			, false	, true	, 'u',	{ "uid"										})	\
	X(do_usr_name		, true	, true	, 'U',	{ "uid-str"			, "usr-name", "user"	})	\
	X(do_gid			, false	, true	, 'g',	{ "gid"										})	\
	X(do_grp_name		, true	, true	, 'G',	{ "gid-str"			, "grp-name", "group"	})	\
   /*├──────────────────┼───────┼───────┼───────┼───────────────────────────────────────────┤*/	\
	X(do_time			, false	, true	, 't',	{ "time"									})	\
	X(do_time_str		, true	, true	, 'T',	{ "time-str"								})	\
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

// note: the long options `--all` and `--all-fields` are also in use,
//		  as well as all previous long options, with `--do-` and `--no-` prefixed to them

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
