/// @file features/git/git.c

#include <git2.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "malloc.h"
#include "strings.h"
#include "debugging.h"
#include "form/formatting.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define private static inline
#define public

/* ——————————————————————————————————————————————————————— */

static bool did_init = false;

private void initGitState(void) {
	if (did_init) return;
	if (git_libgit2_init() != 1) debug(WARNING, "libgit2 initialised more than once");
	did_init = true;
}

public void freeGitState(void) {
	if (!did_init) return;
	if (git_libgit2_shutdown() != 0) debug(WARNING, "libgit2 not fully shut down");
	did_init = false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

private const char *getBranchName(const git_reference *const head) {
	/** The name of the branch. May be the alnum name (e.g. `main`), or the branch hash. */
	const char *branch_name = git_reference_name(head);

	// if the branchname is formatted as, e.g., `origin/main`, or `ref/head/branch`, then only keep the final segment
	const char *const branch_basename = strrchr(branch_name, '/');
	if (branch_basename != NULL) branch_name = branch_basename + 1;

	return branch_name;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RETURN(obj) do { git_info_obj = (obj); goto LABEL_RETURN; } while (0)

public const GitInfo *getGitInfo(const FileStat *const pFS) {
	printf("file      : %s\n", pFS->abspath);

	// initialise `libgit2`'s global state
	//	note: this state will be released by `main`, at the end of the program
	initGitState();

	/* ——————————————————————————————————————————————————————— */

	/** A pointer to the `GitInfo` object we're creating, which will be returned by the function. */
	const GitInfo *git_info_obj = NULL;

	git_repository *repo = NULL; /** Repr. of an existing git repo, including all its object contents. */
	git_reference  *head = NULL; /** Information about the current branch of a repo. */

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	// fill out the repo, branch, and commit info, returning `NULL` if any of them can't be found
	if (git_repository_open_ext(&repo, pFS->abspath, 0, NULL) != 0) RETURN(NULL); // open the repo
	if (git_repository_head(&head, repo) != 0) RETURN(NULL); // get the HEAD reference (current branch)

	/* ——————————————————————————————————————————————————————— */

	const char *const repo_root = git_repository_commondir(repo);
	const char *const branch_name = getBranchName(head);

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	printf("from repo : %s\n", repo_root);
	printf("on branch : %s\n", branch_name);

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */
	/* —— */ LABEL_RETURN: /* ——————————————————————————————————————————————————————————————————————— */

	// free all allocations
	//	note: usually I wouldn't check for `NULL` when freeing things, but I don't know how these functions work, so
	//		I'd rather be safe than sorry
	if (head != NULL) git_reference_free(head);
	if (repo != NULL) git_repository_free(repo);

	/* ——————————————————————————————————————————————————————— */

	dline();
	return git_info_obj;
}

#undef RETURN

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

public void print_git_info(const FileStat *const pFS) {
	if (pFS->f == NULL || pFS->f->git == NULL) {
		putspaces(getLen(FI_git_info));
		return;
	}

	printf("%s%*d", getcol(RESET_ALL), getLen(FI_git_info), pFS->f->git->status);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /\\(?:e|0?33)\[[0-9;]*m\B/g
