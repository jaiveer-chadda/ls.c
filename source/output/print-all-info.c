/// @file output/print-all-info.c

#include <stdio.h>
#include <string.h>

#include "icons/icons.h"
#include "form/formatting.h"
#include "options/options.h"
#include "graphics/graphics.h"
#include "debugging.h"
#include "features/mount/mount-point.h"

#include "output.h"

typedef unsigned int u_int;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// If colour is disabled, print `field` as normal, otherwise, run `colour_func`.
#define COLOUR(field, colour_func) if (DO_COLOUR()) { colour_func; } else { PRINT_FIELD(field); }

/// Whether a symlink target path should be printed after the filename.
#define DO_SYMLINK() (do_link_to() && (file.ln_suf != NOT_LINK))

/// Get the appropriate format string based on whether a file has a normal or majmin size.
#define GET_SIZE_FMT() (file.rdev == 0 ? fmt_strs_long.size : fmt_strs_long.majmin)

/* —————————————————————————————————————————————————————————————————————————————————————————————— */

/// A macro which, like with the field lengths, should be able to print most fields in the correct format.
#define PRINT_FIELD(field)									\
	if ((do_ ## field())) {									\
		sprintf(fmt_str, "%s%%s", (fmt_strs_long.field));	\
		printf(fmt_str,										\
			(int)(field_lengths.field), (file.field),		\
			FIELD_PAD										\
		);													\
	}

/* —————————————————————————————————————————————————————————————————————————————————————————————— */

/// `size_str` is once again an exception due to the possibility of having a majmin size.
#define PRINT_SIZE()									\
	if (do_size()) {									\
		sprintf(fmt_str, "%s%%s", GET_SIZE_FMT());		\
		printf(fmt_str,									\
			(int)field_lengths.size, (u_int)file.size,	\
			FIELD_PAD									\
		);												\
	}

/* —————————————————————————————————————————————————————————————————— */

/// `time` and `time_str` are also exceptions, since the colour for each time is stored in the `FileInfo` struct.
#define PRINT_TIME(field)									\
	if (do_ ## field()) {									\
		COLOUR(field,										\
			sprintf(fmt_str, "%%s%%s%%s" "%s%s%s",			\
				fmt_strs_long.field, RESET, FIELD_PAD		\
			);												\
			printf(fmt_str,									\
				CSI_FG, time_colour_esc[file.time_col], END,\
				(int)field_lengths.field, file.field		\
			);												\
		)													\
	}

/* —————————————————————————————————————————————————————————————————————————————————————————————— */

/// The following macros are all exceptions to the standard `PRINT_FIELD` macro,
///	 since they all have custom functions which handle their printing.
#define PRINT_FLAG_STR() COLOUR(flag_str, printFlagStr(	&(file.flags)											))
#define PRINT_USR_NAME() COLOUR(usr_name, printUsrName(	&(file.uid)		,	file.usr_name	, &(file.is_valid)	))
#define PRINT_GRP_NAME() COLOUR(grp_name, printGrpName(	&(file.gid)		,	file.grp_name	, &(file.is_valid)	))
#define	   PRINT_NLINK() COLOUR(nlink	,	printNLink(	&(file.nlink)	, &(file.mode)							))
#define PRINT_SIZE_STR()				  printSizeStr(	  file.size_str	, &(file.size_unit)	, &(file.mode)		 )
#define PRINT_MODE_STR()				  printModeStr(	  file.mode_str	,	file.has_acl	,	file.has_xattr	 )

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
#	define ff fflush(stdout)
#else
#	define ff
#endif

inline void printFields(const FileInfo *all_files, const int *count) {
	/// The `printf` format string that'll be used to construct a field's output.
	char fmt_str[16];

	for (int i = 0; i < *count; i++) {
		FileInfo file = all_files[i];

		// print each of the fields in order
		PRINT_FIELD(inode)	; ff; PRINT_FIELD(dev_no)	; ff; 
		PRINT_FIELD(mode)	; ff; PRINT_MODE_STR()		; ff; 

		PRINT_NLINK()		; ff;
		PRINT_SIZE()		; ff; PRINT_SIZE_STR()		; ff; 
		PRINT_FIELD(uid)	; ff; PRINT_USR_NAME()		; ff; 
		PRINT_FIELD(gid)	; ff; PRINT_GRP_NAME()		; ff; 
		PRINT_FIELD(flags)	; ff; PRINT_FLAG_STR()		; ff; 
		PRINT_TIME (time)	; ff; PRINT_TIME(time_str)	; ff; 

		if (do_icon()) printIcon(file.icon, file.file_col);

		// print the file's name and its suffix (if enabled)
		printName(file.name, &file.file_col, &file.do_link_hl, &file.flags, &file.suffix);
		if (do_suffix() && file.suffix != '\0') { putchar(file.suffix); ff; }

		// next, if the file's a symlink, print the pointed-to path
		if (DO_SYMLINK()) { printSymlink(file.link_to, file.ln_suf, file.link_col, file.is_ln_apple); ff; }

		// then, if the file's a mount point, print some information about the mount
		if (DO_MOUNTDEV() && file.is_mount) { printMountDevice(file.name); ff; }

		// finally, print a newline and move onto the next file
		putchar('\n');
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
