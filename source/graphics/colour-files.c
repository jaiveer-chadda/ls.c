/// @file graphics/colour-files.c

#include "../model/stat-model.h"
#include "../features/mode/mode.h"

#include "graphics.h"

inline void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags) {
	if (flags & SF_DATALESS) { *colour = FC_DATALESS; return; }
	if (mode & EXEC_MASK) *colour = FC_EXEC;

	switch (mode & TYPE_MASK) {
		case S_IFIFO:	*colour = FC_PIPE		; return; // named pipe
		case S_IFCHR:	*colour = FC_CHR_DEV	; return; // char device
		case S_IFBLK:	*colour = FC_BLK_DEV	; return; // block device
		case S_IFLNK:	*colour = FC_SYMLINK	; return; // symbolic link
		case S_IFSOCK:	*colour = FC_SOCKET		; return; // socket
		case S_IFWHT:	*colour = FC_WHITEOUT	; return; // whiteout
	}

	if ((mode & TYPE_MASK) == S_IFDIR) {
		if (mode & S_ISVTX) { *colour = FC_STICKY_X	; return; } // directory w/ sticky bit
		if (mode & S_IWOTH) { *colour = FC_OW_DIR	; return; } // other-writeable directory
		/**/				  *colour = FC_DIRECT	; return;   // regular directory
	}

	if (mode & S_ISUID) { *colour = FC_SUID_X; return; } // file w/ setuid bit
	if (mode & S_ISGID) { *colour = FC_SGID_X; return; } // file w/ setgid bit
}
