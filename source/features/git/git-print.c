/// @file features/git/git-print.c

#include <git2.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>

#include "malloc.h"
#include "strings.h"
#include "strbuilder.h"

#include "form/formatting.h"
#include "model/stat-model.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RETURN_STATUS(type) do { *colour = (GFS_COL_##type); return (GFS_##type); } while (0)

static inline char getIndexStatus(Colour *const colour, const git_status_t status) {
	if (status & GIT_STATUS_CONFLICTED		) RETURN_STATUS(CONFLICTED	);

	if (status & GIT_STATUS_INDEX_TYPECHANGE) RETURN_STATUS(TYPECHANGE	);
	if (status & GIT_STATUS_INDEX_RENAMED	) RETURN_STATUS(RENAMED		);
	if (status & GIT_STATUS_INDEX_DELETED	) RETURN_STATUS(DELETED		);
	if (status & GIT_STATUS_INDEX_NEW		) RETURN_STATUS(NEW			);
	if (status & GIT_STATUS_INDEX_MODIFIED	) RETURN_STATUS(MODIFIED	);

	RETURN_STATUS(CURRENT);
}

static inline char getWTreeStatus(Colour *const colour, const git_status_t status) {
	if (status & GIT_STATUS_WT_TYPECHANGE	) RETURN_STATUS(TYPECHANGE	);
	if (status & GIT_STATUS_WT_RENAMED		) RETURN_STATUS(RENAMED		);
	if (status & GIT_STATUS_WT_DELETED		) RETURN_STATUS(DELETED		);
	if (status & GIT_STATUS_WT_NEW			) RETURN_STATUS(NEW			);
	if (status & GIT_STATUS_WT_MODIFIED		) RETURN_STATUS(MODIFIED	);

	if (status & GIT_STATUS_WT_UNREADABLE	) RETURN_STATUS(UNREADABLE	);
	if (status & GIT_STATUS_IGNORED			) RETURN_STATUS(IGNORED		);

	RETURN_STATUS(CURRENT);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {

	const int gitinfo_len = getLen(FI_git_info);

	// if `gitinfo_len` is 0, then no git repos were ever encountered,
	//	and so there's no point in printing anything in the `git` field
	if (gitinfo_len == 0) return;

	/* ——————————————————————————————————————————————————————— */

	if (pFS->f == NULL || pFS->f->git == NULL) {
		printf("%s%-*s%ls", getcol(PUNCT), gitinfo_len, GIT_DEFAULT_STRING, FIELD_PAD);
		return;
	}

	/* ——————————————————————————————————————————————————————— */

	const GitInfo *const git  = pFS->f->git;
	const git_status_t status = git->status == GIT_NO_STATUS ? 0 : git->status;

	StringBuilder output = sb_init(STRLEN("-- - -"));
	size_t outlen = 0;

	sb_addcol(output, RESET_ALL);

	Colour index_col, wtree_col;

	const char index_chr = getIndexStatus(&index_col, status); // staged changes
	const char wtree_chr = getWTreeStatus(&wtree_col, status); // unstaged changes

	sb_addcol(output, index_col); outlen += sb_addchr(output, index_chr);
	sb_addcol(output, wtree_col); outlen += sb_addchr(output, wtree_chr);
	outlen += sb_addchr(output, ' ');

	if (git->branch != NULL) {
		const GitBranchInfo *const branch = git->branch;
		sb_addcol(output, git_branch_colours[branch->status]);

		outlen += sb_addchr(output, git_branch_chars[branch->status]);
		outlen += sb_addchr(output, ' ');

		Colour branch_col;

		if (branch->branch_len >= STRLEN("main") &&
			branch->branchname[0] == 'm'		 &&
			branch->branchname[1] == 'a'		 && (
				strcmp(branch->branchname + 2, "in"	 ) == 0 ||
				strcmp(branch->branchname + 2, "ster") == 0
			)
		)	 branch_col = GIT_BRANCH_COLOUR_MAIN;
		else branch_col = GIT_BRANCH_COLOUR_OTHER;

		sb_addcol(output, branch_col);
		outlen += sb_addstr(output, branch->branchname, branch->branch_len);

		efree((void*)branch->branchname);
		efree((void*)branch);

	} else {
		sb_addcol(output, PUNCT);
		outlen += sb_addlit(output, "- -");
	}

	sb_putsf(output);
	putspaces(gitinfo_len - outlen);

	fputws(FIELD_PAD, stdout);

	/* ——————————————————————————————————————————————————————— */

	efree((void*)git);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore wtree
