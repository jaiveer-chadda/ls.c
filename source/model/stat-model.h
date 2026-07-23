/// @file model/stat-model.h

#ifndef STAT_MODEL_INITIALISED
#define STAT_MODEL_INITIALISED

#include "types.h"
#include "../graphics/graphics.h"

extern path_t G_DOTDIR_PATH;

typedef struct {
	/// Whether we were able to `stat` the file or not.
	bool		is_valid	; // bool				-	 1

	bool		do_link_hl	; // bool				-	 1
	bool		has_xattr	; // bool				-	 1
	bool		is_mount	; // bool				-	 1
	bool		has_acl		; // bool				-	 1

	suff_t		suffix		; // char				-	 1
	suff_t		ln_suf		; // char				-	 1
	unit_t		size_unit	; // char				-	 1

	nlink_t		nlink		; // unsigned short		-	 2
	mode_t		mode		; // unsigned short		-	 2

	flag_t		flags		; // unsigned int		-	 4

	dev_t		dev_no		; // int				-	 4
	dev_t		rdev		; // int				-	 4

	uid_t		uid			; // unsigned int		-	 4
	gid_t		gid			; // unsigned int		-	 4

	FileColour	file_col	; // int				-	 4
	FileColour	link_col	; // int				-	 4
	TimeColour	time_col	; // int				-	 4

	time_t		time		; // long				-	 8
	link_t		link_to		; // char*				-	 8
	off_t		size		; // long long			-	 8
	ino_t		inode		; // unsigned long long	-	 8

	sizestr		size_str	; // char[10]			-	10
	modestr		mode_str	; // char[11]			-	11
	timestr		time_str	; // char[32]			-	32
	ugidstr		usr_name	; // char[32]			-	32
	ugidstr		grp_name	; // char[32]			-	32

	flagstr		flag_str	; // char[168]			-  168
	name_t		name		; // char[255]			-  255
} FileInfo;

#endif /* !STAT_MODEL_INITIALISED */
