/// @file graphics/graphics.h

void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags);
void printNLink(const nlink_t *nlink, const mode_t *mode, bool *hardln_hl);
void printModeStr(const modestr str);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define INTERFIELD_PADDING " "

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RESET	"\33[m"

#define NO_FG	"\33[39m"
#define NO_BG	"\33[49m"

#define	UNDER	"\33[4m"
#define NOUNDER	"\33[24m"

#define	BOLD	"\33[1m"
#define NOBOLD	"\33[22m"

#define HARDLN_UNDERLINE "\33[1;21;58;5;13m"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

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
