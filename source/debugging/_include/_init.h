/// @file debugging/_include/_init.h

#ifndef DEBUGGING__INIT_H_
#define DEBUGGING__INIT_H_

#ifdef DEBUG_MODE
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
#	define initDebugging(argv)
#endif /* DEBUG_MODE */

#endif /* !DEBUGGING__INIT_H_ */
