/// @file features/git.c

#include <git2.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "hash.h"
#include "malloc.h"
#include "debugging.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GIT_STATUS_OPTS_FLAGS ((unsigned int)(	\
	GIT_STATUS_OPT_INCLUDE_IGNORED			|	\
	GIT_STATUS_OPT_INCLUDE_UNTRACKED		|	\
	GIT_STATUS_OPT_INCLUDE_UNMODIFIED		|	\
	GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX	|	\
	GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS	|	\
	GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR		\
))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int getGitStatusList(git_status_list **const status_list, git_repository *const repo);
static inline int getBasicCommitInfo(
	git_repository **const repo, git_reference **const head, git_object **const commit, const char *const path
);

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

#define RETURN goto LABEL_RETURN

GitInfo *getGitInfo(const FileStat *const pFS) {
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

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	// fill out the repo, branch, and commit info, returning `NULL` if one of them can't be found
	int error = getBasicCommitInfo(&repo, &head, &commit, pFS->path);

	// TEMP: this switch statement is currently just being used to print debugging messages
	switch (error) {
		case 0: break;
		case GIT_ENOTFOUND: printf("file      : %s \33[91m( not in git repo )\33[m\n", pFS->display);
		/*[[fallthrough]];*/
		default: RETURN;
	}
	// this is what the switch statement will eventually be replaced with
	if (error != 0) RETURN;

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	/// I'm making the executive decision to not handle bare repos. With how complicated `git` already is, I don't need
	///  any more unnecessary complexity, and they're so rare that they're not worth considering.
	/// @todo I may add support for them later, but not while I'm still setting the system up.
	if ((bool)git_repository_is_bare(repo)) RETURN;

	/* ——————————————————————————————————————————————————————— */

	/** The name of the branch. May be the alnum name (e.g. `main`), or the branch hash. */
	const char *branch_name = git_reference_name(head);

	// if the branchname is formatted as, e.g., `origin/main`, then only keep the final segment, `main`
	const char *const branch_basename = strrchr(branch_name, '/');
	if (branch_basename != NULL) branch_name = branch_basename + 1;

	/* ——————————————————————————————————————————————————————— */

	/** The path to the repo's `.git/` directory. */
	const char *const repo_root = git_repository_commondir(repo);

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
	const hash_t repo_hash = hashstr(repo_root);

	/* ——————————————————————————————————————————————————————— */

	printf("file      : %s\n", pFS->display);
	printf("from repo : %s\n", repo_root);
	printf("on branch : %s\n", branch_name);
	printf("repo hash : %llu\n", repo_hash);

	/* ——————————————————————————————————————————————————————— */

	// from the repo, get the status of all ignored, modified, new, etc. files
	error = getGitStatusList(&status_list, repo);
	if (error != 0) RETURN;

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	const size_t count = git_status_list_entrycount(status_list);
	if (count == 0) {
		/*TEMP:*/ puts("\33[32m( nothing to be tracked )\33[m");
		RETURN;
	}

	/* ——————————————————————————————————————————————————————— */

	for (size_t i = 0; i < count; ++i) {
		const git_status_entry *const entry = git_status_byindex(status_list, i);

		// check for errors, i.e. whether the entry we got, or its diff object, is `NULL`
		//	however, I don't actually know how I would catch/handle it - I think I'll just ignore it for now
		if (entry == NULL || entry->index_to_workdir == NULL) continue;

		const git_status_t status = entry->status;

		// since this is by far the most common case, this short-circuit saves us from doing all the checks below
		/** @todo
		 *	I may expand this single `status` check into a switch/case statement that short-circuits all of the
		 *		most common cases, and then check combined cases if a single.
		 *	This'd keep the `O(1)`/`O(log n)` complexity of switch/case statements for most cases, falling back to
		 *		a tower of `if`s (which is `O(n)`) for all cases in which a file has more than one flag.
		 */
		if (status == GIT_STATUS_CURRENT) continue;

		/*TEMP:*/ if (status == GIT_STATUS_IGNORED) continue; // temp so I don't have to see all the ignored files
		/*TEMP:*/ printf("\33[34m'%s'\33[m  \t: ", entry->index_to_workdir->old_file.path);

		/* ——————————————————————————————————————————————————————— */

		// staged
		if (status & GIT_STATUS_INDEX_NEW		) printf("INDEX_NEW "		);
		if (status & GIT_STATUS_INDEX_MODIFIED	) printf("INDEX_MODIFIED "	);
		if (status & GIT_STATUS_INDEX_DELETED	) printf("INDEX_DELETED "	);
		if (status & GIT_STATUS_INDEX_RENAMED	) printf("INDEX_RENAMED "	);
		if (status & GIT_STATUS_INDEX_TYPECHANGE) printf("INDEX_TYPECHANGE ");

		// unstaged
		if (status & GIT_STATUS_WT_NEW			) printf("WT_NEW "			);
		if (status & GIT_STATUS_WT_MODIFIED		) printf("WT_MODIFIED "		);
		if (status & GIT_STATUS_WT_DELETED		) printf("WT_DELETED "		);
		if (status & GIT_STATUS_WT_TYPECHANGE	) printf("WT_TYPECHANGE "	);
		if (status & GIT_STATUS_WT_RENAMED		) printf("WT_RENAMED "		);
		if (status & GIT_STATUS_WT_UNREADABLE	) printf("WT_UNREADABLE "	);

		// general
		if (status & GIT_STATUS_IGNORED			) printf("IGNORED "			);
		if (status & GIT_STATUS_CONFLICTED		) printf("CONFLICTED "		);

		putchar('\n');
	}

	/* —— */ LABEL_RETURN: /* ——————————————————————————————————————————————————————————————————————— */

	// free all allocations
	//	note: usually I wouldn't check for `NULL` when freeing things, but I don't know how these functions work, so
	//		I'd rather be safe than sorry
	if (commit		!= NULL) git_object_free(commit);
	if (head		!= NULL) git_reference_free(head);
	if (repo		!= NULL) git_repository_free(repo);
	if (status_list	!= NULL) git_status_list_free(status_list);

	/*TEMP:*/ dline();

	return git_info_obj;
}

#undef RETURN

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int getGitStatusList(git_status_list **const status_list, git_repository *const repo) {
	const git_status_options opts = {
		.version = GIT_STATUS_OPTIONS_VERSION,
		.show	 = GIT_STATUS_SHOW_INDEX_AND_WORKDIR,
		.flags	 = GIT_STATUS_OPTS_FLAGS,
	};

	const int error = git_status_list_new(status_list, repo, &opts);

	switch (error) {
		case 0	: break;
		default	: return error; // error is an `errno` code
	}

	assert(error == 0);
	return error;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int getBasicCommitInfo(
	git_repository **const repo, git_reference **const head, git_object **const commit, const char *const path
) {
	/// @todo print/store proper error messages for each of the caught errors
	int error = 0;

	/* ——————————————————————————————————————————————————————— */

	error = git_repository_open_ext(repo, path, 0, NULL); // open the repo

	switch (error) {
		case 0				: break;
		case GIT_ENOTFOUND	: return error; // repo not found (not a git repo)
		case -1				: return error; // repo found, but corruption/error while reading it
		default				: return error; // unknown error
	}

	/* ——————————————————————————————————————————————————————— */

	error = git_repository_head(head, *repo); // get the HEAD reference (current branch)

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

	/* ——————————————————————————————————————————————————————— */

	assert(error == 0);
	return error;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {
	/*TEMP:*/ (void)pFS;
	/*TEMP:*/ printf("%s%s", getcol(RESET_ALL), "gitinfo");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /\bGIT_E\B|commit|(?<=\n\s*#.+"-)W/g
