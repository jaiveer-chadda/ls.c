/// @file options/parse-options.h

#pragma once

void none(void);

#define MAX_FLAG_COUNT	4
#define MAX_INPUT_LEN	1 << 6

enum OptType { FILES, VISUAL, FEATURE };

typedef struct {
	const char short_flag;
	const char *other_flags[MAX_FLAG_COUNT];

	const enum OptType type;
	const bool takes_input;

	char input[MAX_INPUT_LEN];
} Option;

const Option
	do_all		= {'a', {"--all"				}, FILES	, false, ""},
	do_alm_all	= {'A', {"--almost-all"			}, FILES	, false, ""},
	do_colour	= {'G', {"--colour", "--color"	}, VISUAL	, false, ""},
	do_psx_mode	= {'P', {"--posix-modes"		}, VISUAL	, false, ""},
	do_octal	= {'O', {"--octal"				}, FEATURE	, false, ""};
