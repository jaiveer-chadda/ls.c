/// @file graphics/colour-files.c

#include "../model/stat-model.h"
#include "../features/mode/mode.h"

#include "graphics.h"

#define	GET_STICKY_COLOUR(mode) (((mode) & S_IXOTH) ? FC_STICKY_X : FC_STICKY_N)
#define	  GET_SUID_COLOUR(mode) (((mode) & S_IXUSR) ? FC_SUID_X	  : FC_SUID_N  )
#define	  GET_SGID_COLOUR(mode) (((mode) & S_IXGRP) ? FC_SGID_X	  : FC_SGID_N  )

inline void setFileColour(FileColour *colour, const mode_t mode, const flag_t flags, const dev_t dev_no) {
	// `dataless` has the highest priority, so if the file is dataless, colour it and return immediately
	if (flags & SF_DATALESS) { *colour = FC_DATALESS; return; }
	
	// `mount point` has the 2ⁿᵈ highest priority
	if (dev_no != root_dev_no && root_dev_no != -1) { *colour = FC_MOUNT; return; }

	// `exec` has the lowest priority, so set the colour to exec, but it can be overwritten by anything else below
	if (mode & EXEC_MASK) *colour = FC_EXEC;

	// colour the file based on its type - filetype has the next highest priority after dataless
	switch (mode & TYPE_MASK) {
		case S_IFIFO:	*colour = FC_PIPE		; return; // named pipe
		case S_IFCHR:	*colour = FC_CHR_DEV	; return; // char device
		case S_IFBLK:	*colour = FC_BLK_DEV	; return; // block device
		case S_IFLNK:	*colour = FC_SYMLINK	; return; // symbolic link
		case S_IFSOCK:	*colour = FC_SOCKET		; return; // socket
		case S_IFWHT:	*colour = FC_WHITEOUT	; return; // whiteout
		case S_IFDIR:									  // directories
			if		(mode & S_ISVTX) *colour = GET_STICKY_COLOUR(mode);	// directory w/ sticky bit set
			else if (mode & S_IWOTH) *colour = FC_OW_DIR;				// other-writeable directory
			else					 *colour = FC_DIRECT;				// regular directory
			return;
	}

	// finally, colour the file based on the suid/sgid bits
	// note: directories with the suid/sgid bit are intentionally not coloured by these suid/sgid colours
	if (mode & S_ISUID) { *colour = GET_SUID_COLOUR(mode); return; } // file w/ suid bit set
	if (mode & S_ISGID) { *colour = GET_SGID_COLOUR(mode); return; } // file w/ sgid bit set
}
