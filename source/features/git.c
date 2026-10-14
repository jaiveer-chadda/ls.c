/// @file features/git.c

#include <git2.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "malloc.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static bool did_init = false;

static inline void initGitState(void) { if (!did_init) git_libgit2_init		(); did_init = true; }
/**/		  void freeGitState(void) { if ( did_init) git_libgit2_shutdown	();					 }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

GitInfo *getGitInfo(const FileStat *const pFS) {

	return NULL;

	// initialise `libgit2`'s global state
	//	note: this state will be released by `main`, at the end of the program
	initGitState();

	git_status_list *list = NULL;
	git_repository	*repo = NULL;
	git_reference	*head = NULL;
	git_object		*comt = NULL;

	/* ——————————————————————————————————————————————————————— */

	const char *const path_to_get = /* (pFS->parent != NULL) ? pFS->parent->path : */ pFS->path;

	/* ——————————————————————————————————————————————————————— */

	/// @todo print/store proper error messages for each of the caught errors
	int error = 0;

	error = git_repository_open_ext(&repo, path_to_get, 0, NULL); // open the repo

	switch (error) {
		case 0				: break;
		case GIT_ENOTFOUND	: goto return_; // repo not found (not a git repo)
		case -1				: goto return_; // repo found, but corruption/error while reading it
		default				: goto return_; // unknown error
	}

	/* ——————————————————————————————————————————————————————— */

	error = git_repository_head(&head, repo); // get the HEAD reference (current branch)

	switch (error) {
		case 0: break;
		case GIT_ENOTFOUND		: goto return_; // `head` is missing
		case GIT_EUNBORNBRANCH	: goto return_; // points to a branch that doesn't exist
		default					: goto return_; // other error - `errno` was set
	}

	/* ——————————————————————————————————————————————————————— */

	error = git_reference_peel(&comt, head, GIT_OBJECT_COMMIT); // resolve HEAD to the latest commit object

	switch (error) {
		case 0: break;
		case GIT_ENOTFOUND	: goto return_; // `head` is missing
		case GIT_EAMBIGUOUS	: goto return_; // ambiguous commit
		default				: goto return_; // unknown error
	}

	/* ——————————————————————————————————————————————————————— */

	// GitInfo *const info = emalloc(sizeof(GitInfo));

	const char *branch_name = git_reference_name(head);
	const char *const branch_basename = strrchr(branch_name, '/');

	if (branch_basename != NULL) branch_name = branch_basename + 1;

	printf("\33[m\n%s - on branch %s\n", path_to_get, branch_name);

	/* ——————————————————————————————————————————————————————— */
	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

	git_status_options opts = GIT_STATUS_OPTIONS_INIT;

	#pragma GCC diagnostic pop

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.flags = (
		GIT_STATUS_OPT_INCLUDE_IGNORED			|
		GIT_STATUS_OPT_INCLUDE_UNTRACKED		|
		GIT_STATUS_OPT_INCLUDE_UNMODIFIED		|
		GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX	|
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS	|
		GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR
	);

	error = git_status_list_new(&list, repo, &opts);
	if (error != 0) goto return_;

	/* ——————————————————————————————————————————————————————— */

	const size_t count = git_status_list_entrycount(list);

	for (size_t i = 0; i < count; ++i) {
		const git_status_entry *const entry = git_status_byindex(list, i);
		if (entry == NULL) continue;

		if (entry->index_to_workdir	!= NULL) printf("\33[1;4;34m%s\33[m\n", entry->index_to_workdir->old_file.path);

		const git_status_t status = entry->status;

		// general
		if (status & GIT_STATUS_CURRENT			) puts("CURRENT			");
		if (status & GIT_STATUS_IGNORED			) puts("IGNORED			");
		if (status & GIT_STATUS_CONFLICTED		) puts("CONFLICTED		");

		// unstaged
		if (status & GIT_STATUS_WT_NEW			) puts("WT_NEW			");
		if (status & GIT_STATUS_WT_MODIFIED		) puts("WT_MODIFIED		");
		if (status & GIT_STATUS_WT_DELETED		) puts("WT_DELETED		");
		if (status & GIT_STATUS_WT_TYPECHANGE	) puts("WT_TYPECHANGE	");
		if (status & GIT_STATUS_WT_RENAMED		) puts("WT_RENAMED		");
		if (status & GIT_STATUS_WT_UNREADABLE	) puts("WT_UNREADABLE	");

		// staged
		if (status & GIT_STATUS_INDEX_NEW		) puts("INDEX_NEW		");
		if (status & GIT_STATUS_INDEX_MODIFIED	) puts("INDEX_MODIFIED	");
		if (status & GIT_STATUS_INDEX_DELETED	) puts("INDEX_DELETED	");
		if (status & GIT_STATUS_INDEX_RENAMED	) puts("INDEX_RENAMED	");
		if (status & GIT_STATUS_INDEX_TYPECHANGE) puts("INDEX_TYPECHANGE");

		putchar('\n');
	}

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	return_:

	// free all allocations
	if (comt != NULL) git_object_free(comt);
	if (head != NULL) git_reference_free(head);
	if (repo != NULL) git_repository_free(repo);
	if (list != NULL) git_status_list_free(list);

	static int iter_count = 0;

	if (iter_count++ == 0) {
		putchar('\n');
		exit(0);
	}

	return NULL;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {
	(void)pFS;
	printf("%s%s", getcol(RESET_ALL), "gitinfo");
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /\bGIT_E\B|comt|(?<=\n\s*#.+"-)W/g
