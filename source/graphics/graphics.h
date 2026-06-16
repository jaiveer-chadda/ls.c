/// @file graphics/graphics.h

#ifndef GRAPHICS_INITIALIASED
#define GRAPHICS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define FIELD_PAD " "

/* ———————————————————————————————————————————————————————————————————————————————— */

#define REGULAR_CHAR	'.'
#define DIR_CHAR		'd'
#define SYMLINK_CHAR	'l'
#define PIPE_CHAR		'|'
#define SOCKET_CHAR		'='
#define CHRDEV_CHAR		'c'
#define BLKDEV_CHAR		'b'
#define WHITEOUT_CHAR	'%'

#define DIR_SUFFIX		'/'
#define SYMLINK_SUFFIX	'@'
#define EXEC_SUFFIX		'*'

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define CSI "\033["
#define END "m"

#define CSI_FG	CSI "3"
#define CSI_BG	CSI "4"

#define RGB(r,g,b) "8;2;" #r ";" #g ";" #b

/* ———————————————————————————————————————————————————————————————————————————————— */

#define RESET		CSI END

#define NO_FG		CSI	"39" END
#define NO_BG		CSI	"49" END

#define	UNDER		CSI	 "4" END
#define	DUNDER		CSI	"21" END
#define NOUNDER		CSI	"24" END

#define	BOLD		CSI	 "1" END
#define	DIM			CSI	 "2" END
#define NOBOLD		CSI	"22" END

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NLINK_COL_DIR		CSI	"1;96"			END	// \e[96m
#define NLINK_COL_REG_1		CSI	"36"			END	// \e[36m
#define NLINK_COL_REG_MORE	CSI	"1;30;105"		END	// \e[105m

#define HARDLN_UNDERLINE	CSI	"1;21;58;5;13"	END	// \e[21m \e[95m

#define MAJ_COL				CSI "1;37"			END // \e[37m
#define MIN_COL				CSI "36"			END // \e[36m

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define HL_REG			""			//  \e[37m
#define HL_PUNCT		"90"		//  \e[90m

#define HL_DIR			"1;36"		//  \e[36m
#define HL_LINK			"35"		//  \e[35m
#define HL_EXEC			"31"		//  \e[31m
#define HL_PIPE			"33"		//  \e[33m
#define HL_MOUNT		"34"		//  \e[34m
#define HL_SOCKET		"32"		//  \e[32m
#define HL_CHRDEV		";1;30;43"	//  \e[43m
#define HL_BLKDEV		";1;30;46"	//  \e[46m
#define HL_OW_DIR		";1;30;42"	//  \e[42m
#define HL_SUID_X		";1;30;41"	//  \e[41m
#define HL_SUID_N		";1;30;101"	// \e[101m
#define HL_SGID_X		";1;30;45"	//  \e[45m
#define HL_SGID_N		";1;30;105"	// \e[105m
#define HL_STICKY_X		";1;30;44"	//  \e[44m
#define HL_STICKY_N		";1;30;104"	// \e[104m
#define HL_DATALESS		";1;30;47"	//  \e[47m
#define HL_WHITEOUT		";1;30;107"	// \e[107m

#define HL_READ			"92"		//  \e[92m
#define HL_W_USRGRP		"93"		//  \e[93m
#define HL_W_OTHER		";1;30;42"	//  \e[42m
#define HL_X_REG		"1;31"		//  \e[31m
#define HL_X_NREG		"91"		//  \e[91m

/* ———————————————————————————————————————————————————————————————————————————————— */

#define PUNCT	CSI HL_PUNCT END

/* ———————————————————————————————————————————————————————————————————————————————— */

// use the macro `X`, on the expectation that it'll be defined later
#define FILE_COLOUR_TABLE \
	X(FC_REGULAR,		HL_REG			) /* \e[37m */ \
	X(FC_DIRECT,	CSI	HL_DIR		END	) /* \e[36m */ \
	X(FC_SYMLINK,	CSI	HL_LINK		END	) /* \e[35m */ \
	X(FC_EXEC,		CSI	HL_EXEC		END	) /* \e[31m */ \
	X(FC_PIPE,		CSI	HL_PIPE		END	) /* \e[33m */ \
	X(FC_SOCKET,	CSI	HL_SOCKET	END	) /* \e[32m */ \
	X(FC_MOUNT,		CSI	HL_MOUNT	END	) /* \e[34m */ \
	X(FC_CHR_DEV,	CSI	HL_CHRDEV	END	) /* \e[43m */ \
	X(FC_BLK_DEV,	CSI	HL_BLKDEV	END	) /* \e[46m */ \
	X(FC_OW_DIR,	CSI	HL_OW_DIR	END	) /* \e[42m */ \
	X(FC_SUID_X,	CSI	HL_SUID_X	END	) /* \e[41m */ \
	X(FC_SUID_N,	CSI	HL_SUID_N	END	) /*\e[101m */ \
	X(FC_SGID_X,	CSI	HL_SGID_X	END	) /* \e[45m */ \
	X(FC_SGID_N,	CSI	HL_SGID_N	END	) /*\e[105m */ \
	X(FC_STICKY_X,	CSI	HL_STICKY_X	END	) /* \e[44m */ \
	X(FC_STICKY_N,	CSI	HL_STICKY_N	END	) /*\e[104m */ \
	X(FC_DATALESS,	CSI	HL_DATALESS	END	) /* \e[47m */ \
	X(FC_WHITEOUT,	CSI	HL_WHITEOUT	END	) /*\e[107m */

#define PERM_COLOUR_TABLE \
	X(PC_NONE		, CSI ";" HL_PUNCT		END	) /* \e[90m */ \
	X(PC_READ		, CSI ";" HL_READ		END	) /* \e[92m */ \
	X(PC_W_USRGRP	, CSI ";" HL_W_USRGRP	END	) /* \e[93m */ \
	X(PC_W_OTHER	, CSI ";" HL_W_OTHER	END	) /* \e[42m */ \
	X(PC_X_REG		, CSI ";" HL_X_REG		END	) /* \e[31m */ \
	X(PC_X_NREG		, CSI ";" HL_X_NREG		END	) /* \e[91m */ \
	X(PC_SUID_X		, CSI ";" HL_SUID_X		END	) /* \e[41m */ \
	X(PC_SUID_N		, CSI ";" HL_SUID_N		END	) /*\e[101m */ \
	X(PC_SGID_X		, CSI ";" HL_SGID_X		END	) /* \e[45m */ \
	X(PC_SGID_N		, CSI ";" HL_SGID_N		END	) /*\e[105m */ \
	X(PC_STICKY_X	, CSI ";" HL_STICKY_X	END	) /* \e[44m */ \
	X(PC_STICKY_N	, CSI ";" HL_STICKY_N	END	) /*\e[104m */

#define TIME_COLOUR_TABLE \
	X(TC_NOW	, CSI_FG RGB(203, 210, 242) ";1" END ) \
	X(TC_MIN	, CSI_FG RGB(200, 208, 241)		 END ) \
	X(TC_TODAY	, CSI_FG RGB(165, 183, 236)		 END ) \
	X(TC_YESTD	, CSI_FG RGB(133, 161, 228)		 END ) \
	X(TC_2DAYS	, CSI_FG RGB(100, 145, 225)		 END ) \
	X(TC_THIS_MO, CSI_FG RGB( 70, 132, 230)		 END ) \
	X(TC_THIS_YR, CSI_FG RGB( 35, 106, 204)		 END ) \
	X(TC_OTHER	, CSI_FG RGB(  4,  65, 145)		 END )

#define SIZE_COLOUR_TABLE \
	X(SC_Bb, CSI "92"		END ) /* \e[102m */ \
	X(SC_Bk, CSI "93"		END ) /* \e[103m */ \
	X(SC_Bm, CSI "38;5;216"	END ) /* #FFAB81 */ \
	X(SC_Bg, CSI "91"		END ) /* \e[101m */ \
	X(SC_Bt, CSI "38;5;168"	END ) /* #E85587 */ \
	\
	X(SC_Ub, CSI "32"		END ) /* \e[42m  */ \
	X(SC_Uk, CSI "33"		END ) /* \e[43m  */ \
	X(SC_Um, CSI "38;5;208"	END ) /* #FF8400 */ \
	X(SC_Ug, CSI "31"		END ) /* \e[41m  */ \
	X(SC_Ut, CSI "38;5;125"	END ) /* #BD0060 */

/* ———————————————————————————————————————————————————————————————————————————————— */

#define X(name, esc) name,	// only unpack the names
typedef enum { FILE_COLOUR_TABLE FILE_COLOUR_COUNT } FileColour;
typedef enum { PERM_COLOUR_TABLE PERM_COLOUR_COUNT } PermColour;
typedef enum { TIME_COLOUR_TABLE TIME_COLOUR_COUNT } TimeColour;
typedef enum { SIZE_COLOUR_TABLE SIZE_COLOUR_COUNT } SizeColour;
#undef X

extern const char *const file_colour_esc[FILE_COLOUR_COUNT];
extern const char *const perm_colour_esc[PERM_COLOUR_COUNT];
extern const char *const time_colour_esc[TIME_COLOUR_COUNT];
extern const char *const size_colour_esc[SIZE_COLOUR_COUNT];

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "../model/types.h"

void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags);
void printNLink(const nlink_t *nlink, const mode_t *mode, bool *hardln_hl);
void printSize(const sizestr size_str, const char unit);
void printModeStr(const modestr str);

#endif /* !GRAPHICS_INITIALIASED */
