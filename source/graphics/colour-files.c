/// @file graphics/colour-files.c

#include "../model/stat-model.h"
#include "../features/mode/mode.h"

#include "graphics.h"

inline void setFileColour(FileColour *col, const mode_t mode, const flag_t flags) {
	if (flags & SF_DATALESS) {	*col = FC_DATALESS; return; }
	if (mode & EXEC_MASK)		*col = FC_EXEC;

	switch (mode & TYPE_MASK) {
		case S_IFIFO:	*col = FC_PIPE		; return; // named pipe
		case S_IFCHR:	*col = FC_CHR_DEV	; return; // char device
		case S_IFBLK:	*col = FC_BLK_DEV	; return; // block device
		case S_IFLNK:	*col = FC_SYMLINK	; return; // symbolic link
		case S_IFSOCK:	*col = FC_SOCKET	; return; // socket
		case S_IFWHT:	*col = FC_WHITEOUT	; return; // whiteout
	}

	if (mode & S_IFDIR) {
		if		(mode & S_ISVTX) *col = (mode & S_IXOTH) ? FC_STICKY_X : FC_STICKY_N;	// directory w/ sticky bit
		else if (mode & S_IWOTH) *col = FC_OW_DIR;										// other-writeable directory
		else					 *col = FC_DIRECT;										// regular directory

		return;
	}

	if (mode & S_ISUID) { *col = (mode & S_IXUSR) ? FC_SUID_X : FC_SUID_N; return; } // file w/ setuid bit
	if (mode & S_ISGID) { *col = (mode & S_IXGRP) ? FC_SGID_X : FC_SGID_N; return; } // file w/ setgid bit
}
