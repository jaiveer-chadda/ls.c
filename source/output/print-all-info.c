/// @file output/print-all-info.c

#include <stdio.h>
#include <string.h>

#include "../form/formatting.h"
#include "../options/options.h"
#include "../graphics/graphics.h"
#include "../features/mode/mode.h"

#include "output.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PRINT_FIELD(field)									\
	if ((do_##field())) {									\
		sprintf(fmt_str, "%s%%s", (fmt_strs_long.field));	\
		printf(fmt_str,										\
			(int)(field_lengths.field), (file.field),		\
			FIELD_PAD										\
		);													\
	}

#define COLOUR(field, colour_func) if (DO_COLOUR()) { colour_func; } else { PRINT_FIELD(field); }

/* ——————————————————————————————————————————————————————————————————————————— */

#define PRINT_TIME_STR()								\
	COLOUR(time_str,									\
		sprintf(fmt_str, "%%s%s%s",						\
			fmt_strs_long.time_str, RESET FIELD_PAD		\
		);												\
		printf(fmt_str,									\
			time_colour_esc[file.time_col],				\
			(int)field_lengths.time_str, file.time_str	\
		);												\
	)

#define PRINT_FLAG_STR() COLOUR(flag_str, printFlagStr(	&(file.flags)											))
#define PRINT_USR_NAME() COLOUR(usr_name, printUsrName(	&(file.uid)		,	file.usr_name	, &(file.is_valid)	))
#define PRINT_GRP_NAME() COLOUR(grp_name, printGrpName(	&(file.gid)		,	file.grp_name	, &(file.is_valid)	))
#define	   PRINT_NLINK() COLOUR(nlink	,	printNLink(	&(file.nlink)	, &(file.mode)							))
#define PRINT_SIZE_STR()				  printSizeStr(	  file.size_str	, &(file.size_unit)	, &(file.mode)		 )
#define PRINT_MODE_STR()				  printModeStr(	  file.mode_str	,	file.has_acl	,	file.has_xattr	 )

/* ——————————————————————————————————————————————————————————————————————————— */

inline void printFields(const FileInfo *all_files, const int *count) {
	char fmt_str[16];

	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];

		PRINT_FIELD(inode);	PRINT_FIELD(dev_no);
		PRINT_FIELD(mode);	PRINT_MODE_STR();

		PRINT_NLINK();
		PRINT_FIELD(size);	PRINT_SIZE_STR();
		PRINT_FIELD(uid);	PRINT_USR_NAME();
		PRINT_FIELD(gid);	PRINT_GRP_NAME();
		PRINT_FIELD(flags);	PRINT_FLAG_STR();
		PRINT_FIELD(time);	PRINT_TIME_STR();

		printName(file.name, &(file.file_col), &(file.do_link_hl), &(file.flags), &(file.suffix));

		if (do_suffix() && file.suffix != '\0') printf("%c", file.suffix);

		printSymlink(file.link_to, file.ln_suf, file.link_col);
		printf("%s", "\n");
	}
}

#undef COLOUR

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
