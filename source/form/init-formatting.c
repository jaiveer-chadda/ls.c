/// @file form/init-formatting.c

#include <string.h>
#include "formatting.h"
#include "options/options.h"

#define X(fld, ttl, fms, fml) \
	/* initialise the array, and set all the elements' lengths to 0 */ \
	[fld] = (field_t){ .title = ttl, .fmt_s = fms, .fmt_l = fml, .len = 0 },

field_t fields[FI_COUNT] = { FIELDS_TABLE };
#undef X

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// called from `main()`
inline void initFormatting(void) {
	if (DO_HEADER()) {
		// if we're printing a header, then set all field lengths to the lengths of their header strings
		#define X(fld, ttl, fms, fml) \
			fields[fld].len = sizeof(ttl) - 1;

		FIELDS_TABLE
		#undef X
	}
}

// this is honestly just a helper function - I could do the logic inline, but this adds a nice level of abstraction
inline void setLen(const FieldIdx field, const size_t length) {
	// if the inputted length is longer than the current max, replace it
	if (length > fields[field].len) {
		fields[field].len = length;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
