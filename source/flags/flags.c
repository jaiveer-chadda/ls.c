/// @file flags/flags.c

#include <stdio.h>

#include "../model/stat-model.h"
#include "flags.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define UF_SETTABLE		0x0000ffff	// mask of owner-changeable flags

/* ————————————————————————————————————————— */

#define UF_NODUMP		0x00000001	// do not dump file
#define UF_IMMUTABLE	0x00000002	// file may not be changed
#define UF_APPEND		0x00000004	// writes to file may only append
#define UF_OPAQUE		0x00000008	// directory is opaque wrt. union
#define UF_COMPRESSED	0x00000020	// file is compressed (some file-systems)
#define UF_TRACKED		0x00000040	// UF_TRACKED is used for dealing with document IDs.
#define UF_DATAVAULT	0x00000080	// entitlement required for reading and writing

#define UF_HIDDEN		0x00008000	// hint that this item should not be displayed in a GUI

/* ———————————————————————————————————————————————————————————————————————————————————————— */

#define SF_SUPPORTED	0x009f0000	// mask of superuser-supported flags
#define SF_SETTABLE		0x3fff0000	// mask of superuser-changeable flags
#define SF_SYNTHETIC	0xc0000000	// mask of system read-only synthetic flags

/* ————————————————————————————————————————— */

#define SF_ARCHIVED		0x00010000	// file is archived
#define SF_IMMUTABLE	0x00020000	// file may not be changed
#define SF_APPEND		0x00040000	// writes to file may only append
#define SF_RESTRICTED	0x00080000	// entitlement required for writing
#define SF_NOUNLINK		0x00100000	// Item may not be removed, renamed or mounted on
#define SF_DATALESS		0x40000000	// file is dataless object

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void parseFlags(flagstr flag_string, const flag_t raw_flags) {
	sprintf(flag_string, "%u", raw_flags);
}
