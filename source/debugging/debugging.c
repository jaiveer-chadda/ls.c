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

#define T		DIMS("├─")
#define I		DIMS("│ ")
#define O		DIMS("└─")

#define S		" \33[96m* "			RESET
#define E		" \33[96m" DIMS("=")" "	RESET

#define null	" \33[91m(null)"		RESET
#define STRUCT	" \33[95mstruct "		RESET
#define CHAR	" \33[95mchar "			RESET
#define BOOL	" \33[34mbool "			RESET

#define PTR		"\33[38;5;147m%p"		RESET
#define STR		"\33[92m'%s'"			RESET
#define CHR		"\33[92m'%c'"			RESET
#define LCR		"\33[92m'%lc'"			RESET

#define IDX(idx) "\33[38;5;215m" DIMS("[")	#idx DIMS("]")	RESET
#define NUM(fmt) "\33[38;5;216m"			#fmt		""	RESET
#define OCT(fmt) "\33[94m"					#fmt		""	RESET
#define  V(type) "\33[93m"					#type		""	RESET

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define toStderr(...) do { fprintf(stderr, __VA_ARGS__); fflush(stderr); } while (0)
#define err(fmt, ...) do { fprintf(stderr, (fmt "\n"), __VA_ARGS__); fflush(stderr); } while (0)
#define ERR(str) fputs(str "\n", stderr);
#define nl() fputc('\n', stderr)

#define pbool(val) ((val) ? "\33[32mtrue\33[m" : "\33[31mfalse\33[m")

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

void d__dump(const FileStat *const fs) {
	struct stat		*pst = fs->s;
	FileStatFields	*fsf = fs->f;

	dline();

	err("FileStat"S"fs"E PTR, (void*)fs);
	err(T     CHAR  "   "S"name    "E STR      , fs->name           );
	err(T" "V(icon_t)"     icon    "E LCR      , fs->icon           );
	err(T" "V(suff_t)"     suffix  "E CHR      , fs->suffix         );
	ERR(I);
	err(T" "V(FileStat)  S"parent  "E PTR      , (void*)fs->parent  );
	err(T" "V(ino_t)"      inum    "E NUM(%llu), fs->inum           );
	err(T" "V(namlen_t)"   name_len"E NUM(%hd) , fs->name_len       );
	ERR(I);
	err(T" "V(mode_t)"     mode    "E OCT(%06o), fs->mode           );
	err(T" "V(modestr)"    mode_str"E STR      , fs->mode_str       );
	err(T     BOOL  "      has_xat "E"%s"      , pbool(fs->has_xat) );
	err(T     BOOL  "      has_acl "E"%s"      , pbool(fs->has_acl) );
	ERR(I);

	err(T STRUCT V(stat) S"s"E PTR, (void*)fsf);
	if (pst != NULL) {
		err(I"  "T" "V(dev_t)"     st_dev             "E NUM(%d)   , pst->st_dev              );
		err(I"  "T" "V(mode_t)"    st_mode            "E NUM(%hu)  , pst->st_mode             );
		err(I"  "T" "V(nlink_t)"   st_nlink           "E NUM(%hu)  , pst->st_nlink            );
		err(I"  "T" "V(ino_t)"     st_ino             "E NUM(%llu) , pst->st_ino              );
		err(I"  "T" "V(uid_t)"     st_uid             "E NUM(%u)   , pst->st_uid              );
		err(I"  "T" "V(gid_t)"     st_gid             "E NUM(%u)   , pst->st_gid              );
		err(I"  "T" "V(dev_t)"     st_rdev            "E NUM(%d)   , pst->st_rdev             );
		err(I"  "T" "V(off_t)"     st_size            "E NUM(%lld) , pst->st_size             );
		err(I"  "T" "V(blkcnt_t)"  st_blocks          "E NUM(%lld) , pst->st_blocks           );
		err(I"  "T" "V(blksize_t)" st_blksize         "E NUM(%d)   , pst->st_blksize          );
		err(I"  "T" "V(suint32_t)" st_flags           "E NUM(%u)   , pst->st_flags            );
		err(I"  "T" "V(suint32_t)" st_gen             "E NUM(%u)   , pst->st_gen              );
		ERR(I"  "I);
		err(I"  "T" "V(time_t)"    st_atimespec.tv_sec"E NUM(%ld)  , pst->st_atimespec.tv_sec );
		err(I"  "T" "V(time_t)"    st_mtimespec.tv_sec"E NUM(%ld)  , pst->st_mtimespec.tv_sec );
		err(I"  "T" "V(time_t)"    st_ctimespec.tv_sec"E NUM(%ld)  , pst->st_ctimespec.tv_sec );
		err(I"  "O" "V(time_t)"    st_btimespec.tv_sec"E NUM(%ld)  , pst->st_btimespec.tv_sec );
		ERR(I);
	} else {
		ERR(I"  "O  null);
	}

	err(O" FileStatFields"S"f"E PTR, (void*)fsf);

	if (fsf != NULL) {
		err("    "T     CHAR"   " S "size_str       "E STR     , fsf->size_str               );
		err("    "T     CHAR"   " S "flag_str       "E STR     , fsf->flag_str               );
		err("    "T     CHAR"   " S "usr_name       "E STR     , fsf->usr_name               );
		err("    "T     CHAR"   " S "grp_name       "E STR     , fsf->grp_name               );
		ERR("    "I);
		err("    "T" "V(FileColour)" file_col       "E NUM(%u) , fsf->file_col               );
		err("    "T" "V(unit_t)"     size_unit      "E CHR     , fsf->size_unit              );
		ERR("    "I);
		err("    "T     BOOL  "      do_link_hl     "E"%s"     , pbool(fsf->do_link_hl)      );
		err("    "T     BOOL  "      is_mount       "E"%s"     , pbool(fsf->is_mount)        );
		ERR("    "I);

		err("    "T" "V(TargetInfo) S"target"E PTR, (void*)fsf->target);
		if (fsf->target != NULL) {
			err("    "I"  "T     CHAR "   " S "path    "E STR    , fsf->target->path           );
			err("    "I"  "T" "V(FileColour) " colour  "E NUM(%u), fsf->target->colour         );
			err("    "I"  "T     CHAR   "      suffix  "E CHR    , fsf->target->suffix         );
			err("    "I"  "O     BOOL   "      is_apple"E"%s"    , pbool(fsf->target->is_apple));
		} else {
			ERR("    "I"  "O  null);
		}

		ERR("    "I);
		ERR("    "T" "V(TimeInfo) S"times"IDX(TT_COUNT));

		err("    "I"  "T" times"IDX(A_TIME) E PTR, (void*)fsf->times[A_TIME]);
		if (fsf->times[A_TIME] != NULL) {
			err("    "I"  "I"  "T" "V(timestr)"    str   "E STR    , fsf->times[A_TIME]->str);
			err("    "I"  "I"  "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[A_TIME]->colour);
		} else {
			ERR("    "I"  "I"  "O  null)
		}

		err("    "I"  "T" times"IDX(M_TIME) E PTR, (void*)fsf->times[M_TIME]);
		if (fsf->times[M_TIME] != NULL) {
			err("    "I"  "I"  "T" "V(timestr)"    str   "E STR    , fsf->times[M_TIME]->str);
			err("    "I"  "I"  "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[M_TIME]->colour);
		} else {
			ERR("    "I"  "I"  "O  null)
		}

		err("    "I"  "T" times"IDX(C_TIME) E PTR, (void*)fsf->times[C_TIME]);
		if (fsf->times[C_TIME] != NULL) {
			err("    "I"  "I"  "T" "V(timestr)"    str   "E STR    , fsf->times[C_TIME]->str);
			err("    "I"  "I"  "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[C_TIME]->colour);
		} else {
			ERR("    "I"  "I"  "O  null)
		}

		err("    "I"  "O" times"IDX(B_TIME) E PTR, (void*)fsf->times[B_TIME]);
		if (fsf->times[B_TIME] != NULL) {
			err("    "I"      "T" "V(timestr)"    str   "E STR    , fsf->times[B_TIME]->str);
			err("    "I"      "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[B_TIME]->colour);
		} else {
			ERR("    "I"      "O  null)
		}

		ERR("    "I);
		err("    "O" "V(FileStat) S"children[%d]", fsf->child_count);
		for (int i = 0; i < fsf->child_count; i++) {
			err("        %s children"IDX(%d) E PTR " " STR,
				i != fsf->child_count - 1 ? T : O,
				i,
				(void*)&fsf->children[i],
				fsf->children[i].name
			);
		}

	} else {
		ERR("    "O  null);
	}

	dline();
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
