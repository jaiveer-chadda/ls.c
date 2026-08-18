/// @file debugging/debugging.h

#ifndef DEBUGGING_INITIALISED
#define DEBUGGING_INITIALISED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define LOG_LEVEL_TABLE \
	X(TRACE	, 90) \
	X(DEBUG	, 34) \
	X(INFO	, 37) \
	X(SUCCE	, 32) \
	X(WARN	, 33) \
	X(ERROR	, 31) \
	X(CRIT	, 41) \

#define X(name, ...) L_##name,
typedef enum { LOG_LEVEL_TABLE L_COUNT } LogLevelIdx;
#undef X

typedef struct {
	char name[10];
	unsigned short colour;
} LogLevel;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__debug(const LogLevelIdx level_, const char *time, const int line, const char *file, const char *fmt, ...);
void d__func(const char *func, const char *file);
void d__line(void);

#ifdef DEBUG_MODE
#	define debug(log_level, ...) d__debug(L_##log_level, __TIME__, __LINE__, __FILE__, __VA_ARGS__)
#	define Dfunc(func) d__func(#func, __FILE__)
#	define Dline() d__line()
#else
#	define debug(log_level, ...)
#	define Dfunc(func)
#	define Dline()
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING_INITIALISED */

#if defined(LOG_LEVEL_TABLE) && !defined(DEBUGGING_IMPLEMENTATION)
#	undef LOG_LEVEL_TABLE
#endif
