/// @file form/init-formatting.c

#include <string.h>
#include "formatting.h"
#include "options/options.h"

#define X(fld, ttl, fms, fml) \
	[fld] = (field_t){ .title = ttl, .fmt_s = fms, .fmt_l = fml, .len = 0 },

field_t fields[FI_COUNT] = { FIELDS_TABLE };
#undef X

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// called from `main()`
inline void initFormatting(void) {
	if (DO_HEADER()) {
		#define X(fld, ttl, fms, fml) fields[fld].len = sizeof(ttl);
		FIELDS_TABLE
		#undef X
	}
}

void setLen(const FieldIdx field, const size_t length) {
	if (length > fields[field].len) {
		fields[field].len = length;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
