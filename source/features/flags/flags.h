/// @file features/flags/flags.h

#ifndef FLAGS_INITIALIASED
#define FLAGS_INITIALIASED

#include "../../options/options.h"

#define GET_FLAG_NAME(flag) \
	DO_TINY_FLAGS() ? flag.tiny_name : ( \
		DO_SHORT_FLAGS() ? flag.short_name : flag.name \
	)

typedef struct {
	flag_t mask;
	char name[MAX_FLAG_LEN];
	char short_name[6];
	char tiny_name[3];

	char colour[16];
} flagset;

extern const flagset ALL_FLAGS[MAX_FLAG_NUM];

void parseFlags(flagstr flag_string, const flag_t raw_flags);

#endif /* !FLAGS_INITIALIASED */
