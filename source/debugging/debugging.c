/// @file debugging/debugging.c

#include <stdio.h>
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

#define LEVEL	ANSI("%hu") LBR " %-5s " RBR RESET " "
#define TIME	LBR "%s" RBR
#define FILE	ANSI("38;5;217") " %-30s" LPA "%3d" RPA RESET " "

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

void d__debug(const LogLevelIdx level_, const char *message, const char *time, const int line, const char *file) {
	const LogLevel level = LOG_LEVELS[level_ ? level_ < L_COUNT : L_DEBUG];
	const char *rel_path = strstr(file, "source/") + strlen("source/");

	toStderr(LEVEL TIME FILE "%s\n",
		level.colour, level.name, time, rel_path, line, message
	);
}
