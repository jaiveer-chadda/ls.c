/// @file debugging/_include/_line.h

#ifndef DEBUGGING__LINE_H_
#define DEBUGGING__LINE_H_

#ifdef DEBUG_MODE
	void d__line(const uint8_t len);

#	define DEFAULT_DLINE_LEN 150

#	ifndef TTYCOLUMNS
#		define arg1__dline(len)	d__line((uint8_t)(len))
#		define arg0__dline()	d__line((uint8_t)(DEFAULT_DLINE_LEN))
#	else
#		define arg1__dline(len)	d__line((uint8_t)(((len) * TTYCOLUMNS) / DEFAULT_DLINE_LEN))
#		define arg0__dline()	d__line((uint8_t)(TTYCOLUMNS))
#	endif /* !TTYCOLUMNS */

#	define dline__DISPATCH(_1, NAME, ...) NAME
#	define dline(...) dline__DISPATCH(__VA_ARGS__ __VA_OPT__(,) arg1__dline, arg0__dline)(__VA_ARGS__)

#else
#	define DEFAULT_DLINE_LEN (void)0
#	define dline(...)
#endif /* DEBUG_MODE */

#endif /* !DEBUGGING__LINE_H_ */
