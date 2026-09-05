/// @file debugging/debugging.c

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <execinfo.h>

#define DEBUGGING_IMPLEMENTATION
#include "debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef RESET
#	undef RESET
#	undef ANSI
#	undef DIM
#endif

#define RESET "\33[m"
#define ANSI(code) "\033[" code "m"

#define DIM		ANSI("2")
#define NO_DIM	ANSI("22")

#define DIMS(str) DIM str NO_DIM

#define LBR DIMS("[")
#define RBR DIMS("]")

#define LPA DIMS("(")
#define RPA DIMS(")")

#define REL_PATH(file) (char *)(strstr((char *)(file), "source/") + (int)strlen("source/"))

#define STACK_MAX 128

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define toStderr(...) do { fprintf(stderr, __VA_ARGS__); fflush(stderr); } while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define X(name, ...) [L_##name] = { #name, __VA_ARGS__ }, 
static const LogLevel LOG_LEVELS[] = { LOG_LEVEL_TABLE };
#undef X

#ifdef LOG_LEVEL_TABLE
#	undef LOG_LEVEL_TABLE
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static char *last_file = "";
static char *last_func = "";

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__debug(
	const LogLevelIdx level_,
	const char *const time, const int lineno, const char *const file,
	const char *const fmt, ...
) {
	if (strcmp(last_file, file) != 0) {
		last_file = (char*)file;
		dline();
	}

	const LogLevel level = LOG_LEVELS[level_ < L_COUNT ? level_ : L_DEBUG];

	toStderr(
		ANSI("%hu") LBR " %-7s " RBR RESET " "	// [ WARNING ]
		LBR "%s" RBR " "						//		[02:41:15]
		ANSI("38;5;217") " %-22s" DIMS("@")		// 			getTargetInfo @
		ANSI("38;5;111") " %-30s"				//				info/get-file-info.c
		LPA "%3d" RPA RESET " "					//					(110)
		ANSI("%hu")
		,
		level.colour, level.name,
		time,
		last_func,
		REL_PATH(file),
		lineno,
		level.colour
	);

	va_list va_args;
	va_start(va_args, fmt); // `fmt` is the last known fixed argument

	vfprintf(stderr, fmt, va_args);
	va_end(va_args);

	fputs(RESET "\n", stderr);
	dline();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__func(const char *func) {
	if (strcmp(last_func, func) != 0) last_func = (char*)func;
}

void d__line(void) {
	toStderr("%s", DIM);
	for (int i = 0; i < 150; i++) fputs("─", stderr);
	toStderr("%s\n", RESET);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__stacktrace(void) {
	void *stack_buffer[STACK_MAX];

	// get the current stack return addresses
	int trace_size = backtrace(stack_buffer, STACK_MAX);
	// translate addresses into strings
	char **symbols = backtrace_symbols(stack_buffer, trace_size);

	dline();
	if (symbols == NULL) {
		debug(ERROR, "`stacktrace` failed");
		return;
	}

	printf("%s function call stack (depth: %d) %s\n", "────────", trace_size, "────────");
	for (int i = 0; i < trace_size; i++) printf("[%d] %s\n", i, symbols[i]);
	dline(); 

	free(symbols);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
