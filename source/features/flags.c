/// @file features/flags/flags.c

#include <stdio.h>
#include <stdlib.h>
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

static const flagset ALL_FLAGS[] = {
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
	{ SF_NOUNLINK	, "snounlink"	, "sunln", "su", FL_S_NOUNLINK	 }, // may not be removed, renamed or mounted on
	{ SF_FIRMLINK	, "firmlink"	, "firml", "fl", FL_S_FIRMLINK	 }, // directory is a firmlink
	{ SF_DATALESS	, "dataless"	, "dtles", "dl", FL_S_DATALESS	 }, // file is dataless object

	//UF_NOUNLINK	, "unounlink"	, "unoul", "uu", FL_U_NOUNLINK	 }, // [BSD only]
	//SF_SNAPSHOT	, "dataless"	, "snaps", "sn", FL_S_SNAPSHOT	 }, // [BSD only]
};

#define FLAG_COUNT ((int)(sizeof(ALL_FLAGS) / sizeof(ALL_FLAGS[0])))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/** The file containing the mapping between `System` directories, and their firmlinked directories in `Data`. */
#define FIRMLINK_MAP_FILE "/usr/share/firmlinks"

/** The longest firmlink len on my system is 62 chars long, so this should be enough memory.
 *	However, this is arbitrary, as `getdelim` will allocate as much memory as it needs to. */
#define INIT_LN_BUFSIZE	((size_t)64)
#define INIT_FLN_COUNT	((size_t)16)

#define SYST_MODE_DELIM	'\t'
#define DATA_MODE_DELIM	'\n'

#define SWAP_DELIMS() ((delim == SYST_MODE_DELIM) ? DATA_MODE_DELIM : SYST_MODE_DELIM)

/** Approximately multiplies a number by 1.5 */
#define MULT_BY_1_5(var) ((var) += (var) == 1 ? 1 : (var) >> 1)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// @brief Static pointer to the firmlink file.
static FILE *p_flink = NULL;

/// @brief An array of strings containing all firmlinks listed in `/usr/share/firmlinks`
static char **FIRMLINKS = NULL;
static uint16_t fl_count = 0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool initFirmlinks(void) {
	static bool did_init = false, success = false;

	if (did_init) return success;
	did_init = true;

	/* ———————————————————————————————————————————————— */
	// from here on, everything will only run once

	// open the firmlink file for reading
	p_flink = fopen(FIRMLINK_MAP_FILE, "r");

	// it's fine p_flink is NULL - we'll check this return value in the calling function,
	//	which should return early every time from now on
	if (p_flink == NULL) return ( success = false );

	/* ———————————————————————————————————————————————— */

	// initialise the main firmlink array
	uint16_t fl_alloced = INIT_FLN_COUNT;
	FIRMLINKS = ecalloc((size_t)fl_alloced, sizeof(char*));

	/* ———————————————————————————————————————————————— */

	// allocate some memory in which the section parsed by `getdelim` will go
	//	this has to be heap memory, since `getdelim` will realloc `sec_buf` to make sure it always has enough space
	size_t sec_bufsize = INIT_LN_BUFSIZE;
	char *sec_buf = emalloc(sec_bufsize);

	// initialise the section length to be `-1`, so if errors occur on the first iteration, they're caught correctly
	ssize_t sec_len = EOF;

	/* ———————————————————————————————————————————————— */

	// the `/usr/share/firmlinks` file is mapped with a pair of system and data filepaths per line,
	//	with the filepaths separated with a tab (`\t`), and the lines separated by newline (`\n`)
	// we therefore read the file in system and data sections, and compare the system section with the file's realpath
	char delim = SYST_MODE_DELIM;

	while (( sec_len = getdelim(&sec_buf, &sec_bufsize, delim, p_flink) ) != EOF) {
		// `getdelim` keeps the trailing delimiter, so remove it if it exists
		if (sec_buf[sec_len - 1] == delim) sec_buf[sec_len - 1] = '\0';

		delim = SWAP_DELIMS(); // swap the delimiters around for the next iteration

		// if, after being swapped, the delimiter is in system mode, then we were in data mode before we swapped
		//	since we don't care about the information in the data section, we can just continue
		if (delim == SYST_MODE_DELIM) continue;

		// reallocate memory if we're about to go over what we've already allocated
		if (fl_count + 1 > fl_alloced) {
			FIRMLINKS = erealloc(FIRMLINKS, (size_t)MULT_BY_1_5(fl_alloced) * sizeof(char*));
		}

		// since we already know `sec_len`, we don't have to use `strdup`, and can do everything manually instead:
		//	- allocate memory for the firmlink (including the nullbyte),
		//	- then copy `sec_buf` into the newly-allocated firmlink buffer,
		//	- then add the firmlink_buf pointer to the main `FIRMLINKS` array
		FIRMLINKS[fl_count++] = memcpy(emalloc(sec_len), sec_buf, sec_len);
	}

	// if `getdelim` changes the pointer to `sec_buf` when calling `realloc`, it'll put the new pointer
	//	back into `sec_buf`, so this should be safe to free
	efree(sec_buf);
	return ( success = true );
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void freeFirmlinks(void) {
	if (p_flink == NULL) return;
	fclose(p_flink);

	if (FIRMLINKS == NULL) return;
	for (uint16_t i = 0; i < fl_count; i++) {
		if (FIRMLINKS[i] != NULL) efree(FIRMLINKS[i]);
	}

	efree(FIRMLINKS);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void checkFirmlink(FileStat *const pFS) {
	// only directories can be firmlinks, so there's no point in checking anything else
	if (!S_ISDIR(pFS->mode)) return;

	// make sure the firmlinks array is initialised
	if (!initFirmlinks()) return; // if we weren't able to get all the the data we needed, return

	// get the absolute path to the file we're checking, since that's how they're stored in the lookup file
	path_t abs_path = {0};
	if (realpath(pFS->name, abs_path) == NULL) return;

	// iterate through each firmlink we've stored
	for (uint16_t i = 0; i < fl_count; i++) {
		if (strcmp(FIRMLINKS[i], abs_path) == 0) { // if the firmlink's path matches our file's path
			pFS->s->st_flags |= SF_FIRMLINK; // then add the firmlink flag to the file's flags
			break; // no more processing to be done
		}
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DO_FIRMLINKS() /*temp*/ true

#define GET_FLAG_NAME(flag) \
	(DO_TINY_FLAGS() ? (flag).tiny_name : ( \
		DO_SHORT_FLAGS() ? (flag).short_name : (flag).name \
	))

char *parseFlags(FileStat *const pFS) {
	/// @todo implement the `--check-firmlinks` option
	if (DO_FIRMLINKS()) checkFirmlink(pFS);

	if (pFS->s->st_flags == 0) {
		// make sure that we note down the size of the string
		//	which will be displayed if there aren't any flags
		setLen(FI_flag_str, sizeof(NO_FLAG_STR) - 1);
		return (char*)NULL;
	}

	flagstr flag_str = {0};
	bool is_first = true;

	uint8_t str_len = 0U;
	size_t flag_len;
	flagset flag;

	for (int i = 0; i < MAX_FLAG_NUM; i++) {
		flag = ALL_FLAGS[i];

		if (pFS->s->st_flags & flag.mask) {
			if (!is_first) flag_str[str_len++] = FLAG_SEP_CHR;
			is_first = false;

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
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// Rounds a number down to the nearest 4.
#define ROUND_DOWN_TO_4(num) ((num) & ~3)
/// Strip the trailing zeros from a hexadecimal number
#define STRIP_TZ_HEX(num) (num) >> ROUND_DOWN_TO_4(__builtin_ctz((num)))

void print_flags(const FileStat *const pFS) {
	const bool valid = pFS->s != NULL && pFS->s->st_flags != 0;
	if (!valid) {
		printf("%s%*c%ls", getcol(PUNCT), getLen(FI_flags), '-', FIELD_PAD);
		return;
	}

	flag_t hex_out[FLAG_COUNT] = {0};
	Colour colours[FLAG_COUNT] = {0};

	for (int i = 0; i < FLAG_COUNT; i++) {
		const flag_t mask = ALL_FLAGS[i].mask;
		if (!(pFS->s->st_flags & mask)) continue;

		const int trailing_0s = ROUND_DOWN_TO_4(__builtin_ctz(mask));

		hex_out[trailing_0s >> 2] += (mask >> trailing_0s);
		colours[trailing_0s >> 2] =  (ALL_FLAGS[i].colour);
	}

	for (int i = FLAG_COUNT - getLen(FI_flags); i < FLAG_COUNT; i++) {
		const int get_idx = FLAG_COUNT - (i + 1);

		Colour colour = colours[get_idx];
		if (!areEqual(colour, RESET_ALL)) colour.style |= G_BOLD;

		printf("%s%x%ls", getcol(colour), hex_out[get_idx], (i + 1 == FLAG_COUNT) ? FIELD_PAD : L"");
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_flag_str(const FileStat *const pFS) {
	if (pFS->s == NULL || pFS->s->st_flags == 0) {
		printf("%s%-*s%ls", getcol(PUNCT), getLen(FI_flag_str), NO_FLAG_STR, FIELD_PAD);
		return;
	}

	char output[512] = {0};
	char *out_ptr = output;
	const char *flag, *colour;
	uint8_t flag_len = 0, col_len = 0, flagstr_len = 0;

	bool is_first = true;

	for (int flag_i = 0; flag_i < MAX_FLAG_NUM; flag_i++) {
		if (!(pFS->s->st_flags & ALL_FLAGS[flag_i].mask)) continue;

		flag = GET_FLAG_NAME(ALL_FLAGS[flag_i]);
		flag_len = (uint8_t)strlen(flag);

		if (!is_first) {
			colour = getcollen(PUNCT, &col_len);
			memcpy(out_ptr, colour, col_len);
			out_ptr += col_len;

			*out_ptr++ = FLAG_SEP_CHR;
			flagstr_len++;
		}

		is_first = false;

		colour = getcollen(ALL_FLAGS[flag_i].colour, &col_len);
		memcpy(out_ptr, colour, col_len);
		out_ptr += col_len;

		memcpy(out_ptr, flag, flag_len);
		out_ptr += flag_len;
		flagstr_len += flag_len;
	}

	*out_ptr++ = '\0';

	const int spaces = getLen(FI_flag_str) - (int)flagstr_len;
	printf("%s%*s" "%s%ls",
		output, spaces, "",
		has_bg(ALL_FLAGS[MAX_FLAG_NUM - 1].colour) ? getcol(RESET_ALL) : "",
		FIELD_PAD
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegExp /, "\w+"/g
