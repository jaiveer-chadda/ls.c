/// @file features/git/git.c

#include <stdio.h>
#include <stdbool.h>

#include "malloc.h"
#include "debugging.h"
#include "model/stat-model.h"

/* ——————————————————————————————————————————————————————— */

/// I'm including these `.c` files directly, so that I can keep the performace benefits of
///	 using `static inline` functions, but I can also keep things neat & separated.
#include "_git.h"
#include "_repo.c"
#include "_status.c"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static bool did_init = false;

static inline void initGitState(void) {
	if (did_init) return;
	if (git_libgit2_init() != 1) debug(WARNING, "libgit2 initialised more than once");
	did_init = true;
}

void freeGitState(void) {
	if (!did_init) return;
	if (git_libgit2_shutdown() != 0) debug(WARNING, "libgit2 not fully shut down");
	did_init = false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

GitInfo *getGitInfo(const FileStat *const pFS) {
	printf("file      : %s", pFS->display);

	// initialise `libgit2`'s global state
	//	note: this state will be released by `main`, at the end of the program
	initGitState();

	/* ——————————————————————————————————————————————————————— */

	/** A pointer to the `GitInfo` object we're creating, which will be returned by the function. */
	GitInfo *git_info_obj	= NULL;

	git_repository	*repo	= NULL; /** Repr. of an existing git repo, including all its object contents. */
	git_reference	*head	= NULL; /** Information about the current branch of a repo. */
	git_object		*commit	= NULL; /** Info about the commmit that the branch `head` is at. */

	// note: this is defined earlier than it needs to be, so that the `goto LABEL_RETURN` statement works correctly
	git_status_list *status_list = NULL; /** The statuses of all ignored/modified/new/etc files in a repo. */

	/* ——————————————————————————————————————————————————————— */

	const char *repo_root; /** The path to the repo's `.git/` directory. */
	hash_t		repo_hash; /** The unique ID of the repo, based on the path to the repo's `.git` directory. */

	// fill out the repo, branch, and commit info, returning `NULL` if one of them can't be found
	if (getRepo(&repo, &repo_root, &repo_hash, pFS->path) != 0) goto LABEL_RETURN;

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	// from this point on, we know for a fact that we're in a git repo
	/// @todo now check if the repo already exists
	///			based on that, branch off to either creating a new repo, or assigning one to a file

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	/// @todo if the repo doesn't exist, start creating a new one...

	/** The name of the branch. May be the alnum name (e.g. `main`), or the branch hash. */
	const char *branch_name;
	size_t status_count;

	if (getRepoInfo(&head, &commit, &branch_name, &status_list, &status_count, repo) != 0) goto LABEL_RETURN;
	/*TEMP:*/ printf("\nfrom repo : %s\non branch : %s\nrepo hash : %llu\n", repo_root, branch_name, repo_hash);

	/* ——————————————————————————————————————————————————————— */

	/// @todo now that we've successfully got all the repo info, parse the statuses of each file

	parseStatuses(status_list, status_count);

	/* —— */ LABEL_RETURN: /* ——————————————————————————————————————————————————————————————————————— */

	// free all allocations
	//	note: usually I wouldn't check for `NULL` when freeing things, but I don't know how these functions work, so
	//		I'd rather be safe than sorry
	if (commit		!= NULL) git_object_free(commit);
	if (head		!= NULL) git_reference_free(head);
	if (repo		!= NULL) git_repository_free(repo);
	if (status_list	!= NULL) git_status_list_free(status_list);

	/* ——————————————————————————————————————————————————————— */

	/*TEMP:*/ dline();
	return git_info_obj;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {
	/*TEMP:*/ (void)pFS;
	/*TEMP:*/ printf("%s%s", getcol(RESET_ALL), "gitinfo");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /\bGIT_E\B|commit|(?<=\n\s*#.+"-)W/g
