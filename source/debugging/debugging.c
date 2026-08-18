/// @file debugging/debugging.c

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#define DEBUGGING_IMPLEMENTATION
#include "debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RESET "\33[m"
#define ANSI(code) "\033[" code "m"

#define DIM		ANSI("2")
#define NO_DIM	ANSI("22")

#define DIMS(str) DIM str NO_DIM

#define LBR DIMS("[")
#define RBR DIMS("]")

#define LPA DIMS("(")
#define RPA DIMS(")")

#define FILENAME ANSI("38;5;217")

#define LEVEL	ANSI("%hu") LBR " %-5s " RBR RESET " "
#define TIME	LBR "%s" RBR
#define FILE	FILENAME " %-30s" LPA "%3d" RPA RESET " "

#define REL_PATH(file) (char *)(strstr((char *)(file), "source/") + (int)strlen("source/"))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define toStderr(...) fprintf(stderr, __VA_ARGS__)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define X(name, ...) [L_##name] = { #name, __VA_ARGS__ }, 
static const LogLevel LOG_LEVELS[] = { LOG_LEVEL_TABLE };
#undef X

#ifdef LOG_LEVEL_TABLE
#	undef LOG_LEVEL_TABLE
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__debug(const LogLevelIdx level_, const char *time, const int line, const char *file, const char *fmt, ...) {
	const LogLevel level = LOG_LEVELS[level_ < L_COUNT ? level_ : L_DEBUG];

	toStderr(LEVEL TIME FILE,
		level.colour, level.name, time, REL_PATH(file), line
	);

	va_list va_args;
	va_start(va_args, fmt); // `fmt` is the last known fixed argument

	vfprintf(stderr, fmt, va_args);

	va_end(va_args);
	fprintf(stderr, "\n");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__func(const char *func, const char *file) {
	d__line();
	toStderr(FILENAME "%s() " DIMS("@") " %s" RESET "\n", func, REL_PATH(file));
	d__line();
}

void d__line(void) {
	toStderr("%s", DIM);
	for (int i = 0; i < 150; i++) toStderr("─");
	toStderr("%s\n", RESET);
}
