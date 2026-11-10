/// @file debugging/_include/_seestr.h

#ifndef DEBUGGING__SEESTR_H_
#define DEBUGGING__SEESTR_H_

#ifdef DEBUG_MODE
#	define str_i ((int)*((char*)str + i))
#	define seestr(str_, len)																					\
	do {																										\
		fflush(stdout);																							\
		fflush(stderr);																							\
		\
		const void *const str = str_;																			\
		\
		for (int i = 0; i < (int)len; i++) {																	\
			switch (str_i) {																					\
				case '\0' : fputs("\33[100m0\33[m",stderr); break;												\
				case '\n' : fputs("\33[33mn\33[m", stderr); break;												\
				case '\r' : fputs("\33[33mr\33[m", stderr); break;												\
				case '\33': fputs("\33[34me\33[m", stderr); break;												\
				\
				default: {																						\
					if (0x01 <= str_i && str_i <= 0x09)	{ fprintf(stderr, "\33[91m\\%hu\33[m", str_i); break; }	\
					if (0x0A <= str_i && str_i <= 0x1F)	{ fprintf(stderr, "\33[92m\\x%x\33[m", str_i); break; }	\
					if (str_i & 128 /*(top bit set)*/ )	{ fprintf(stderr, "\33[95m\\x%x\33[m", str_i); break; }	\
					fputc(str_i, stderr);																		\
				}																								\
			}																									\
		}																										\
		\
		fputc('\n', stderr);																					\
		fflush(stderr);																							\
	} while (0)
#else 
#	define seestr(str_, len)
#endif /* DEBUG_MODE */

#endif /* !DEBUGGING__SEESTR_H_ */
