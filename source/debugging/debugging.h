/// @file debugging/debugging.h

#ifndef DEBUGGING_INITIALISED
#define DEBUGGING_INITIALISED

/* —— #include ————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "model/stat-model.h"

#include "./_include/_init.h"
#include "./_include/_line.h"
#include "./_include/_assert.h"
#include "./_include/_seestr.h"

/* —— LOG_LEVEL_TABLE —————————————————————————————————————————————————————————————————————————————————————————————— */

#define LOG_LEVEL_TABLE \
	X(TRACE		, 90) \
	X(DEBUG		, 34) \
	X(INFO		, 37) \
	X(SUCCESS	, 32) \
	X(WARNING	, 33) \
	X(ERROR		, 31) \
	X(FATAL		, 41) \
/**/

#define X(name, ...) LL_##name,
	typedef enum LogLevelIdx { LOG_LEVEL_TABLE LL_COUNT } LogLevelIdx;
#undef X

#ifndef DEBUGGING_IMPLEMENTATION
#	undef LOG_LEVEL_TABLE
#endif

/* —— debug() & stacktrace() ——————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE

	void d__debug(
		const LogLevelIdx level_,
		const char *const time, const int lineno,
		const char *const file, const char *const func,
		const char *const fmt, ...
	);
	void d__stacktrace(void);

#	define debug(log_level, ...) d__debug(LL_##log_level, __TIME__, __LINE__, __FILE__, __func__, __VA_ARGS__)
#	define stacktrace() d__stacktrace()

#else
#	define debug(log_level, ...)
#	define stacktrace()
#endif /* DEBUG_MODE */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING_INITIALISED */
