/// @file features/features.h

#ifndef FEATURES_H
#define FEATURES_H

#include "model/types.h"
#include "graphics/graphics.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Field Printing Functions ————————————————————————————————————————————————————————————————————————————————————— */

void print_uid(const FileStat *const pFS);
void print_gid(const FileStat *const pFS);
void print_inum(const FileStat *const pFS);
void print_link(const FileStat *const pFS);
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

void print_mount(const MountInfo *const mount);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— flags.c —————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *parseFlags(FileStat *const pFS);
void freeFirmlinks(void);

/* —— inum.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

void processInum(ino_t inum);

/* —— links.c —————————————————————————————————————————————————————————————————————————————————————————————————————— */

TargetInfo *getLink(FileStat *const pFS);

/* —— mode.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define TYPE_MASK S_IFMT  /// A mask to keep just the type information from the Unix octal mode - (`0o170000`).
#define PERM_MASK 0007777 /// A mask to keep just the permission info. from the Unix octal mode - (`0o007777`).
#define EXEC_MASK 0000111 /// A mask to tell whether a file is an executable or not - (`0o000111`).

void getMode(modestr mode_str, const mode_t oct_mode);
char getTypeSuffix(const mode_t mode);
bool checkXattr(const path_t path);
bool checkACL(const path_t path);

/* —— mount.c —————————————————————————————————————————————————————————————————————————————————————————————————————— */

const MountInfo *getMountPoint(const char *const path, const bool is_dir);

/* —— path.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IS_LINK_TARGET INT16_MIN

const char *getDisplayPath(const char *const path, const namlen_t path_len);

/* —— size.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

char *parseSize(unit_t *const size_unit, const off_t size, const dev_t rdev);

/* —— time.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

TimeInfo *parseTime(TimeInfo *const timeobj, const time_t file_time, size_t *const b_writ);

/* —— ugid.c ——————————————————————————————————————————————————————————————————————————————————————————————————————— */

char  *getUser(const uid_t uid);
char *getGroup(const gid_t gid);
Colour get_usr_colour(const uid_t uid);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !FEATURES_H */
