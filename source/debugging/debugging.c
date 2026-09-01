/// @file debugging/debugging.c

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#define DEBUGGING_IMPLEMENTATION
#include "debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef RESET
#	undef RESET
#	undef ANSI
#	undef DIM
#endif

#define RESET "\33[m"
#define ANSI(code) "\033[" code "m"

#define DIM		ANSI("2")
#define NO_DIM	ANSI("22")

#define DIMS(str) DIM str NO_DIM

#define LBR DIMS("[")
#define RBR DIMS("]")

#define LPA DIMS("(")
#define RPA DIMS(")")

#define REL_PATH(file) (char *)(strstr((char *)(file), "source/") + (int)strlen("source/"))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define toStderr(...) do { fprintf(stderr, __VA_ARGS__); fflush(stderr); } while (0)
#define err(fmt, ...) do { fprintf(stderr, (fmt "\n"), __VA_ARGS__); fflush(stderr); } while (0)
#define ERR(str) fputs(str "\n", stderr);
#define nl() fputc('\n', stderr)

#define pbool(val) ((val) ? "true" : "false")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define X(name, ...) [L_##name] = { #name, __VA_ARGS__ }, 
static const LogLevel LOG_LEVELS[] = { LOG_LEVEL_TABLE };
#undef X

#ifdef LOG_LEVEL_TABLE
#	undef LOG_LEVEL_TABLE
#endif

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static char *last_file = "";
static char *last_func = "";

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define nulstr "(null)"
#define isnul(field)		((fs->field) == NULL ? nulstr : (fs->field))
// #define ifnul(field, else)	((long long)(fs->field) == 0ll ? (else) : (fs->field))

void d__dump(const FileStat *const fs) {
	struct stat		*pst = fs->s;
	FileStatFields	*fsf = fs->f;

	dline();

	err("FileStat * fs = %p  ", (void*)fs);
	err("├─ char     * name     = '%s'  ", fs->name           );
	err("├─ icon_t     icon     = '%lc' ", fs->icon           );
	err("├─ suff_t     suffix   = '%c'  ", fs->suffix         );
	ERR("│");
	err("├─ FileStat * parent   = %p    ", (void*)fs->parent  );
	err("├─ ino_t      inum     = %llu  ", fs->inum           );
	err("├─ namlen_t   name_len = %hd   ", fs->name_len       );
	ERR("│");
	err("├─ mode_t     mode     = %06o  ", fs->mode           );
	err("├─ modestr    mode_str = '%s'  ", fs->mode_str       );
	err("├─ bool       has_xat  = %s    ", pbool(fs->has_xat) );
	err("├─ bool       has_acl  = %s    ", pbool(fs->has_acl) );
	ERR("│");

	err("├─ struct stat * s = %p", (void*)fsf);
	if (pst != NULL) {
	err("│   ├─ dev_t     st_dev              = %d   ", pst->st_dev              );
	err("│   ├─ mode_t    st_mode             = %hu  ", pst->st_mode             );
	err("│   ├─ nlink_t   st_nlink            = %hu  ", pst->st_nlink            );
	err("│   ├─ ino_t     st_ino              = %llu ", pst->st_ino              );
	err("│   ├─ uid_t     st_uid              = %u   ", pst->st_uid              );
	err("│   ├─ gid_t     st_gid              = %u   ", pst->st_gid              );
	err("│   ├─ dev_t     st_rdev             = %d   ", pst->st_rdev             );
	err("│   ├─ off_t     st_size             = %lld ", pst->st_size             );
	err("│   ├─ blkcnt_t  st_blocks           = %lld ", pst->st_blocks           );
	err("│   ├─ blksize_t st_blksize          = %d   ", pst->st_blksize          );
	err("│   ├─ suint32_t st_flags            = %u   ", pst->st_flags            );
	err("│   ├─ suint32_t st_gen              = %u   ", pst->st_gen              );
	ERR("│   │");
	err("│   ├─ time_t    st_atimespec.tv_sec = %ld  ", pst->st_atimespec.tv_sec );
	err("│   ├─ time_t    st_mtimespec.tv_sec = %ld  ", pst->st_mtimespec.tv_sec );
	err("│   ├─ time_t    st_ctimespec.tv_sec = %ld  ", pst->st_ctimespec.tv_sec );
	err("│   └─ time_t    st_btimespec.tv_sec = %ld  ", pst->st_btimespec.tv_sec );
	ERR("│"); } else
	ERR("│   └─ (null)");

	err("└─ FileStatFields * f = %p", (void*)fsf);
	if (fsf != NULL) {
	err("    ├─ char     * size_str        = '%s' ", fsf->size_str               );
	err("    ├─ char     * flag_str        = '%s' ", fsf->flag_str               );
	err("    ├─ char     * usr_name        = '%s' ", fsf->usr_name               );
	err("    ├─ char     * grp_name        = '%s' ", fsf->grp_name               );
	ERR("    │");
	err("    ├─ FileColour file_col        = %u   ", fsf->file_col               );
	err("    ├─ unit_t     size_unit       = '%c' ", fsf->size_unit              );
	ERR("    │");
	err("    ├─ bool       do_link_hl      = %s   ", pbool(fsf->do_link_hl)      );
	err("    ├─ bool       is_mount        = %s   ", pbool(fsf->is_mount)        );
	ERR("    │");

	err("    ├─ TargetInfo * target = %p          ", (void*)fsf->target          );
	if				   (fsf->target != NULL) {
	err("    │   ├─ char     * path     = '%s'    ", fsf->target->path           );
	err("    │   ├─ FileColour colour   = %u      ", fsf->target->colour         );
	err("    │   ├─ char       suffix   = '%c'    ", fsf->target->suffix         );
	err("    │   └─ bool       is_apple = %s      ", pbool(fsf->target->is_apple));
	ERR("    │"); } else
	ERR("    │   └─ (null)");

	ERR("    ├─ TimeInfo * times[TT_COUNT]");
	err("    │   ├─ times[A_TIME] = %p"   , (void*)fsf->times[A_TIME]);
	if		  (fsf->times[A_TIME] != NULL) {
	err("    │   │   ├─ timestr    str    = '%s'", fsf->times[A_TIME]->str);
	err("    │   │   └─ TimeColour colour = %u  ", fsf->times[A_TIME]->colour); } else
	ERR("    │   │   └─ (null)")
	err("    │   ├─ times[M_TIME] = %p"   , (void*)fsf->times[M_TIME]);
	if		  (fsf->times[M_TIME] != NULL) {
	err("    │   │   ├─ timestr    str    = '%s'", fsf->times[M_TIME]->str);
	err("    │   │   └─ TimeColour colour = %u  ", fsf->times[M_TIME]->colour); } else
	ERR("    │   │   └─ (null)")
	err("    │   ├─ times[C_TIME] = %p"   , (void*)fsf->times[C_TIME]);
	if		  (fsf->times[C_TIME] != NULL) {
	err("    │   │   ├─ timestr    str    = '%s'", fsf->times[C_TIME]->str);
	err("    │   │   └─ TimeColour colour = %u  ", fsf->times[C_TIME]->colour); } else
	ERR("    │   │   └─ (null)")
	err("    │   └─ times[B_TIME] = %p"   , (void*)fsf->times[B_TIME]);
	if		  (fsf->times[B_TIME] != NULL) {
	err("    │       ├─ timestr    str    = '%s'", fsf->times[B_TIME]->str);
	err("    │       └─ TimeColour colour = %u  ", fsf->times[B_TIME]->colour); } else
	ERR("    │       └─ (null)")
	ERR("    │");

	err("    └─ FileStat * children[%d]", fsf->child_count);

	for (int i = 0; i < fsf->child_count; i++) {
	if (i != fsf->child_count - 1) {
	err("        ├─ FileStat * children[%d] = %p", i, (void*)&fsf->children[i]);
	err("        │   └─ char * name = '%s'", fsf->children[i].name);
	} else {
	err("        └─ FileStat * children[%d] = %p", i, (void*)&fsf->children[i]);
	err("            └─ char * name = '%s'", fsf->children[i].name); }
	}
	} else
	ERR("    └─ (null)");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__debug(const LogLevelIdx level_, const char *time, const int lineno, const char *file, const char *fmt, ...) {
	if (strcmp(last_file, file) != 0) {
		last_file = (char*)file;
		dline();
	}

	const LogLevel level = LOG_LEVELS[level_ < L_COUNT ? level_ : L_DEBUG];

	toStderr(
		ANSI("%hu") LBR " %-7s " RBR RESET " "	// [ WARNING ]
		LBR "%s" RBR " "						//		[02:41:15]
		ANSI("38;5;217") " %-22s" DIMS("@")		// 			getTargetInfo @
		ANSI("38;5;111") " %-30s"				//				info/get-file-info.c
		LPA "%3d" RPA RESET " "					//					(110)
		ANSI("%hu")
		,
		level.colour, level.name,
		time,
		last_func,
		REL_PATH(file),
		lineno,
		level.colour
	);

	va_list va_args;
	va_start(va_args, fmt); // `fmt` is the last known fixed argument

	vfprintf(stderr, fmt, va_args);
	va_end(va_args);

	fputs(RESET "\n", stderr);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__func(const char *func) {
	if (strcmp(last_func, func) != 0) last_func = (char*)func;
}

void d__line(void) {
	toStderr("%s", DIM);
	for (int i = 0; i < 150; i++) fputs("─", stderr);
	toStderr("%s\n", RESET);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
