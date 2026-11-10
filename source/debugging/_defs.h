/// @file debugging/_defs.h
/// @note this file is used to define macros for `assert.c` and `debugging.c` - it shouldn't be included anywhere else

#ifndef DEBUGGING__DEFS_H_
#define DEBUGGING__DEFS_H_

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <string.h> // strstr()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef RESET
#	undef RESET
#	undef ANSI
#	undef DIM
#endif

#define RESET "\33[m"
#define ANSI(code) "\033[" code "m"
#define ANSI8(code) "\33[38;5;" #code "m"

#define DIM		ANSI("2")
#define NO_DIM	ANSI("22")

#define DIMS(str) DIM str NO_DIM
#define D DIMS

#define LBR DIMS("[")
#define RBR DIMS("]")

#define LPA DIMS("(")
#define RPA DIMS(")")

#define REL_PATH(abspath) ((char*)(			\
	strstr(((char*)(abspath)), "source/")	\
		+ ((int)(sizeof("source/") - 1))	\
))

#define STACK_MAX 128

/* ———————————————————————————————————————————————————— */

#define SP " "

#define NAME_LEN 8
#define TIME_LEN (int)(sizeof("19:47:42") - 1)
#define FUNC_LEN 17
#define FILE_LEN 26
#define LNNO_LEN 3

#define TOTAL_LEN (int)(\
	NAME_LEN + 1 +		\
	TIME_LEN + 1 +		\
	FUNC_LEN + 1 +		\
	FILE_LEN + 1 +		\
	LNNO_LEN + 1 +		\
	sizeof(				\
		SP "[]" "[]"	\
		SP "@"  "()"	\
	) - 1				\
)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define toStderr(...) do { fprintf(stderr, __VA_ARGS__); fflush(stderr); } while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define	RESET	"\33[m"		// reset colours

#define	NRED	"\33[31m"	// normal red
#define	BRED	"\33[91m"	// bright red
#define	BMAG	"\33[95m"	// bright magenta
#define	NBLUE	"\33[34m"	// normal blue
#define	BBLUE	"\33[94m"	// bright blue
#define	GREEN	"\33[92m"	// normal green

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING__DEFS_H_ */

// spell:ignore lnno bmag
