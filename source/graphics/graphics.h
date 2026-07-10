/// @file graphics/graphics.h

#ifndef GRAPHICS_INITIALIASED
#define GRAPHICS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— —— Chars & Strings —— ————————————————————————————————————————————————— */

/// The spacing between each of the fields/columns listed in long (`-l`) mode
#define FIELD_PAD " "
/// The extra spacing that should be printed before the filename column
#define PRE_NAME_PAD " "

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— Base ANSI Definitions ————————————————————————————————————————————————— */

#define CSI		"\033["
#define END		"m"

#define RESET	CSI END

#define ANSI(esc) CSI esc END

/* —— ANSI Non-Colour ——————————————————————————————————————————————————————— */

#define	UNDER		CSI	 "4" END	// \e[4m
#define	DUNDER		CSI	"21" END	// \e[21m
#define NOUNDER		CSI	"24" END	// \e[24m

#define	BOLD		CSI	 "1" END	// \e[1m
#define	DIM			CSI	 "2" END	// \e[2m
#define NOBOLD		CSI	"22" END	// \e[22m

/* —— tput screen controls —————————————————————————————————————————————————— */

#define RMAM		CSI "?7l"
#define SMAM		CSI "?7h"

#define REDRAW_SCRN	CSI "2J"
#define CURSOR_HOME	CSI "H"

#define CLR_SCREEN	CURSOR_HOME REDRAW_SCRN

/* —— RGB Definitions ——————————————————————————————————————————————————————— */

#define CSI_FG	CSI "3"
#define CSI_BG	CSI "4"

#define RGB(r,g,b)	"8;2;" #r ";" #g ";" #b

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— [Internal] Filename Colour Definitions ——————————————————————————————————————————————————————————————————————— */

#define HL_NONE			""			// \e[37m

#define HL_REG			HL_NONE		// \e[37m
#define HL_DIR			"1;36"		// \e[36m
#define HL_LINK			"35"		// \e[35m
#define HL_EXEC			"31"		// \e[31m
#define HL_PIPE			"33"		// \e[33m
#define HL_SOCKET		"32"		// \e[32m
#define HL_MOUNT		";1;4;34"	// \e[34m \e[4m
#define HL_CHRDEV		";1;30;43"	// \e[43m
#define HL_BLKDEV		";1;30;46"	// \e[46m
#define HL_OW_DIR		";1;30;42"	// \e[42m
#define HL_SUID_X		";1;30;41"	// \e[41m
#define HL_SUID_N		";1;30;101"	// \e[101m
#define HL_SGID_X		";1;30;45"	// \e[45m
#define HL_SGID_N		";1;30;105"	// \e[105m
#define HL_STICKY_X		";1;30;44"	// \e[44m
#define HL_STICKY_N		";1;30;104"	// \e[104m
#define HL_DATALESS		";1;30;47"	// \e[47m
#define HL_WHITEOUT		";1;30;107"	// \e[107m

#define HL_READ			"92"		// \e[92m
#define HL_W_USRGRP		"93"		// \e[93m
#define HL_W_OTHER		";1;30;42"	// \e[42m
#define HL_X_REG		"1;31"		// \e[31m
#define HL_X_NREG		"91"		// \e[91m

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— Header ———————————————————————————————————————————————————————————————— */

#define HEADER_HL				CSI "1;4;94" END // \e[94m

/* —— Punctuation ——————————————————————————————————————————————————————————— */

#define HL_PUNCT				"90"					// \e[90m
#define PUNCT					CSI HL_PUNCT		END	// \e[90m

/* —— Escape Characters ————————————————————————————————————————————————————— */

#define ESC_CHAR_COLOUR			"8;5;125"				// #BD0060

/* —— Links ————————————————————————————————————————————————————————————————— */

#define SYMLINK_ARROW			" -> "

#define	  VALID_ARROW_COLOUR	HL_PUNCT	// \e[90m
#define INVALID_ARROW_COLOUR	"31"		// \e[31m

#define LINK_PATH_COLOUR		"96"		// \e[96m
#define INVALID_LINK_COLOUR		"2;97"		// \e[90m [kinda]

/* —— NLink ————————————————————————————————————————————————————————————————— */

#define LN_COL_DIR				CSI	"1;96"			END	// \e[96m
#define LN_COL_DIR_EMPTY		CSI	"36"			END	// \e[36m
#define LN_COL_REG_1			CSI	"2;96"			END	// \e[96m \e[2m
#define LN_COL_REG_MORE			CSI	"1;30;105"		END	// \e[105m
#define LN_COL_OTHER			CSI	"1;30;41"		END	// \e[41m

#define HARDLN_UNDERLINE		CSI	"1;21;58;5;13"	END	// \e[21m \e[95m

/* —— Mode / Permissions ———————————————————————————————————————————————————— */

#define NO_PERM_CHAR			'-'

#define XATTR_CHAR				'@'
#define ACL_CHAR				'+'

#define READ_BIT_CHAR			'r'
#define WRITE_BIT_CHAR			'w'
#define EXEC_BIT_CHAR			'x'

#define SUGID_X_BIT_CHAR		's'
#define SUGID_N_BIT_CHAR		'S'

#define STICKY_X_BIT_CHAR		't'
#define STICKY_N_BIT_CHAR		'T'

#define SUID_N_BIT_CHAR			SUGID_N_BIT_CHAR
#define SUID_X_BIT_CHAR			SUGID_X_BIT_CHAR

#define SGID_N_BIT_CHAR			SUGID_N_BIT_CHAR
#define SGID_X_BIT_CHAR			SUGID_X_BIT_CHAR

/* —— UID/GID ——————————————————————————————————————————————————————————————— */

#define INV_FILE_USRNAME		"-"
#define INV_FILE_GRPNAME		"-"

#define USR_INV_COL				CSI HL_PUNCT		END	// \e[90m
#define GRP_INV_COL				CSI HL_PUNCT		END	// \e[90m

#define USR_YOU_COL				CSI "1;38;5;105"	END	// #807DED
#define USR_ROOT_COL			CSI "31"			END	// \e[31m
#define USR_OTH_COL				CSI "93"			END	// \e[93m

#define GRP_YOU_COL				CSI "93"			END	// \e[93m
#define GRP_ROOT_COL			CSI "94"			END	// \e[94m
#define GRP_OTH_COL				CSI "91"			END	// \e[91m

/* —— Flags ————————————————————————————————————————————————————————————————— */

#define NO_FLAG_STR				"-"
#define FLAG_SEP_STR			","

#define FL_U_NODUMP				CSI "92"		END	// \e[92m
#define FL_U_IMMUTABLE			CSI "94"		END	// \e[94m
#define FL_U_APPEND				CSI "93"		END	// \e[93m
#define FL_U_OPAQUE				CSI "97"		END	// \e[97m
#define FL_U_COMPRESSED			CSI "95"		END	// \e[95m
#define FL_U_TRACKED			CSI "91"		END	// \e[91m
#define FL_U_DATAVAULT			CSI "1;7"		END	// \e[07m
#define FL_U_HIDDEN				CSI "2"			END	// \e[02m
#define FL_S_ARCHIVED			CSI "32"		END	// \e[32m
#define FL_S_IMMUTABLE			CSI "34"		END	// \e[34m
#define FL_S_APPEND				CSI "33"		END	// \e[33m
#define FL_S_RESTRICTED			CSI "31"		END	// \e[31m
#define FL_S_NOUNLINK			CSI "36"		END	// \e[36m
#define FL_S_DATALESS			CSI HL_DATALESS	END	// \e[47m

/* —— Filetypes ————————————————————————————————————————————————————————————— */

#define UNKNOWN_CHAR			'?'
#define REGULAR_CHAR			'.'

#define DIR_CHAR				'd'
#define SYMLINK_CHAR			'l'
#define PIPE_CHAR				'|'
#define SOCKET_CHAR				'='
#define CHRDEV_CHAR				'c'
#define BLKDEV_CHAR				'b'
#define WHITEOUT_CHAR			'%'

#define DIR_SUFFIX				'/'
#define SYMLINK_SUFFIX			'@'
#define EXEC_SUFFIX				'*'

#define NOT_LINK				'{'	// both just arbitrary values
#define INVALID_LINK			'}'

// use the macro `X`, on the expectation that it'll be defined later
#define FILE_COLOUR_TABLE \
	X(FC_REGULAR	, HL_REG		) /* \e[37m  */ \
	X(FC_DIRECT		, HL_DIR		) /* \e[36m  */ \
	X(FC_SYMLINK	, HL_LINK		) /* \e[35m  */ \
	X(FC_EXEC		, HL_EXEC		) /* \e[31m  */ \
	X(FC_PIPE		, HL_PIPE		) /* \e[33m  */ \
	X(FC_SOCKET		, HL_SOCKET		) /* \e[32m  */ \
	X(FC_MOUNT		, HL_MOUNT		) /* \e[34m  */ \
	X(FC_CHR_DEV	, HL_CHRDEV		) /* \e[43m  */ \
	X(FC_BLK_DEV	, HL_BLKDEV		) /* \e[46m  */ \
	X(FC_OW_DIR		, HL_OW_DIR		) /* \e[42m  */ \
	X(FC_SUID_X		, HL_SUID_X		) /* \e[41m  */ \
	X(FC_SUID_N		, HL_SUID_N		) /* \e[101m */ \
	X(FC_SGID_X		, HL_SGID_X		) /* \e[45m  */ \
	X(FC_SGID_N		, HL_SGID_N		) /* \e[105m */ \
	X(FC_STICKY_X	, HL_STICKY_X	) /* \e[44m  */ \
	X(FC_STICKY_N	, HL_STICKY_N	) /* \e[104m */ \
	X(FC_DATALESS	, HL_DATALESS	) /* \e[47m  */ \
	X(FC_WHITEOUT	, HL_WHITEOUT	) /* \e[107m */

/* —— Permission Colours ———————————————————————————————————————————————————— */

#define XATTR_COLOUR  CSI ";38;5;147"		END
#define ACL_COLOUR	  CSI ";38;5;39"		END

#define PERM_COLOUR_TABLE \
	X(PC_NONE		, CSI ";" HL_PUNCT		END	) /* \e[90m  */ \
	X(PC_READ		, CSI ";" HL_READ		END	) /* \e[92m  */ \
	X(PC_W_USRGRP	, CSI ";" HL_W_USRGRP	END	) /* \e[93m  */ \
	X(PC_W_OTHER	, CSI ";" HL_W_OTHER	END	) /* \e[42m  */ \
	X(PC_X_REG		, CSI ";" HL_X_REG		END	) /* \e[31m  */ \
	X(PC_X_NREG		, CSI ";" HL_X_NREG		END	) /* \e[91m  */ \
	X(PC_SUID_X		, CSI ";" HL_SUID_X		END	) /* \e[41m  */ \
	X(PC_SUID_N		, CSI ";" HL_SUID_N		END	) /* \e[101m */ \
	X(PC_SGID_X		, CSI ";" HL_SGID_X		END	) /* \e[45m  */ \
	X(PC_SGID_N		, CSI ";" HL_SGID_N		END	) /* \e[105m */ \
	X(PC_STICKY_X	, CSI ";" HL_STICKY_X	END	) /* \e[44m  */ \
	X(PC_STICKY_N	, CSI ";" HL_STICKY_N	END	) /* \e[104m */

/* —— Time —————————————————————————————————————————————————————————————————— */

#define DATETIME_SPACE	"  "
#define TIME_ERR_STR	"--" DATETIME_SPACE "-- --"

#define DATE_FMT		"%a %e %b %y"
#define TIME_FMT		DATETIME_SPACE "%R"

#define TIME_COLOUR_TABLE \
	X(TC_NOW	, CSI_FG RGB(203, 210, 242) ";1" END ) \
	X(TC_MIN	, CSI_FG RGB(200, 208, 241)		 END ) \
	X(TC_TODAY	, CSI_FG RGB(165, 183, 236)		 END ) \
	X(TC_YESTD	, CSI_FG RGB(133, 161, 228)		 END ) \
	X(TC_2DAYS	, CSI_FG RGB(100, 145, 225)		 END ) \
	X(TC_THIS_MO, CSI_FG RGB( 70, 132, 230)		 END ) \
	X(TC_THIS_YR, CSI_FG RGB( 35, 106, 204)		 END ) \
	X(TC_OTHER	, CSI_FG RGB(  4,  65, 145)		 END )

/* —— File Sizes ———————————————————————————————————————————————————————————— */

#define NO_SIZE_STR		"-"
#define MAJ_MIN_SEP		","

#define UNIT_MAJ_MIN	','
#define UNIT_ZERO		'-'

#define UNIT_BYTE		'\0'
#define UNIT_KILO		'k'
#define UNIT_MEGA		'M'
#define UNIT_GIGA		'G'
#define UNIT_TERA		'T'
#define UNIT_PETA		'P'
#define UNIT_EXA		'E'
#define UNIT_ZETA		'Z'
#define UNIT_YOTTA		'Y'
#define UNIT_RONNA		'R'
#define UNIT_QUETTA		'Q'

#define MAJ_COL			CSI "1;37"	END // \e[37m
#define MIN_COL			CSI "36"	END // \e[36m

#define SIZE_COLOUR_TABLE \
	/* value */ \
	X(SC_BB, CSI "92"		END ) /* \e[102m */ \
	X(SC_BK, CSI "93"		END ) /* \e[103m */ \
	X(SC_BM, CSI "38;5;216"	END ) /* #FFAB81 */ \
	X(SC_BG, CSI "91"		END ) /* \e[101m */ \
	X(SC_BT, CSI "38;5;168"	END ) /* #E85587 */ \
	/* units */ \
	X(SC_UB, CSI "32"		END ) /* \e[42m  */ \
	X(SC_UK, CSI "33"		END ) /* \e[43m  */ \
	X(SC_UM, CSI "38;5;208"	END ) /* #FF8400 */ \
	X(SC_UG, CSI "31"		END ) /* \e[41m  */ \
	X(SC_UT, CSI "38;5;125"	END ) /* #BD0060 */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— —— Type Definitions —— ——————————————————————————————————————————————————————————————————————————————————————— */

#define X(name, esc) name,	// only unpack the names
typedef enum { FILE_COLOUR_TABLE FC_COUNT } FileColour;
typedef enum { PERM_COLOUR_TABLE PC_COUNT } PermColour;
typedef enum { TIME_COLOUR_TABLE TC_COUNT } TimeColour;
typedef enum { SIZE_COLOUR_TABLE SC_COUNT } SizeColour;
#undef X

/* —— —— Colour Enum Declarations —— ——————————————————————————————————————————————————————————————————————————————— */

extern const char *const file_colour_esc[FC_COUNT];
extern const char *const perm_colour_esc[PC_COUNT];
extern const char *const time_colour_esc[TC_COUNT];
extern const char *const size_colour_esc[SC_COUNT];

/* —— —— Function Declarations —— ——————————————————————————————————————————— */

#include "../model/types.h"
void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags, const bool is_mount);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !GRAPHICS_INITIALIASED */
