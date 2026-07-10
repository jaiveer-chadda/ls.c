/// @file output/print-mode.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../form/formatting.h"
#include "../options/options.h"

#define IF_COLOUR(print) (DO_COLOUR() ? (print) : "")

#define IS_REG() (str[0] == REGULAR_CHAR)	/// Whether the file is a regular file or not.
#define IS_UID() (i == 3) /// `3` is the index of the SUID bit in the mode string.
#define IS_OTH() (i == 8) /// `8` is the index of the `other-writable` bit in the mode string.

#define ESCS_ARE_EQUAL(esc_1, esc_2)			\
	((esc_1 == esc_2) ||						\
		esc_1 != PC_COUNT && esc_2 != PC_COUNT	\
		&& strcmp(perm_colour_esc[esc_1], perm_colour_esc[esc_2]) == 0)

void printModeStr(const modestr str, const bool has_acl, const bool has_xattr) {
	if (!do_mode_str()) return;

	// ( bit count `= 10` )  ×  ( max hl len `= 11` )
	char output[10 * 11] = "";
	FileColour type = FC_COUNT;

	if (DO_COLOUR()) {
		// the first char will always be the filetype
		//  colour it in accordance with how the file itself will be highlighted
		switch (str[0]) {
			case REGULAR_CHAR	: type = FC_REGULAR	; break;
			case DIR_CHAR		: type = FC_DIRECT	; break;
			case SYMLINK_CHAR	: type = FC_SYMLINK	; break;
			case PIPE_CHAR		: type = FC_PIPE	; break;
			case SOCKET_CHAR	: type = FC_SOCKET	; break;
			case CHRDEV_CHAR	: type = FC_CHR_DEV	; break;
			case BLKDEV_CHAR	: type = FC_BLK_DEV	; break;
			case WHITEOUT_CHAR	: type = FC_WHITEOUT; break;
		}

		char *tmp_output = malloc(sizeof(output));

		sprintf(tmp_output, "%s%s%s%s", output, CSI, file_colour_esc[type], END);
		strcpy(output, tmp_output);

		free(tmp_output);
	}

	output[strlen(output)	 ] = str[0];
	output[strlen(output) + 1] = '\0';

	PermColour last_esc, esc = PC_COUNT;

	for (int i = 1; i < MODE_STR_LEN; i++) {
		if (DO_COLOUR()) {
			last_esc = esc;

			switch (str[i]) {
				// this permission bit isn't set
				case NO_PERM_CHAR		: esc = PC_NONE; break;

				// any of the 3 `read` bits
				case READ_BIT_CHAR		: esc = PC_READ; break;
				// colour the usr and grp write bits one colour, and the other-write bit another colour
				case WRITE_BIT_CHAR		: esc = IS_OTH() ? PC_W_OTHER : PC_W_USRGRP; break;
				// colour the exec bit based on whether the file is a regular file or not
				case EXEC_BIT_CHAR		: esc = IS_REG() ? PC_X_REG	: PC_X_NREG; break;

				// colour the UID and GID bits based on whether they're executable or not
				//  and run `IS_UID()` to determine if we're currently looking at the usr or group bit
				case SUGID_X_BIT_CHAR	: esc = IS_UID() ? PC_SUID_X : PC_SGID_X; break;
				case SUGID_N_BIT_CHAR	: esc = IS_UID() ? PC_SUID_N : PC_SGID_N; break;

				// colour the sticky bit based on whether the files is executable or not
				case STICKY_X_BIT_CHAR	: esc = PC_STICKY_X	; break;
				case STICKY_N_BIT_CHAR	: esc = PC_STICKY_N	; break;
			}

			// only print an escape if the previous one wasn't the exact same
			// this'll just save on unnecessary escape printing
			if (!ESCS_ARE_EQUAL(last_esc, esc)) strcat(output, perm_colour_esc[esc]);
		}

		output[strlen(output)] = str[i];
	}

	printf("%s", output);

	int spaces = (int)(field_lengths.mode_str - strlen(str));

	if (has_xattr)	{ printf("%s%c", IF_COLOUR(XATTR_COLOUR	), XATTR_CHAR); spaces-- ; }
	if (has_acl)	{ printf("%s%c", IF_COLOUR(ACL_COLOUR	), ACL_CHAR	 ); spaces-- ; }

	printf("%s" "%*s" "%s",
		IF_COLOUR(RESET),
		spaces, "",
		FIELD_PAD
	);
}
