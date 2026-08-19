/// @file debugging/debugging.h

#ifndef DEBUGGING_INITIALISED
#define DEBUGGING_INITIALISED

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

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

void d__debug(const LogLevelIdx level_, const char *time, const int lineno, const char *file, const char *fmt, ...);
void d__func(const char *func, const char *file);
void d__line(void);

#ifdef DEBUG_MODE
#	define debug(log_level, ...) d__debug(L_##log_level, __TIME__, __LINE__, __FILE__, __VA_ARGS__)
#	define dfunc(func) d__func(#func, __FILE__)
#	define dline() d__line()
#	define initDebugging(argv1) do {													\
		/* this is a very crude way to check for the `--clear` flag, */					\
		/*	but it's only used for debugging, so shouldn't be that big of an issue */	\
		if (argv1 != NULL && strcmp(argv1, "--clear") == 0) {							\
			printf("%s", CLEAR_SCREEN);													\
			fflush(stdout);																\
		}																				\
		/* debug(DEBUG, "────── DEBUGGING ──────"); */										\
	} while (0)
#else
#	define debug(log_level, ...)
#	define dfunc(func)
#	define dline()
#	define initDebugging(argv1)
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING_INITIALISED */

#if defined(LOG_LEVEL_TABLE) && !defined(DEBUGGING_IMPLEMENTATION)
#	undef LOG_LEVEL_TABLE
#endif
