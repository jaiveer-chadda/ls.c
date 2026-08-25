/// @file graphics/graphics.h

#ifndef GRAPHICS_INITIALIASED
#define GRAPHICS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— —— Chars & Strings —— ————————————————————————————————————————————————— */

#define FIELD_PAD	 " " /// The spacing between each of the fields/columns listed in long (`-l`) mode.
#define PRE_NAME_PAD " " /// The extra spacing that should be printed before the filename column.

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— Base ANSI Definitions ————————————————————————————————————————————————— */

#define CSI		"\033["	// \e[
#define END		"m"		// m

#define RESET	CSI END	/// \e[m /** Reset all ANSI highlighting. */
#define CSIR	CSI ";"	/// \e[; /** Reset all ANSI highlighting before printing the subsequent escape sequence. */

#define NO_COLOUR ""

#define ANSI(esc)  CSI	esc END
#define ANSIR(esc) CSIR	esc END

/* —— ANSI Non-Colour ——————————————————————————————————————————————————————— */

#define	UNDER	"4"	// \e[4m
#define	DIM		"2"	// \e[2m
#define	NODIM	"22"// \e[22m

/* —— tput screen controls —————————————————————————————————————————————————— */

#define RMAM		CSI "?7l"
#define SMAM		CSI "?7h"

#define REDRAW_SCRN	CSI "2J"
#define CURSOR_HOME	CSI "H"

#define CLEAR_SCREEN	CURSOR_HOME REDRAW_SCRN

/* —— RGB Definitions ——————————————————————————————————————————————————————— */

#define CSI_FG	CSI "3"
#define CSI_BG	CSI "4"

#define RGB(r,g,b)	"8;2;" #r ";" #g ";" #b

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— [Internal] Filename Colour Definitions ——————————————————————————————————————————————————————————————————————— */

#define HL_REG			NO_COLOUR	// \e[37m
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

#define HL_COMPRESSED	"38;5;137"	// #B68558
#define HL_IMAGE		"95"		// \e[95m
#define HL_VIDEO		"91"		// \e[91m
#define HL_AUDIO_UNCM	"38;5;116"	// #6ADAD8
#define HL_AUDIO_COMP	"92"		// \e[92m
#define HL_TEMP_BACK	"90"		// \e[90m

#define HL_READ			"92"		// \e[92m
#define HL_W_USRGRP		"93"		// \e[93m
#define HL_W_OTHER		";1;30;42"	// \e[42m
#define HL_X_REG		"1;31"		// \e[31m
#define HL_X_NREG		"91"		// \e[91m

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/* —— Header ———————————————————————————————————————————————————————————————— */

#define HEADER_HL				"1;4;94"		// \e[94m

/* —— Punctuation ——————————————————————————————————————————————————————————— */

#define PUNCT					"90"			// \e[90m

/* —— Escape Characters ————————————————————————————————————————————————————— */

#define ESC_CHAR_COLOUR			"8;5;125"		// #BD0060

/* —— Links ————————————————————————————————————————————————————————————————— */

#define SYMLINK_ARROW			" -> "
#define APPLE_ARROW				" —a→ "
#define EACCES_ARROW			" —?→ "

#define EACCES_MSG_NO_COLOUR	"[permission denied]"
#define EACCES_MSG_COLOUR		ANSI(DIM ";31") "[" ANSI(NODIM) "permission denied" ANSI(DIM) "]" RESET

#define	  VALID_ARROW_COLOUR	PUNCT			// \e[90m
#define INVALID_ARROW_COLOUR	"31"			// \e[31m

#define LINK_PATH_COLOUR		"96"			// \e[96m
#define INVALID_LINK_COLOUR		"2;97"			// \e[90m [kinda]

/* —— NLink ————————————————————————————————————————————————————————————————— */

#define LN_COL_DIR				"1;96"			// \e[96m
#define LN_COL_DIR_EMPTY		"36"			// \e[36m
#define LN_COL_REG_1			"2;96"			// \e[96m \e[2m
#define LN_COL_REG_MORE			"1;30;105"		// \e[105m
#define LN_COL_OTHER			"1;30;41"		// \e[41m

#define HARDLN_UNDERLINE		";21;58;5;13"	// \e[21m \e[95m

/* —— Mount Point ——————————————————————————————————————————————————————————— */

// [/dev/disk3s1s1 (apfs)]
#define MTPT_COL_FROM			"38;5;182"		// /dev/disk3s1s1
#define MTPT_COL_TYPE			"38;5;146"		//  apfs
#define MTPT_COL_PUNC_1			PUNCT			// \e[90m
#define MTPT_COL_PUNC_2			PUNCT			// \e[90m

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

#define INV_FILE_USRNAME		"-"				/// The string to display if a file's username couldn't be found.
#define INV_FILE_GRPNAME		"-"				/// The string to display if a file's groupname couldn't be found.

#define USR_INV_COL				PUNCT			// \e[90m
#define GRP_INV_COL				PUNCT			// \e[90m

#define USR_YOU_COL				"1;38;5;105"	// #807DED
#define USR_ROOT_COL			"31"			// \e[31m
#define USR_OTH_COL				"93"			// \e[93m

#define GRP_YOU_COL				"93"			// \e[93m
#define GRP_ROOT_COL			"94"			// \e[94m
#define GRP_OTH_COL				"91"			// \e[91m

/* —— Flags ————————————————————————————————————————————————————————————————— */

#define NO_FLAG_STR				"-"			/// The string to display if the file doesn't have any flags.
#define FLAG_SEP_STR			","			/// The string to display between a file's flags.

#define FL_U_NODUMP				"92"		// \e[92m
#define FL_U_IMMUTABLE			"94"		// \e[94m
#define FL_U_APPEND				"93"		// \e[93m
#define FL_U_OPAQUE				"97"		// \e[97m
#define FL_U_COMPRESSED			"95"		// \e[95m
#define FL_U_TRACKED			"91"		// \e[91m
#define FL_U_DATAVAULT			"1;7"		// \e[07m
#define FL_U_HIDDEN				"2"			// \e[02m
#define FL_S_ARCHIVED			"32"		// \e[32m
#define FL_S_IMMUTABLE			"34"		// \e[34m
#define FL_S_APPEND				"33"		// \e[33m
#define FL_S_RESTRICTED			"31"		// \e[31m
#define FL_S_NOUNLINK			"36"		// \e[36m
#define FL_S_DATALESS			HL_DATALESS	// \e[47m

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

#define NOT_LINK				'{' /// An arbitrary value to indicate that this file isn't a symlink.
#define INVALID_LINK			'}' /// An arbitrary value to indicate that this file is an invalid symlink.

#define APPLE_LINK				'1' /// An arbitrary value to indicate that this file is an Apple alias file.
#define INV_APPLE_LINK			'2' /// An arbitrary value to indicate that this file is an invalid Apple alias file.

// use the macro `X`, on the expectation that it'll be defined later
#define FILE_COLOUR_TABLE \
	/* File Type   */ \
	X(FC_REGULAR	, HL_REG		) /* \e[37m  */ \
	X(FC_DIRECT		, HL_DIR		) /* \e[36m  */ \
	X(FC_SYMLINK	, HL_LINK		) /* \e[35m  */ \
	X(FC_EXEC		, HL_EXEC		) /* \e[31m  */ \
	X(FC_PIPE		, HL_PIPE		) /* \e[33m  */ \
	X(FC_SOCKET		, HL_SOCKET		) /* \e[32m  */ \
	X(FC_MOUNT		, HL_MOUNT		) /* \e[34m  */ \
	X(FC_CHR_DEV	, HL_CHRDEV		) /* \e[43m  */ \
	X(FC_BLK_DEV	, HL_BLKDEV		) /* \e[46m  */ \
	X(FC_WHITEOUT	, HL_WHITEOUT	) /* \e[107m */ \
	/* Permissions */ \
	X(FC_OW_DIR		, HL_OW_DIR		) /* \e[42m  */ \
	X(FC_SUID_X		, HL_SUID_X		) /* \e[41m  */ \
	X(FC_SUID_N		, HL_SUID_N		) /* \e[101m */ \
	X(FC_SGID_X		, HL_SGID_X		) /* \e[45m  */ \
	X(FC_SGID_N		, HL_SGID_N		) /* \e[105m */ \
	X(FC_STICKY_X	, HL_STICKY_X	) /* \e[44m  */ \
	X(FC_STICKY_N	, HL_STICKY_N	) /* \e[104m */ \
	/* Flags	   */ \
	X(FC_DATALESS	, HL_DATALESS	) /* \e[47m  */ \
	/* Extension   */ \
	X(FC_COMPRESSED	, HL_COMPRESSED	) /* #B68558 */ \
	X(FC_IMAGE		, HL_IMAGE		) /* \e[95m  */ \
	X(FC_VIDEO		, HL_VIDEO		) /* \e[91m  */ \
	X(FC_AUDIO_UNCM	, HL_AUDIO_UNCM	) /* #6ADAD8 */ \
	X(FC_AUDIO_COMP	, HL_AUDIO_COMP	) /* \e[92m  */ \
	X(FC_TEMP_BACK	, HL_TEMP_BACK	) /* \e[90m  */

/* —— Permission Colours ———————————————————————————————————————————————————— */

#define XATTR_COLOUR  ";38;5;147"
#define ACL_COLOUR	  ";38;5;39"

#define PERM_COLOUR_TABLE \
	X(PC_NONE		, PUNCT			) /* \e[90m  */ \
	X(PC_READ		, HL_READ		) /* \e[92m  */ \
	X(PC_W_USRGRP	, HL_W_USRGRP	) /* \e[93m  */ \
	X(PC_W_OTHER	, HL_W_OTHER	) /* \e[42m  */ \
	X(PC_X_REG		, HL_X_REG		) /* \e[31m  */ \
	X(PC_X_NREG		, HL_X_NREG		) /* \e[91m  */ \
	X(PC_SUID_X		, HL_SUID_X		) /* \e[41m  */ \
	X(PC_SUID_N		, HL_SUID_N		) /* \e[101m */ \
	X(PC_SGID_X		, HL_SGID_X		) /* \e[45m  */ \
	X(PC_SGID_N		, HL_SGID_N		) /* \e[105m */ \
	X(PC_STICKY_X	, HL_STICKY_X	) /* \e[44m  */ \
	X(PC_STICKY_N	, HL_STICKY_N	) /* \e[104m */

/* —— Time —————————————————————————————————————————————————————————————————— */

#define DATETIME_SPACE	"  "
#define TIME_ERR_STR	"--" DATETIME_SPACE "-- --"

#define DATE_FMT		"%a %e %b %y"
#define TIME_FMT		DATETIME_SPACE "%R"

#define TIME_COLOUR_TABLE \
	X(TC_NOW	, RGB(203, 210, 242) ";1"	) \
	X(TC_MIN	, RGB(200, 208, 241)		) \
	X(TC_TODAY	, RGB(165, 183, 236)		) \
	X(TC_YESTD	, RGB(133, 161, 228)		) \
	X(TC_2DAYS	, RGB(100, 145, 225)		) \
	X(TC_THIS_MO, RGB( 70, 132, 230)		) \
	X(TC_THIS_YR, RGB( 35, 106, 204)		) \
	X(TC_OTHER	, RGB(  4,  65, 145)		)

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

#define MAJ_COL	"1;37"	// \e[37m
#define MIN_COL	"36"	// \e[36m

#define SIZE_COLOUR_TABLE \
	/* value */	\
	X(SC_BB, "92"		) /* \e[102m */ \
	X(SC_BK, "93"		) /* \e[103m */ \
	X(SC_BM, "38;5;216"	) /* #FFAB81 */ \
	X(SC_BG, "91"		) /* \e[101m */ \
	X(SC_BT, "38;5;168"	) /* #E85587 */ \
	/* units */	\
	X(SC_UB, "32"		) /* \e[42m  */ \
	X(SC_UK, "33"		) /* \e[43m  */ \
	X(SC_UM, "38;5;208"	) /* #FF8400 */ \
	X(SC_UG, "31"		) /* \e[41m  */ \
	X(SC_UT, "38;5;125"	) /* #BD0060 */

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

#include "model/types.h"
void setFileColour(FileColour *colour, const name_t name, const mode_t mode, const flag_t flags, const bool is_mount);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !GRAPHICS_INITIALIASED */
