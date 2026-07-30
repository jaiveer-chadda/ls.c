/// @file graphics/colour-files.c

#include <stdio.h>
#include <string.h>

#include "../model/stat-model.h"
#include "../features/mode/mode.h"

#include "graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:disable
static const char  *ALL_COMPRESSED_EXTS[] = {
	"7z" , "ace", "alz", "apk", "arc", "arj", "bz" , "bz2" , "cab", "cpio", "crate", "deb", "drpm", "dwm" , "dz"  ,
	"ear", "egg", "esd", "gz" , "jar", "lha", "lrz", "lz"  , "lz4", "lzh" , "lzma" , "lzo", "pyz" , "rar" , "rpm" ,
	"rz" , "sar", "swm", "t7z", "tar", "taz", "tbz", "tbz2", "tgz", "tlz" , "txz"  , "tz" , "tzo" , "tzst", "udeb",
	"war", "whl", "wim", "xz" , "z"  , "zip", "zoo", "zst" , "dmg"
};
static const char 		*ALL_IMAGE_EXTS[] = {
	"avif", "bmp", "gif", "jpeg", "jpg", "mjpeg", "mjpg", "png", "svg", "svgz", "tif", "tiff", "webm", "webp", "jxl",
	"pbm" , "pgm", "ppm", "tga" , "xbm", "xpm"  , "mng" , "pcx", "xcf", "xwd" , "cgm", "emf"
};
static const char 		*ALL_VIDEO_EXTS[] = {
	"m2v", "m4v", "mov", "mp4", "mp4v", "mpg", "mpeg", "ogm", "qt", "mkv", "vob", "nuv", "wmv", "asf", "rm", "rmvb",
	"flc", "fli", "avi", "flv", "gl"  , "dl" , "yuv" , "ogv"
};
static const char  *ALL_AUDIO_UNCM_EXTS[] = { "au" , "flac", "m4a", "mid", "midi", "mka", "wav" , "xspf"	  };
static const char  *ALL_AUDIO_COMP_EXTS[] = { "aac", "mp3" , "mpc", "oga", "ogg" , "ogx", "opus", "ra", "spx" };
static const char 	*ALL_TEMP_BACK_EXTS[] = {
	"tmp", "swp", "old" , "part"  , "rpmsave", "rpmorig", "dpkg-tmp", "ucf-dist", "dpkg-dist" ,
	"rej", "bak", "orig", "rpmnew", "ucf-old", "ucf-new", "dpkg-old", "dpkg-new", "crdownload",
};
// spell:enable

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define	GET_STICKY_COLOUR(mode) (((mode) & S_IXOTH) ? FC_STICKY_X : FC_STICKY_N	)
#define	  GET_SUID_COLOUR(mode) (((mode) & S_IXUSR) ? FC_SUID_X	  : FC_SUID_N	)
#define	  GET_SGID_COLOUR(mode) (((mode) & S_IXGRP) ? FC_SGID_X	  : FC_SGID_N	)

#define GET_ARR_LEN(array) (int)(sizeof(array) / sizeof((array)[0]))

#define CHECK_EXTENSION_TYPE(type)			\
	if (strInArr(extension + 1,				\
		ALL_ ## type ## _EXTS,				\
		GET_ARR_LEN(ALL_ ## type ## _EXTS))	\
	) {										\
		*colour = FC_ ## type;				\
		return;								\
	}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline bool strInArr(const char *string, const char *array[], const int arr_len) {
	for (int i = 0; i < arr_len; i++) {
		if (strcmp(array[i], string) == 0) return true;
	}
	return false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void setFileColour(FileColour *colour, const name_t name, const mode_t mode, const flag_t flags, const bool is_mount) {

	/* —— Flags ————————————————————————————————————————————————— */

	// dataless files have the highest priority, so if the file is dataless, colour it and return immediately
	if (flags & SF_DATALESS) { *colour = FC_DATALESS; return; }

	/* —— Type —————————————————————————————————————————————————— */

	// colour the file based on its type - filetype has the next highest priority after dataless
	switch (mode & TYPE_MASK) {
		case S_IFIFO:	*colour = FC_PIPE		; return; // named pipe
		case S_IFCHR:	*colour = FC_CHR_DEV	; return; // char device
		case S_IFBLK:	*colour = FC_BLK_DEV	; return; // block device
		case S_IFLNK:	*colour = FC_SYMLINK	; return; // symbolic link
		case S_IFSOCK:	*colour = FC_SOCKET		; return; // socket
		case S_IFWHT:	*colour = FC_WHITEOUT	; return; // whiteout

		/* —— Permissions ——————————————————————————————————————— */

		case S_IFDIR:									  // directories
			if		(mode & S_ISVTX) *colour = GET_STICKY_COLOUR(mode);	// directory w/ sticky bit set
			else if (mode & S_IWOTH) *colour = FC_OW_DIR;				// other-writeable directory
			else if (is_mount)		 *colour = FC_MOUNT;				// mount point
			else					 *colour = FC_DIRECT;				// regular directory
			return;

		default: break;
	}

	// colour the file based on the suid/sgid bits
	// note: directories with the suid/sgid bit are intentionally not coloured by these suid/sgid colours
	if (mode & S_ISUID) { *colour = GET_SUID_COLOUR(mode); return; } // file w/ suid bit set
	if (mode & S_ISGID) { *colour = GET_SGID_COLOUR(mode); return; } // file w/ sgid bit set

	if (mode & EXEC_MASK) { *colour = FC_EXEC; return; } // executable file

	/* —— Regular File —————————————————————————————————————————— */

	// file is a regular file
	*colour = FC_REGULAR;

	/* —— Specific Filenames ———————————————————————————————————— */

	const size_t name_len = strlen(name);

	// if a file ends with a `~` or `#`, then it's a temporary file
	if (name[name_len] == '~' || name[name_len] == '#') {
		*colour = FC_TEMP_BACK;
		return;
	}

	/* —— Extensions ———————————————————————————————————————————— */

	const char* extension = strrchr(name, '.');
	if (extension == name || extension == NULL) return;

	CHECK_EXTENSION_TYPE(COMPRESSED);
	CHECK_EXTENSION_TYPE(IMAGE);
	CHECK_EXTENSION_TYPE(VIDEO);
	CHECK_EXTENSION_TYPE(AUDIO_UNCM);
	CHECK_EXTENSION_TYPE(AUDIO_COMP);
	CHECK_EXTENSION_TYPE(TEMP_BACK);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
