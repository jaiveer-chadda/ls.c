/// @file parsing/parse-file.c

#include <assert.h>

#include "malloc.h"
#include "debugging.h"
#include "parse-file.h"

#include "model/types.h"
#include "options/options.h"

#include "icons/icons.h"
#include "form/formatting.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define A_TIME_SPEC st_atimespec
#define M_TIME_SPEC st_mtimespec
#define C_TIME_SPEC st_ctimespec
#define B_TIME_SPEC st_btimespec

#define SPEC(chr) chr##_SPEC

#define parseTime_t(type) do {				\
	if (do_time_t((type))) {				\
		size_t b_writ = 0;					\
		pfsf->times[(type)] = parseTime(	\
			emalloc(sizeof(TimeInfo)),		\
			(pstat->SPEC(type).tv_sec),		\
			&b_writ							\
		);									\
		setLen(timeFieldStr(type), b_writ);	\
	}										\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

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

	// `FileStat::mode` and `FileStat::inum` are the two fields which are filled by both `dirent` and `stat`
	if (!is_incomplete) {
		// move the inode and mode fields from the `stat` object into the main `FileStat` object
		// this is just to make sure everything's always in the same place - makes it easier to get later

		// `mode` is always transferred over, since its needed to parse other fields
		pfile->mode = pstat->st_mode;
		// however, `inum` is being transferred conditionally, since its only use is to be printed
		if (do_inum()) processInum(( pfile->inum = pstat->st_ino ));
	}

	// make sure to keep calculating the maximum name length
	setLen(FI_name, pfile->name_len);

	if (do_icon	 ()) pfile->icon   = getIcon(pfile->name, S_ISDIR(pfile->mode));
	if (do_suffix()) pfile->suffix = getTypeSuffix(pfile->mode);

	if (do_mode_str()) {
		getMode(pfile->mode_str, pfile->mode);						// find the basic mode string ("drwxr-xr-x")
		setLen(FI_acl, (pfile->has_acl =   checkACL(pfile->name)));	// check if file has an access control list ("+")
		setLen(FI_xat, (pfile->has_xat = checkXattr(pfile->name)));	// check if file has any extended attributes ("@")
	}

	checkLengths(pfile, true); // calculate the lengths of the `inode` and `mode` fields (if they're being displayed)

	if (is_incomplete) {
		if (do_inum()) processInum(pfile->inum);
		if (DO_COLOUR()) pfile->file_col = setFileColour(pfile->name, pfile->mode, 0U, false);
		return;
	}

	/* ————————————————————————————————————————————————————————— */

	if (do_usr_name()) pfsf->usr_name = getUser(pstat->st_uid);
	if (do_grp_name()) pfsf->grp_name = getGroup(pstat->st_gid);
	if (do_size_str()) pfsf->size_str = parseSize(&pfsf->size_unit, pstat->st_size, pstat->st_rdev);
	if (do_flag_str()) pfsf->flag_str = parseFlags(pstat->st_flags);
	if (DO_MOUNTDEV()) pfsf->is_mount = isMountPoint(pstat->st_dev, pfile->path);
	if (DO_COLOUR  ()) pfile->file_col = setFileColour(pfile->name, pfile->mode, pstat->st_flags, pfsf->is_mount);
	if (do_time_str()) { parseTime_t(A_TIME); parseTime_t(M_TIME); parseTime_t(C_TIME); parseTime_t(B_TIME); }

	if (!S_ISDIR(pstat->st_mode) && pstat->st_nlink > 1) pfsf->do_link_hl = true;

	checkLengths(pfile, false); // calculate the lengths of all numerical fields (i.e., non-string fields)

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
