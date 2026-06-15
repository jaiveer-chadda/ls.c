/// @file features/flags/flags.c

#include <stdio.h>
#include <string.h>

#include "../../model/stat-model.h"
#include "../../options/options.h"
#include "flags.h"

typedef char flagname[MAX_FLAG_LEN];

typedef struct {
	flag_t	 mask;
	char name[MAX_FLAG_LEN];
	char short_name[6];
	char tiny_name[3];
} flagset;

static const flagset all_flags[MAX_FLAG_NUM] = {
	{ UF_NODUMP		, "nodump"		, "nodmp" , "nd" }, // do not dump file
	{ UF_IMMUTABLE	, "uimmutable"	, "uimut" , "ui" }, // file may not be changed
	{ UF_APPEND		, "uappend"		, "uapnd" , "ua" }, // writes to file may only append
	{ UF_OPAQUE		, "opaque"		, "opque" , "op" }, // directory is opaque wrt. union
	{ UF_COMPRESSED	, "compressed"	, "cmprs" , "cm" }, // file is compressed (some file-systems)
	{ UF_TRACKED	, "tracked"		, "track" , "tr" }, // UF_TRACKED is used for dealing with document IDs.
	{ UF_DATAVAULT	, "datavault"	, "dtvlt" , "dv" }, // entitlement required for reading and writing
	{ UF_HIDDEN		, "hidden"		, "hiddn" , "hd" }, // hint that this item should not be displayed in a GUI

	{ SF_ARCHIVED	, "archived"	, "archv" , "ar" }, // file is archived
	{ SF_IMMUTABLE	, "simmutable"	, "simut" , "si" }, // file may not be changed
	{ SF_APPEND		, "sappend"		, "sapnd" , "sa" }, // writes to file may only append
	{ SF_RESTRICTED	, "restricted"	, "restr" , "rs" }, // entitlement required for writing
	{ SF_NOUNLINK	, "nounlink"	, "nouln" , "nu" }, // Item may not be removed, renamed or mounted on
	{ SF_DATALESS	, "dataless"	, "dtles" , "dl" }, // file is dataless object
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define FLAG_NAME ( \
	DO_TINY_FLAGS ? all_flags[i].tiny_name : ( \
		DO_SHORT_FLAGS ? all_flags[i].short_name : all_flags[i].name \
	) \
)

void parseFlags(flagstr flag_string, const flag_t raw_flags) {
	for (int i = 0; i < MAX_FLAG_NUM; i++) {
		if (raw_flags & all_flags[i].mask) {
			strcat(flag_string, FLAG_NAME);
			strcat(flag_string, ",");
		}
	}

	char *last_char = &flag_string[strlen(flag_string)-1];

	if (*last_char == ',') *last_char = '\0';
	else strcpy(flag_string, "-");
}

// spell:ignoreRegExp /, "\w+"/g
