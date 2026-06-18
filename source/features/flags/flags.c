/// @file features/flags/flags.c

#include <stdio.h>
#include <string.h>

#include "../../model/stat-model.h"
#include "../../options/options.h"

#include "flags.h"

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

void parseFlags(flagstr flag_string, const flag_t raw_flags) {
	for (int i = 0; i < MAX_FLAG_NUM; i++) {
		if (raw_flags & ALL_FLAGS[i].mask) {
			strcat(flag_string, GET_FLAG_NAME(ALL_FLAGS[i]));
			strcat(flag_string, ",");
		}
	}

	char *last_char = &flag_string[strlen(flag_string)-1];

	if (*last_char == ',') *last_char = '\0';
	else strcpy(flag_string, NO_FLAG_STR);
}

// spell:ignoreRegExp /, "\w+"/g
