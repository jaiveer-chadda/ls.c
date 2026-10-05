/// @file debugging/_defs.h

#ifndef DEBUGGING__DEFS_H_
#define DEBUGGING__DEFS_H_

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUGGING_IMPLEMENTATION
#include "debugging.h"

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

#define REL_PATH(file) (char *)(strstr((char *)(file), "source/") + (int)(sizeof("source/") - 1))

#define STACK_MAX 128

/* ———————————————————————————————————————————————————— */

#define SP " "

#define NAME_LEN 8
#define TIME_LEN (int)(sizeof("19:47:42") - 1)
#define FUNC_LEN 12
#define FILE_LEN 24
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

#define T		DIMS("├─")
#define I		DIMS("│ ")
#define O		DIMS("└─")

#define p		 "\33[96m*"			RESET
#define S		" \33[96m* "		RESET
#define E		" \33[94m= "		RESET

#define null	" \33[91m(null)"	RESET
#define STRUCT	" \33[95mstruct "	RESET
#define CHAR	" \33[95mchar "		RESET
#define BOOL	" \33[34mbool "		RESET

#define PTR				"%s"
#define STR		"\33[92m%s%s%s"		RESET
#define CHR		"\33[92m'%c'"		RESET
#define LCR		"\33[92m'%lc'"		RESET

#define ENM(idx) "\33[38;5;116m" DIMS("[")	#idx DIMS("]")	RESET
#define IDX(idx) "\33[38;5;216m" DIMS("[")	#idx DIMS("]")	RESET
#define NUM(fmt) "\33[38;5;216m"			#fmt		""	RESET
#define OCT(fmt) "\33[94m"					#fmt		""	RESET
#define   V(typ) "\33[93m"					#typ		""	RESET

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define ptr(ptr) tostr((void*)(ptr))
#define ifn(q, do, else) ((q) == NULL ? (do) : (else))
#define str(fld) ifn(fld,"","\""), ifn(fld, "\b" null, fld), ifn(fld,"","\"")

#define ter(...) fprintf(stderr, __VA_ARGS__);
#define err(fmt, ...) do { fprintf(stderr, (fmt "\n"), __VA_ARGS__); fflush(stderr); } while (0)
#define ERR(str_) fputs(str_ "\n", stderr);
#define pbool(val) ((val) ? "\33[32m✓ true\33[m" : "\33[31m× false\33[m")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING__DEFS_H_ */
