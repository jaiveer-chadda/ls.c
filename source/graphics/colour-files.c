/// @file graphics/colour-files.c

#include "../model/stat-model.h"
#include "../features/mode/mode.h"

#include "graphics.h"

void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags) {
	if (flags & SF_DATALESS) { *colour = DATALESS; return; }
	if (mode & EXEC_MASK) *colour = EXEC;

	switch (mode & TYPE_MASK) {
		case S_IFIFO:	*colour = PIPE		; return; // named pipe
		case S_IFCHR:	*colour = CHR_DEV	; return; // char device
		case S_IFBLK:	*colour = BLK_DEV	; return; // block device
		case S_IFLNK:	*colour = SYMLINK	; return; // symbolic link
		case S_IFSOCK:	*colour = SOCKET	; return; // socket
		case S_IFWHT:	*colour = WHITEOUT	; return; // whiteout
	}

	if ((mode & TYPE_MASK) == S_IFDIR) {
		if (mode & S_ISVTX) { *colour = STICKY; return; } // directory w/ sticky bit
		if (mode & S_IWOTH) { *colour = OW_DIR; return; } // other-writeable directory
		/**/				  *colour = DIRECT; return;   // regular directory
	}

	if (mode & S_ISUID) { *colour = SUID; return; } // file w/ setuid bit
	if (mode & S_ISGID) { *colour = SGID; return; } // file w/ setgid bit
}
