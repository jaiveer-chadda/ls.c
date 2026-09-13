/// @file debugging/debugging.h

#ifndef DEBUGGING_INITIALISED
#define DEBUGGING_INITIALISED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <math.h> // used for some assertions
#include "model/stat-model.h"

#define LOG_LEVEL_TABLE \
	X(TRACE		, 90) \
	X(DEBUG		, 34) \
	X(INFO		, 37) \
	X(SUCCESS	, 32) \
	X(WARNING	, 33) \
	X(ERROR		, 31) \
	X(FATAL		, 41) \

#define X(name, ...) L_##name,
typedef enum { LOG_LEVEL_TABLE L_COUNT } LogLevelIdx;
#undef X

typedef struct {
	char name[10];
	unsigned short colour;
} LogLevel;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__stacktrace(void);
void d__debug(
	const LogLevelIdx level_,
	const char *const time, const int lineno,
	const char *const file, const char *const func,
	const char *const fmt, ...
);
void d__dump(const FileStat *const fs);
void d__line(const uint8_t len);

#ifdef DEBUG_MODE
#	define IN_DEBUG_MODE true
#	define IF_DEBUG(expr) expr

#	define stacktrace() d__stacktrace()
#	define debug(log_level, ...) d__debug(L_##log_level, __TIME__, __LINE__, __FILE__, __func__, __VA_ARGS__)
#	define dump(fs) d__dump(fs)

/* ————————————————————————————————————————————————————— */

#	define DEFAULT_DLINE_LEN 150

#	ifdef TTYCOLUMNS
#		define arg1__dline(len)	d__line((uint8_t)(((len) * TTYCOLUMNS) / DEFAULT_DLINE_LEN))
#		define arg0__dline()	d__line((uint8_t)(TTYCOLUMNS))
#	else
#		define arg1__dline(len)	d__line((uint8_t)(len))
#		define arg0__dline()	d__line((uint8_t)(DEFAULT_DLINE_LEN))
#	endif

#	define dline__DISPATCH(_1, NAME, ...) NAME
#	define dline(...) dline__DISPATCH(__VA_ARGS__ __VA_OPT__(,) arg1__dline, arg0__dline)(__VA_ARGS__)

/* ————————————————————————————————————————————————————— */

#	define _stri ((int)*((char*)str + i))
#	define seestr(str_, len) do {																				\
		fflush(stdout);																							\
		fflush(stderr);																							\
		const void *str = str_;																					\
		\
		for (int i = 0; i < (int)len; i++) {																	\
			switch (_stri) {																					\
				case '\0' : fputs("\33[100m0\33[m",stderr); break;												\
				case '\n' : fputs("\33[33mn\33[m", stderr); break;												\
				case '\r' : fputs("\33[33mr\33[m", stderr); break;												\
				case '\33': fputs("\33[34me\33[m", stderr); break;												\
				default:																						\
					if (0x01 <= _stri && _stri <= 0x09)	{ fprintf(stderr, "\33[91m\\%hu\33[m", _stri); break; }	\
					if (0x0A <= _stri && _stri <= 0x1F)	{ fprintf(stderr, "\33[92m\\x%x\33[m", _stri); break; }	\
					if (_stri & 128 /*(top bit set)*/ )	{ fprintf(stderr, "\33[95m\\x%x\33[m", _stri); break; }	\
					fputc(_stri, stderr);																		\
			}																									\
		}																										\
		\
		fputc('\n', stderr);																					\
		fflush(stderr);																							\
	} while (0)

/* ————————————————————————————————————————————————————— */

#	define initDebugging(argv) do {										\
		/* this is a very crude way to check for the `--clear` flag, */	\
		/*	but it's only used for debugging, so it should be fine   */	\
		if (argv[1] != NULL												\
			&& (strcmp(argv[1], "--clear") == 0)						\
			|| (argv0[0] == 'c')										\
		) {																\
			fputs(CLEAR_SCREEN, stderr);								\
			fflush(stderr);												\
		}																\
		dline();														\
	} while (0)

#else
#	define IN_DEBUG_MODE false
#	define IF_DEBUG(expr)
#	define stacktrace()
#	define debug(log_level, ...)
#	define dump(fs)
#	define dline(...)
#	define seestr(str, len)
#	define initDebugging(argv1)
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING_INITIALISED */

#if defined(LOG_LEVEL_TABLE) && !defined(DEBUGGING_IMPLEMENTATION)
#	undef LOG_LEVEL_TABLE
#endif
