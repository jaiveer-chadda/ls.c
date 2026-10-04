/// @file debugging/debugging.c

#include <wchar.h>
#include <stdarg.h>
#include <stdbool.h>
#include <execinfo.h>

#include "_defs.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef LOG_LEVEL_TABLE
#	define X(name, ...) [L_##name] = { #name, __VA_ARGS__ },
	static const LogLevel LOG_LEVELS[] = { LOG_LEVEL_TABLE };
#	undef X
#	undef LOG_LEVEL_TABLE
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__debug(
	const LogLevelIdx level_,
	const char *const time, const int lineno,
	const char *const file, const char *const func,
	const char *const fmt, ...
) {
	const LogLevel level = LOG_LEVELS[level_ < L_COUNT ? level_ : L_DEBUG];

	/* ———————————————————————————————————————————————————————————————————— */

	toStderr(ANSI("%hu")						,			level.colour	); // colour
	toStderr(D("[")	SP	"%-*s"	D("]") RESET " ", NAME_LEN, level.name		); //	[ WARNING ]
	toStderr(D("[")		"%*s"	D("]") RESET " ", TIME_LEN, time			); //		[02:41:15]
	toStderr(ANSI8(217)	"%*s"SP	D("@")		 " ", FUNC_LEN, func			); //			getTargetInfo @
	toStderr(ANSI8(111)	"%-*s"				 " ", FILE_LEN, REL_PATH(file)	); //				info/get-file-info.c
	toStderr(D("(")		"%*d"	D(")") RESET " ", LNNO_LEN, lineno			); //					(110)
	toStderr(ANSI("%hu")						,			level.colour	); // colour

	/* ———————————————————————————————————————————————————————————————————— */

	// fill the buffer with the output of `printf`
	char *pbuffer;
	va_list va_args;

	va_start(va_args, fmt); // `fmt` is the last known fixed argument
	vasprintf(&pbuffer, fmt, va_args);
	va_end(va_args);

	/* —————————————————————————————————— */

	for (const char *chr = pbuffer; *chr != '\0'; chr++) {
		fputc(*chr, stderr);
		if (*chr == '\n') toStderr("%*s", TOTAL_LEN, "");
	}

	free(pbuffer);
	toStderr(RESET "\n");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__line(const uint8_t len) {
	toStderr("%s", DIM);
	for (uint8_t i = 0; i < len; i++) fputwc(L'─', stderr);
	toStderr("%s\n", RESET);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define ST_LINE L"────────"

void d__stacktrace(void) {
	void *stack_buffer[STACK_MAX];
	// get the current stack return addresses, putting them into the `stack_buffer` array
	int stack_count = backtrace(stack_buffer, STACK_MAX);
	// translate addresses into strings
	char **stack = backtrace_symbols(stack_buffer, stack_count);

	dline();

	if (stack == NULL) {
		debug(ERROR, "`stacktrace` failed");
		dline();
		return;
	}

	// note: `ST_LINE` can't be passed directly to `printf`'s format string, since it's a multibyte (wchar_t) string
	toStderr("%ls function call stack (depth: %d) %ls\n",
		ST_LINE, stack_count, ST_LINE
	);

	// starting at `i = 1` avoids the stacktrace listing `d__stacktrace` in the stack
	for (int i = 1; i < stack_count; i++) {
		toStderr("[%d] %s\n", i - 1, stack[i]);
	}
	free(stack);

	dline();
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore LNNO
