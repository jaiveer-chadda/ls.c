/// @file features/git/_repo.c

#include <stdio.h>
#include <assert.h>
#include <string.h> // strrchr()

#include "_git.h"

#define E_BARE_REPO ((int)-2)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int getRepo(
	git_repository **const repo, const char **const repo_root, hash_t *repo_hash, const char *const path
) {
	/// @todo print/store proper error messages for each of the caught errors
	int error = 0;

	/* ——————————————————————————————————————————————————————— */

	error = git_repository_open_ext(repo, path, 0, NULL); // open the repo

	switch (error) {
		case 0				: break;
		case GIT_ENOTFOUND	: printf(" \33[91m( not in git repo )\33[m\n"); return error; // repo not found
		case -1				: return error; // repo found, but corruption/error while reading it
		default				: return error; // unknown error
	}

	/* ——————————————————————————————————————————————————————— */

	/// I'm making the executive decision to not handle bare repos. With how complicated `git` already is,
	///  I don't need any more unnecessary complexity, and they're so rare that they're not worth considering.
	/// @todo I may add support for them later, but not while I'm still setting the system up.
	if (git_repository_is_bare(*repo)) return E_BARE_REPO;

	/* ———————————————————————————————————————————————————————————————————————————————— */

	/** The path to the repo's `.git/` directory. */
	*repo_root = git_repository_commondir(*repo);

	/**
	 * For the system I'm trying to build to work correctly, I need to be able to compare two repos to check whether
	 *	they're the same or not.
	 *
	 * This could be easily achieved by comparing their paths directly using `strcmp`, however, using `strcmp` while
	 *	iterating through a list of repos would be very inefficient.
	 *
	 * Therefore, I'm going to take the performace hit once per file, by iterating through its `commondir` path
	 *	just once (in `hashstr`), which will then allow me to directly compare hashes, instead of paths.
	 */
	*repo_hash = hashstr(*repo_root);

	/* ———————————————————————————————————————————————————————————————————————————————— */

	assert(error == 0);
	return error;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define STATUS_OPT_FLAGS ((git_status_opt_t)(					\
	GIT_STATUS_OPT_INCLUDE_IGNORED			|					\
	GIT_STATUS_OPT_INCLUDE_UNTRACKED		|					\
	GIT_STATUS_OPT_INCLUDE_UNMODIFIED		|					\
	GIT_STATUS_OPT_INCLUDE_UNREADABLE		| /* maybe...? */	\
	\
	GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS	|					\
	GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH	| /* i think so */	\
	\
	GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX	|					\
	GIT_STATUS_OPT_RENAMES_FROM_REWRITES	| /* maybe...? */	\
	GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR						\
))

#define STATUS_OPT_OBJ_INIT ((git_status_options){	\
	.version = GIT_STATUS_OPTIONS_VERSION,			\
	.show	 = GIT_STATUS_SHOW_INDEX_AND_WORKDIR,	\
	.flags	 = STATUS_OPT_FLAGS						\
})

/* ———————————————————————————————————————————————————————————————————————————————— */

static inline int getRepoInfo(
	git_reference **const head, git_object **const commit, const char **const branch_name,
	git_status_list **const status_list, size_t *status_count, git_repository *const repo
) {
	int error = 0;

	/* ———————————————————————————————————————————————————————————————————————————————— */

	error = git_repository_head(head, repo); // get the HEAD reference (current branch)

	switch (error) {
		case 0					: break;
		case GIT_ENOTFOUND		: return error; // `head` is missing
		case GIT_EUNBORNBRANCH	: return error; // points to a branch that doesn't exist
		default					: return error; // other error - error is an `errno` code
	}

	/* ——————————————————————————————————————————————————————— */

	error = git_reference_peel(commit, *head, GIT_OBJECT_COMMIT); // resolve HEAD to the latest commit object

	switch (error) {
		case 0				: break;
		case GIT_ENOTFOUND	: return error; // `head` is missing
		case GIT_EAMBIGUOUS	: return error; // ambiguous commit
		default				: return error; // unknown error
	}

	/* ———————————————————————————————————————————————————————————————————————————————— */

	/** The name of the branch. May be the alnum name (e.g. `main`), or the branch hash. */
	*branch_name = getBranchName(*head);

	/* ———————————————————————————————————————————————————————————————————————————————— */

	// from the repo, get the status of all ignored, modified, new, etc. files
	const git_status_options opts = STATUS_OPT_OBJ_INIT;
	error = git_status_list_new(status_list, repo, &opts);

	switch (error) {
		case 0	: break;
		default	: return error; // error is an `errno` code
	}

	*status_count = git_status_list_entrycount(*status_list);

	/* ———————————————————————————————————————————————————————————————————————————————— */

	assert(error == 0);
	return error;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char *getBranchName(const git_reference *const head) {
	/** The name of the branch. May be the alnum name (e.g. `main`), or the branch hash. */
	const char *branch_name = git_reference_name(head);

	// if the branchname is formatted as, e.g., `origin/main`, then only keep the final segment, `main`
	const char *const branch_basename = strrchr(branch_name, '/');
	if (branch_basename != NULL) branch_name = branch_basename + 1;

	return branch_name;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#pragma GCC diagnostic pop

// spell:ignoreRegexp /\bGIT_E\B|(?<=\n\s*#.+"-)W/g
