/// @file features/git/git-print.c

#include <git2.h>
#include <stdio.h>

#include "malloc.h"
#include "strings.h"

#include "form/formatting.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {
	if (pFS->f == NULL || pFS->f->git == NULL) {
		putspaces(getLen(FI_git_info));
		return;
	}
	const GitInfo *const git_info = pFS->f->git;

	printf("%s%*d", getcol(RESET_ALL), getLen(FI_git_info), git_info->status);

	/* ——————————————————————————————————————————————————————— */

	if (git_info->repo != NULL) efree((void*)git_info->repo->branchname);
	efree((void*)git_info->repo);
	efree((void*)git_info);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
