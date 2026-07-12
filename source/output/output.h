/// @file output/output.h

#include "../model/stat-model.h"

void  printHeader(void);
void printFlagStr(const flag_t	 *flags																);
void  printFields(const FileInfo *all_files	, const int		*count									);
void   printNLink(const nlink_t	 *nlink		, const mode_t	*mode									);
void printUsrName(const uid_t	 *uid		, const ugidstr	 usr_name, const bool		*is_valid	);
void printGrpName(const gid_t	 *gid		, const ugidstr	 grp_name, const bool		*is_valid	);
void printSizeStr(const sizestr	  size_str	, const char	*unit	 , const mode_t		*mode		);
void printModeStr(const modestr	  str		, const bool	 has_acl , const bool		 has_xattr	);
void printSymlink(const path_t	  target	, const suff_t	 suffix	 , const FileColour	 link_col	);

bool escapeName(name_t escaped_name, const name_t orig_name, const char *colour_escape);
void printName(const name_t name, const FileColour *colour, const bool *is_hln, const flag_t *flags, suff_t *suffix);
