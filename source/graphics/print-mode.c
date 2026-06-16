/// @file graphics/print-mode.c

#include <stdio.h>
#include <string.h>

#include "../model/stat-model.h"
#include "../options/options.h"
#include "graphics.h"

inline void printModeStr(const modestr str) {
	if (!do_mode_str) return;

	char output[128] = "";

	FileColour type = -1;

	switch (str[0]) {
		case PIPE_CHAR:		type = PIPE		; break;
		case CHRDEV_CHAR:	type = CHR_DEV	; break;
		case DIR_CHAR:		type = DIRECT	; break;
		case BLKDEV_CHAR:	type = BLK_DEV	; break;
		case REGULAR_CHAR:	type = REGULAR	; break;
		case SYMLINK_CHAR:	type = SYMLINK	; break;
		case SOCKET_CHAR:	type = SOCKET	; break;
		case WHITEOUT_CHAR:	type = WHITEOUT	; break;
	}

	strcat(output, file_colour_esc[type]);
	
	output[strlen(output)] = str[0];
	output[strlen(output) + 1] = '\0';

	PermColour esc = -1, last_esc;

	for (int i = 1; i < MAX_MODE_LEN - 1; i++) {
		last_esc = esc;

		switch (str[i]) {
			case '-': esc = NONE; break;
			case 'r': esc = READ; break;
			case 't': esc = STICKY_X; break;
			case 'T': esc = STICKY_N; break;
			case 's': esc = i == 3 ? SUID_X : SGID_X; break;
			case 'S': esc = i == 3 ? SUID_N : SGID_N; break;
			case 'w': esc = i == 8 ? W_OTHER : W_USRGRP; break;
			case 'x': esc = str[0] == '.' ? X_REG : X_NREG; break;
		}

		if (last_esc != esc) strcat(output, perm_colour_esc[esc]);

		output[strlen(output)] = str[i];
		output[strlen(output) + 1] = '\0';
	}

	printf("%s%s  ", output, RESET);
}
