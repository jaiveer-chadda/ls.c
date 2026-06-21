/// @file output/output.h

#include "../model/stat-model.h"

void printHeader(void);
void printName(const name_t name, const FileColour *colour, const bool *is_hln, const flag_t *flags, type_t *suffix);

void   printNLink(const nlink_t	 *nlink		, const mode_t	*mode, bool *is_hln);
void  printFields(const FileInfo *all_files	, const int		*count);
void printUsrName(const uid_t	 *uid		, const ugidstr	 usr_name);
void printGrpName(const gid_t	 *gid		, const ugidstr	 grp_name);
void printSymlink(const path_t	  target	, const type_t	 suffix);
void printSizeStr(const sizestr	  size_str	, const char	 unit);
void printModeStr(const modestr	  str);
void printFlagStr(const flag_t	 *flags);
