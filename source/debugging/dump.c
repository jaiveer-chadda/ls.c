/// @file debugging/dump.c

#include <stdio.h>
#include <string.h>
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

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define T		DIMS("├─")
#define I		DIMS("│ ")
#define O		DIMS("└─")

#define p		 "\33[96m*" 		RESET
#define S		" \33[96m* "		RESET
#define E		" \33[94m= "		RESET

#define null	" \33[91m(null)"	RESET
#define STRUCT	" \33[95mstruct "	RESET
#define CHAR	" \33[95mchar "		RESET
#define BOOL	" \33[34mbool "		RESET

#define PTR				"%s"
#define STR		"\33[92m%s%s%s"		RESET
#define CHR		"\33[92m'%c'"		RESET
#define LCR		"\33[92m'%lc'"		RESET

#define ENM(idx) "\33[38;5;116m" DIMS("[")	#idx DIMS("]")	RESET
#define IDX(idx) "\33[38;5;216m" DIMS("[")	#idx DIMS("]")	RESET
#define NUM(fmt) "\33[38;5;216m"			#fmt		""	RESET
#define OCT(fmt) "\33[94m"					#fmt		""	RESET
#define   V(typ) "\33[93m"					#typ		""	RESET

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static char buf[32] = "";
static inline char *tostr(void *ptr) {
	if (ptr == NULL) strcpy(buf, "\33[38;5;69mNULL" RESET);
	else sprintf(buf, "\33[38;5;147m%p"RESET, ptr);
	return buf;
}

#define ptr(ptr) tostr((void*)(ptr))
#define ifn(q, do, else) ((q) == NULL ? (do) : (else))
#define str(fld) ifn(fld,"","\""), ifn(fld, "\b" null, fld), ifn(fld,"","\"")

#define err(fmt, ...) do { fprintf(stderr, (fmt "\n"), __VA_ARGS__); fflush(stderr); } while (0)
#define ERR(str_) fputs(str_ "\n", stderr);
#define pbool(val) ((val) ? "\33[32m✓ true\33[m" : "\33[31m× false\33[m")

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void d__dump(const FileStat *const fs) {
	struct stat		*pst = fs->s;
	FileStatFields	*fsf = fs->f;
	(void)pst; (void)fsf;

	dline();

	err(V(FileStat) S"fs"E PTR, ptr(fs));
	if (fs == NULL) { ERR(" "O  null); return; }
	err(T     CHAR  "   "S"name  "E STR      , str(fs->name)     );
	err(T" "V(icon_t)"   icon    "E LCR      , fs->icon          );
	err(T" "V(suff_t)"   suffix  "E CHR      , fs->suffix        );
	ERR(I);
	err(T" "V(FileStat)  S"parent"E PTR      , ptr(fs->parent)   );
	err(T" "V(ino_t)"    inum    "E NUM(%llu), fs->inum          );
	err(T" "V(namlen_t)" name_len"E NUM(%hd) , fs->name_len      );
	ERR(I);
	err(T" "V(mode_t)"   mode    "E OCT(%06o), fs->mode          );
	err(T" "V(modestr)"  mode_str"E STR      , str(fs->mode_str) );
	err(T     BOOL  "    has_xat "E"%s"      , pbool(fs->has_xat));
	err(T     BOOL  "    has_acl "E"%s"      , pbool(fs->has_acl));
	ERR(I);

	err(T STRUCT V(stat) S"s"E PTR, ptr(fsf));
	if (pst != NULL) {
		err(I"  "T" "V(dev_t)"     st_dev    "E NUM(%d)  , pst->st_dev    );
		err(I"  "T" "V(mode_t)"    st_mode   "E NUM(%hu) , pst->st_mode   );
		err(I"  "T" "V(nlink_t)"   st_nlink  "E NUM(%hu) , pst->st_nlink  );
		err(I"  "T" "V(ino_t)"     st_ino    "E NUM(%llu), pst->st_ino    );
		err(I"  "T" "V(uid_t)"     st_uid    "E NUM(%u)  , pst->st_uid    );
		err(I"  "T" "V(gid_t)"     st_gid    "E NUM(%u)  , pst->st_gid    );
		err(I"  "T" "V(dev_t)"     st_rdev   "E NUM(%d)  , pst->st_rdev   );
		err(I"  "T" "V(off_t)"     st_size   "E NUM(%lld), pst->st_size   );
		err(I"  "T" "V(blkcnt_t)"  st_blocks "E NUM(%lld), pst->st_blocks );
		err(I"  "T" "V(blksize_t)" st_blksize"E NUM(%d)  , pst->st_blksize);
		err(I"  "T" "V(uint32_t)"  st_flags  "E NUM(%u)  , pst->st_flags  );
		err(I"  "T" "V(uint32_t)"  st_gen    "E NUM(%u)  , pst->st_gen    );
		ERR(I"  "I);
		err(I"  "T" "V(time_t)" st_atimespec.tv_sec"E NUM(%ld), pst->st_atimespec.tv_sec );
		err(I"  "T" "V(time_t)" st_mtimespec.tv_sec"E NUM(%ld), pst->st_mtimespec.tv_sec );
		err(I"  "T" "V(time_t)" st_ctimespec.tv_sec"E NUM(%ld), pst->st_ctimespec.tv_sec );
		err(I"  "O" "V(time_t)" st_btimespec.tv_sec"E NUM(%ld), pst->st_btimespec.tv_sec );
		ERR(I);
	} else {
		ERR(I"  "O  null);
	}

	err(O" "V(FileStatFields) S"f"E PTR, ptr(fsf));

	if (fsf != NULL) {
		err("    "T     CHAR"   " S "size_str"E STR    , str(fsf->size_str)    );
		err("    "T     CHAR"   " S "flag_str"E STR    , str(fsf->flag_str)    );
		err("    "T     CHAR"   " S "usr_name"E STR    , str(fsf->usr_name)    );
		err("    "T     CHAR"   " S "grp_name"E STR    , str(fsf->grp_name)    );
		ERR("    "I);
		err("    "T" "V(FileColour)" file_col"E NUM(%u), fsf->file_col         );
		err("    "T" "V(unit_t)"    size_unit"E CHR    , fsf->size_unit        );
		ERR("    "I);
		err("    "T     BOOL  "    do_link_hl"E"%s"    , pbool(fsf->do_link_hl));
		err("    "T     BOOL  "      is_mount"E"%s"    , pbool(fsf->is_mount)  );
		ERR("    "I);

		err("    "T" "V(TargetInfo) S"target"E PTR, ptr(fsf->target));
		if (fsf->target != NULL) {
			err("    "I"  "T     CHAR "   " S "path    "E STR    , str(fsf->target->path)      );
			err("    "I"  "T" "V(FileColour) " colour  "E NUM(%u), fsf->target->colour         );
			err("    "I"  "T     CHAR   "      suffix  "E CHR    , fsf->target->suffix         );
			err("    "I"  "O     BOOL   "      is_apple"E"%s"    , pbool(fsf->target->is_apple));
		} else {
			ERR("    "I"  "O null);
		}

		ERR("    "I);
		ERR("    "T" "V(TimeInfo) DIMS(" (")p"times"DIMS(")")ENM(TT_COUNT));

		err("    "I"  "T" times"ENM(A_TIME) E PTR, ptr(fsf->times[A_TIME]));
		if (fsf->times[A_TIME] != NULL) {
			err("    "I"  "I"  "T" "V(timestr)"    str   "E STR, str(fsf->times[A_TIME]->str));
			err("    "I"  "I"  "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[A_TIME]->colour);
		}

		err("    "I"  "T" times"ENM(M_TIME) E PTR, ptr(fsf->times[M_TIME]));
		if (fsf->times[M_TIME] != NULL) {
			err("    "I"  "I"  "T" "V(timestr)"    str   "E STR, str(fsf->times[M_TIME]->str));
			err("    "I"  "I"  "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[M_TIME]->colour);
		}

		err("    "I"  "T" times"ENM(C_TIME) E PTR, ptr(fsf->times[C_TIME]));
		if (fsf->times[C_TIME] != NULL) {
			err("    "I"  "I"  "T" "V(timestr)"    str   "E STR, str(fsf->times[C_TIME]->str));
			err("    "I"  "I"  "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[C_TIME]->colour);
		}

		err("    "I"  "O" times"ENM(B_TIME) E PTR, ptr(fsf->times[B_TIME]));
		if (fsf->times[B_TIME] != NULL) {
			err("    "I"      "T" "V(timestr)"    str   "E STR, str(fsf->times[B_TIME]->str));
			err("    "I"      "O" "V(TimeColour)" colour"E NUM(%u), fsf->times[B_TIME]->colour);
		}

		const int max_len = sprintf(buf, "%d", fsf->child_count - 1);

		ERR("    "I);
		err("    "O" "V(FileStat) DIMS(" (")p"children"DIMS(")")IDX(%d), fsf->child_count);
		for (int i = 0; i < fsf->child_count; i++) {
			err("        %s children"IDX(%*d) E PTR " " STR,
				i != fsf->child_count - 1 ? T : O,
				max_len, i,
				ptr(&fsf->children[i]),
				str(fsf->children[i].name)
			);
		}

	} else {
		ERR("    "O null);
	}

	dline();
}
