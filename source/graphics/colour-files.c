/// @file graphics/colour-files.c

#include "../model/stat-model.h"
#include "../features/mode/mode.h"

#include "graphics.h"

void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags) {

	switch (mode & TYPE_MASK) {
		case S_IFREG:					; break; // regular file
		case S_IFIFO: *colour = PIPE	; break; // named pipe
		case S_IFCHR: *colour = CHR_DEV	; break; // char device
		case S_IFBLK: *colour = BLK_DEV	; break; // block device
		case S_IFLNK: *colour = SYMLINK	; break; // symbolic link
		case S_IFSOCK:*colour = SOCKET	; break; // socket
		case S_IFWHT: *colour = WHITEOUT; break; // whiteout

		case S_IFDIR:							 // directory
			if		(mode & S_ISVTX) *colour = STICKY;
			else if	(mode & S_IWOTH) *colour = OW_DIR;
			else					 *colour = DIRECT;
			break;
	}

}
