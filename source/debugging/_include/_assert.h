/// @file debugging/_include/_assert.h

#ifndef DEBUGGING__ASSERT_H_
#define DEBUGGING__ASSERT_H_

/* —— builtin_assert() ————————————————————————————————————————————————————————————————————————————————————————————— */

#define builtin_assert(expr) ( \
	__builtin_expect(!(expr), 0) \
		? __assert_rtn(__func__, __FILE_NAME__, __LINE__, #expr) \
		: (void)0 \
)

/* —— static_assert() —————————————————————————————————————————————————————————————————————————————————————————————— */

#if (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 202300L) && !defined(static_assert)
#	define st_as__arg2(expr, msg) _Static_assert((expr), msg)
#	define st_as__arg1(expr		)	 st_as__arg2( expr , ""	)

#	define st_as__dispatch(_1, _2, NAME, ...) NAME
#	define static_assert(expr, ...) \
		st_as__dispatch(expr __VA_OPT__(,) __VA_ARGS__, st_as__arg2, st_as__arg1)(expr __VA_OPT__(,) __VA_ARGS__)
#endif /* !__STDC_VERSION__ */

/* —— assert() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
	bool d__assert(
		const int expr, const char *const expr_str, const char *const message_,
		const int line, const char *const funcname, const char *const filepath
	);

#	ifdef assert
#		pragma message "`assert` macro is already defined"
#		undef assert
#	endif /* assert */

#	define assert__arg2(expr, e_str, msg) d__assert((expr), (e_str), (msg), __LINE__, __FILE__, __func__)
#	define assert__arg1(expr, e_str)	assert__arg2(expr ,	 e_str , NULL)

#	define assert__dispatch(_1, _2, NAME, ...) NAME
#	define assert(expr, ...) assert__dispatch(expr, __VA_ARGS__ __VA_OPT__(,) assert__arg2, assert__arg1) \
		(expr, #expr __VA_OPT__(,) __VA_ARGS__)
#else
#	define assert(expr, ...) true
#endif /* DEBUG_MODE */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !DEBUGGING__ASSERT_H_ */
