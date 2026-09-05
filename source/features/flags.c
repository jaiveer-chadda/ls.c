/// @file features/flags/flags.c

#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"

#include "form/formatting.h"
#include "options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	flag_t mask;
	char name[MAX_FLAG_LEN];
	char short_name[6];
	char tiny_name[3];

	Colour colour;
} flagset;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const flagset ALL_FLAGS[MAX_FLAG_NUM] = {
	{ UF_NODUMP		, "nodump"		, "nodmp", "nd", FL_U_NODUMP	 }, // do not dump file
	{ UF_IMMUTABLE	, "uimmutable"	, "uimut", "ui", FL_U_IMMUTABLE	 }, // file may not be changed
	{ UF_APPEND		, "uappend"		, "uapnd", "ua", FL_U_APPEND	 }, // writes to file may only append
	{ UF_OPAQUE		, "opaque"		, "opque", "op", FL_U_OPAQUE	 }, // directory is opaque wrt. union
	{ UF_COMPRESSED	, "compressed"	, "cmprs", "cm", FL_U_COMPRESSED }, // file is compressed (some file-systems)
	{ UF_TRACKED	, "tracked"		, "track", "tr", FL_U_TRACKED	 }, // used for dealing with document IDs
	{ UF_DATAVAULT	, "datavault"	, "dtvlt", "dv", FL_U_DATAVAULT	 }, // entitlement needed for reading & writing
	{ UF_HIDDEN		, "hidden"		, "hiddn", "hd", FL_U_HIDDEN	 }, // this item shouldn't be displayed in a GUI

	{ SF_ARCHIVED	, "archived"	, "archv", "ar", FL_S_ARCHIVED	 }, // file is archived
	{ SF_IMMUTABLE	, "simmutable"	, "simut", "si", FL_S_IMMUTABLE	 }, // file may not be changed
	{ SF_APPEND		, "sappend"		, "sapnd", "sa", FL_S_APPEND	 }, // writes to file may only append
	{ SF_RESTRICTED	, "restricted"	, "restr", "rs", FL_S_RESTRICTED }, // entitlement required for writing
	{ SF_NOUNLINK	, "nounlink"	, "nouln", "nu", FL_S_NOUNLINK	 }, // may not be removed, renamed or mounted on
	{ SF_DATALESS	, "dataless"	, "dtles", "dl", FL_S_DATALESS	 }, // file is dataless object
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GET_FLAG_NAME(flag) \
	(DO_TINY_FLAGS() ? (flag).tiny_name : ( \
		DO_SHORT_FLAGS() ? (flag).short_name : (flag).name \
	))

char *parseFlags(const flag_t raw_flags) {
	if (raw_flags == 0) {
		// make sure that we note down the size of the string
		//	which will be displayed if there aren't any flags
		setLen(FI_flag_str, sizeof(NO_FLAG_STR) - 1);
		return (char*)NULL;
	}

	flagstr flag_str = {0};
	bool is_first_flag = true;

	uint8_t str_len = 0U;
	size_t flag_len;
	flagset flag;

	for (int i = 0; i < MAX_FLAG_NUM; i++) {
		flag = ALL_FLAGS[i];

		if (raw_flags & flag.mask) {
			if (!is_first_flag) flag_str[str_len++] = FLAG_SEP_CHR;
			is_first_flag = false;

			flag_len = strlen(GET_FLAG_NAME(flag));
			memcpy(&flag_str[str_len], GET_FLAG_NAME(flag), flag_len);

			str_len += flag_len;
		}
	}

	setLen(FI_flag_str, str_len);

	flag_str[str_len++] = '\0';
	return memcpy(emalloc(str_len), flag_str, str_len);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_flags(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL;
	printf(
		valid ? fields[FI_flags].fmt_p : "%*c%s",
		getLen(FI_flags),
		valid ? pFS->s->st_flags : '-',
		FIELD_PAD
	);
}

void print_flag_str(const FileStat *const pFS) {
	const bool valid = pFS->f != NULL && pFS->f->flag_str != NULL;
	printf(fields[FI_flag_str].fmt_p, getLen(FI_flag_str), valid ? pFS->f->flag_str : NO_FLAG_STR, FIELD_PAD);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegExp /, "\w+"/g
