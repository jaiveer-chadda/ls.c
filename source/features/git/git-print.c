/// @file features/git/git-print.c

#include <git2.h>
#include <stdio.h>
#include <string.h>

#include "malloc.h"
#include "strings.h"

#include "form/formatting.h"
#include "model/stat-model.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline char getIndexStatus(const git_status_t status) {
	if (status & GIT_STATUS_CONFLICTED		) return GIT_CHR_CONFLICTED	;

	if (status & GIT_STATUS_INDEX_TYPECHANGE) return GIT_CHR_TYPECHANGE	;
	if (status & GIT_STATUS_INDEX_RENAMED	) return GIT_CHR_RENAMED	;
	if (status & GIT_STATUS_INDEX_DELETED	) return GIT_CHR_DELETED	;
	if (status & GIT_STATUS_INDEX_NEW		) return GIT_CHR_NEW		;
	if (status & GIT_STATUS_INDEX_MODIFIED	) return GIT_CHR_MODIFIED	;

	return GIT_CHR_CURRENT;
}

static inline char getWTreeStatus(const git_status_t status) {
	if (status & GIT_STATUS_WT_TYPECHANGE	) return GIT_CHR_TYPECHANGE	;
	if (status & GIT_STATUS_WT_RENAMED		) return GIT_CHR_RENAMED	;
	if (status & GIT_STATUS_WT_DELETED		) return GIT_CHR_DELETED	;
	if (status & GIT_STATUS_WT_NEW			) return GIT_CHR_NEW		;
	if (status & GIT_STATUS_WT_MODIFIED		) return GIT_CHR_MODIFIED	;

	if (status & GIT_STATUS_WT_UNREADABLE	) return GIT_CHR_UNREADABLE	;
	if (status & GIT_STATUS_IGNORED			) return GIT_CHR_IGNORED	;

	return GIT_CHR_CURRENT;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {

	const int gitinfo_len = getLen(FI_git_info);

	// if `gitinfo_len` is 0, then no git repos were ever encountered,
	//	and so there's no point in printing anything in the `git` field
	if (gitinfo_len == 0) return;

	/* ——————————————————————————————————————————————————————— */

	if (pFS->f == NULL || pFS->f->git == NULL) {
		printf("%s%-*s%ls", getcol(RESET_ALL), gitinfo_len, GIT_DEFAULT_STRING, FIELD_PAD);
		return;
	}

	/* ——————————————————————————————————————————————————————— */

	const GitInfo *const git  = pFS->f->git;
	const git_status_t status = git->status == GIT_NO_STATUS ? 0 : git->status;

	colprint(RESET_ALL);

	char out_buf[STRLEN(GIT_STRING_NO_BRANCH) + MAX_GIT_BRANCH_LEN] = {
		/* 0 */ getIndexStatus(status), // indicates staged changes
		/* 1 */ getWTreeStatus(status), // indicates unstaged changes
		/* 2 */ ' ',
		/* 3 */ '-', // to be replaced with the branch status
		/* 4 */ ' ', //		(replacements only made if `branch != NULL`)
		/* 5 */ '-', // to be replaced with the branch's name
	};

	if (git->branch != NULL) {
		out_buf[3] = git->branch->status;
		strncpy(out_buf + 5, git->branch->branchname, MAX_GIT_BRANCH_LEN);

		efree((void*)git->branch->branchname);
		efree((void*)git->branch);
	}

	printf("%-*s%ls", gitinfo_len, out_buf, FIELD_PAD);

	/* ——————————————————————————————————————————————————————— */

	efree((void*)git);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
