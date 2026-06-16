/// @file model/stat-model.h

#ifndef STAT_MODEL_INITIALISED
#define STAT_MODEL_INITIALISED

#include "types.h"
#include "../graphics/graphics.h"

typedef struct {
	name_t	name	;
	type_t	suffix	;

	path_t	link_to ;
	type_t	ln_suf	;

	nlink_t	nlink	;
	dev_t	dev_no	;	ino_t	inode	;

	flag_t	flags	;	flagstr flag_str;
	mode_t	mode	;	modestr mode_str;
	off_t	size	;	sizestr size_str;	char size_unit;

	uid_t	uid		;	ugidstr usr_name;
	gid_t	gid		;	ugidstr grp_name;

	time_t	time	;	timestr time_str;

	FileColour file_col;
	TimeColour time_col;

	bool do_hardlink_hl;

} FileInfo;

#endif /* !STAT_MODEL_INITIALISED */
