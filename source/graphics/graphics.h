/// @file graphics/graphics.h

#ifndef GRAPHICS_INITIALIASED
#define GRAPHICS_INITIALIASED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define INTERFIELD_PADDING " "

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

#define RESET	"\33[m"

#define NO_FG	"\33[39m"
#define NO_BG	"\33[49m"

#define	UNDER	"\33[4m"
#define NOUNDER	"\33[24m"

#define	BOLD	"\33[1m"
#define	DIM		"\33[2m"
#define NOBOLD	"\33[22m"

#define HARDLN_UNDERLINE "\33[1;21;58;5;13m"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NLINK_COL_DIR		"\33[96m"
#define NLINK_COL_REG_1		"\33[36m"
#define NLINK_COL_REG_MORE	"\33[1;30;105m"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// use the macro `X`, on the expectation that it'll be defined later
#define FILE_COLOUR_TABLE \
	X(REGULAR,	""				) /* \e[37m */ \
	X(DIRECT,	"\33[1;36m"		) /* \e[36m */ \
	X(SYMLINK,	"\33[35m"		) /* \e[35m */ \
	X(EXEC,		"\33[31m"		) /* \e[31m */ \
	X(PIPE,		"\33[33m"		) /* \e[33m */ \
	X(SOCKET,	"\33[32m"		) /* \e[32m */ \
	X(MOUNT,	"\33[34m"		) /* \e[34m */ \
	X(CHR_DEV,	"\33[1;30;43m"	) /* \e[43m */ \
	X(BLK_DEV,	"\33[1;30;46m"	) /* \e[46m */ \
	X(OW_DIR,	"\33[1;30;42m"	) /* \e[42m */ \
	X(SUID,		"\33[1;30;41m"	) /* \e[41m */ \
	X(SGID,		"\33[1;30;45m"	) /* \e[45m */ \
	X(STICKY,	"\33[1;30;44m"	) /* \e[44m */ \
	X(DATALESS,	"\33[1;30;47m"	) /* \e[47m */ \
	X(WHITEOUT, "\33[1;30;107m"	) /*\e[107m */

#define PERM_COLOUR_TABLE \
	X(NONE		, "\33[;90m"		) /* \e[90m */ \
	X(READ		, "\33[;92m"		) /* \e[92m */ \
	X(W_USRGRP	, "\33[;93m"		) /* \e[93m */ \
	X(W_OTHER	, "\33[;1;30;42m"	) /* \e[42m */ \
	X(X_REG		, "\33[;1;31m"		) /* \e[31m */ \
	X(X_NREG	, "\33[;91m"		) /* \e[91m */ \
	X(SUID_X	, "\33[;1;30;41m"	) /* \e[41m */ \
	X(SUID_N	, "\33[;1;30;101m"	) /*\e[101m */ \
	X(SGID_X	, "\33[;1;30;45m"	) /* \e[45m */ \
	X(SGID_N	, "\33[;1;30;105m"	) /*\e[105m */ \
	X(STICKY_X	, "\33[;1;30;44m"	) /* \e[44m */ \
	X(STICKY_N	, "\33[;1;30;104m"	) /*\e[104m */

/* ———————————————————————————————————————————————————————————————————————————————— */

#define X(name, esc) name,	// only unpack the names
typedef enum { FILE_COLOUR_TABLE FILE_COLOUR_COUNT } FileColour;
typedef enum { PERM_COLOUR_TABLE PERM_COLOUR_COUNT } PermColour;
#undef X

extern const char *const file_colour_esc[FILE_COLOUR_COUNT];
extern const char *const perm_colour_esc[PERM_COLOUR_COUNT];

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "../model/types.h"

void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags);
void printNLink(const nlink_t *nlink, const mode_t *mode, bool *hardln_hl);
void printModeStr(const modestr str);

#endif /* !GRAPHICS_INITIALIASED */
