/// @file parsing/parse-file.c

#include <assert.h>

#include "malloc.h"
#include "debugging.h"
#include "parse-file.h"

#include "model/types.h"
#include "options/options.h"

#include "icons/icons.h"
#include "features/mode/mode.h"
#include "features/size/size.h"
#include "features/time/time.h"
#include "features/ugid/ugid.h"
#include "features/flags/flags.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef NOT_DEFINED
	dev_t				st_dev;				/* [XSI] ID of device containing file */
	mode_t				st_mode;			/* [XSI] Mode of file (see below) */
	nlink_t				st_nlink;			/* [XSI] Number of hard links */
	__darwin_ino64_t	st_ino;				/* [XSI] File serial number */
	uid_t				st_uid;				/* [XSI] User ID of the file */
	gid_t				st_gid;				/* [XSI] Group ID of the file */
	dev_t				st_rdev;			/* [XSI] Device ID */
	struct timespec		st_atimespec;		/* time of last access */
	struct timespec		st_mtimespec;		/* time of last data modification */
	struct timespec		st_ctimespec;		/* time of last status change */
	struct timespec		st_birthtimespec;	/* time of file creation(birth) */
	off_t				st_size;			/* [XSI] file size, in bytes */
	blkcnt_t			st_blocks;			/* [XSI] blocks allocated for file */
	blksize_t			st_blksize;			/* [XSI] optimal blocksize for I/O */
	__uint32_t			st_flags;			/* user defined flags for file */
	__uint32_t			st_gen;				/* file generation number */
#elif defined(STILL_NOT_DEFINED)
	// TODO: amalgamate `do_link_hl` into `file_col`
	bool		do_link_hl	; /** Whether this file is a hardlink, and should be highlighted as such. */
	bool		is_mount	; /** Whether this file is a mount point or not. */
	bool		has_xattr	; /** Whether this file has extended attributes. */
	bool		has_acl		; /** Whether this file has an access control list. */
	//
	char		size_unit	; /** The unit of a file's size. Also indicates if size is in `maj,min` format. */
	char		suffix		; /** The symbol to be shown after a filename. From: `/` `@` `*` `=` `|` `%` */
	//
	wchar_t		icon		; /** The icon to be shown before a filename. */
	FileColour	file_col	; 
	TargetInfo*	target		; /** Information about the target of a link, if one exists. */
	//
	char		size_str[10]; /** A string repr of the filesize. */
	char		mode_str[11]; /** A string repr of the file's mode (type & permissions). */
	char		usr_name[32]; /** The name of the file's owner. */
	char		grp_name[32]; /** The name of the file's group. */
	//
	char*		flag_str	; /** A string repr of the file's user-defined flags. `NULL` if file has no flags. */
	FileStat*	children	; /** If this file is a dir, then `children` points to an array of `FileStat`s */
	int32_t		child_count	; /** The number of children that the directory has. If not a directory, then -1. */
	//
	TimeInfo*	times[TIME_COUNT];
#endif

/**
 * @fn parseFile
 * @brief Convert the information in `FileStat` from raw data into formatted, displayable output.
 *
 * @param pfile[in/out] A pointer to a `FileStat` object, where the information for a given file is stored.
 */
void parseFile(FileStat *const pfile) {
	// all NULL `FileStat`s should have been filtered out by now
	assert(pfile != NULL);

	const struct stat *const pstat = pfile->s;
	FileStatFields *const pfsf = pfile->f;

	// there should never be a case in which the stat object has been initiliased, and the FSF object hasn't, &vv
	//	i.e. either both should be initiliased, or neither should
	assert((pstat == NULL) == (pfsf == NULL));

	// if the processing step was able to get the `dirent` object of the file, but wasn't able to `stat` it,
	//	then we don't have any more information to get from the file, so just return
	const bool is_incomplete = (pstat == NULL) /* && (pfsf == NULL) */;

	/* ————————————————————————————————————————————————————————— */

	if (!is_incomplete) {
		// `FileStat::mode` is the one field where the field holds both the `dirent` and `stat` info
		pfile->mode = pstat->st_mode;
	}

	if (do_suffix()) pfile->suffix = getTypeSuffix(pfile->mode);
	if (do_icon()) pfile->icon = getIcon(pfile->name, S_ISDIR(pfile->mode));

	if (is_incomplete) return;

	/* ————————————————————————————————————————————————————————— */

	if (do_flag_str()) pfsf->flag_str = parseFlags(pstat->st_flags);
	if (do_usr_name())	getUser(pfsf->usr_name, pstat->st_uid);
	if (do_grp_name()) getGroup(pfsf->grp_name, pstat->st_gid);

	// if (do_size_str()) parseSize(pfsf->size_str, &pfsf->size_unit, pstat->st_size, pstat->st_rdev);
	// if (do_time_str()) parseTime(pfile->time_str, pstat->st_mtimespec.tv_sec, pfsf->time_col);

	/* ————————————————————————————————————————————————————————— */

	// recursively call this function for all children in a directory
	if (pfsf->child_count > 0) {
		for (int i = 0; i < pfsf->child_count; i++) {
			parseFile(&pfsf->children[i]);
		}
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore pfsf

#pragma clang diagnostic pop
