/// @file features/features.h

#ifndef FEATURES_H
#define FEATURES_H

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include "model/types.h"

#define TYPE_MASK S_IFMT	/// A mask to keep just the type information from the Unix octal mode - (0o170000).
#define PERM_MASK 0000777	/// A mask to keep just the permission info. from the Unix octal mode - (0o000777).
#define EXEC_MASK 0000111	/// A mask to tell whether a file is an executable or not.

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Field Printing Functions ————————————————————————————————————————————————————————————————————————————————————— */

void print_uid(const FileStat *const pFS);
void print_gid(const FileStat *const pFS);
void print_inum(const FileStat *const pFS);
void print_mode(const FileStat *const pFS);
void print_name(const FileStat *const pFS);
void print_size(const FileStat *const pFS);
void print_flags(const FileStat *const pFS);
void print_nlink(const FileStat *const pFS);
void print_dev_no(const FileStat *const pFS);
void print_flag_str(const FileStat *const pFS);
void print_mode_str(const FileStat *const pFS);
void print_size_str(const FileStat *const pFS);
void print_usr_name(const FileStat *const pFS);
void print_grp_name(const FileStat *const pFS);
void print_time_str(const FileStat *const pFS, const TimeType type);
void print_time_raw(const FileStat *const pFS, const TimeType type);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— flags.c —————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *parseFlags(const flag_t raw_flags);

/* —— links.c —————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path);
bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t file_path);

/* —— mode.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getMode(modestr mode_str, const mode_t oct_mode);
char getTypeSuffix(const mode_t mode);
bool checkXattr(const path_t path);
bool checkACL(const path_t path);

/* —— mount.c —————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool isMountPoint(const dev_t dev_no, const path_t path);
void printMountDevice(const name_t filename);

/* —— path.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

int getDirPath(path_t out_path, const path_t path);
void abbrPath(path_t out_path, const path_t abs_path);

/* —— size.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *parseSize(unit_t *const size_unit, const off_t size, const dev_t rdev);

/* —— time.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

TimeInfo *parseTime(TimeInfo *const timeobj, const time_t file_time, size_t *const b_writ);

/* —— ugid.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

char  *getUser(const uid_t uid);
char *getGroup(const gid_t gid);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !FEATURES_H */
