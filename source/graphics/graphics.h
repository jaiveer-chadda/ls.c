/// @file graphics/graphics.h

// #include "../options/options.h"

void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RESET	"\33[m"

#define NO_FG	"\33[39m"
#define NO_BG	"\33[49m"

#define	UNDER	"\33[4m"
#define NOUNDER	"\33[24m"

#define	BOLD	"\33[1m"
#define NOBOLD	"\33[22m"
