/// @file features/git/git.c

#include <stdio.h>
#include <stdbool.h>

#include "malloc.h"
#include "strings.h"
#include "debugging.h"
#include "form/formatting.h"

/* ——————————————————————————————————————————————————————— */

/// I'm including these `.c` files directly, so that I can keep the performace benefits of
///	 using `static inline` functions, but I can also keep things neat & separated.
#include "_git.h"
#include "_repo.c"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define RETURN goto LABEL_RETURN

static GitRepoInfo *all_repos = NULL;
static size_t repo_count = 0, repo_alloc = 0;

static bool did_init = false;

static inline void initGitState(void) {
	if (did_init) return;
	if (git_libgit2_init() != 1) debug(WARNING, "libgit2 initialised more than once");
	did_init = true;
}

void freeGitState(void) {
	for (size_t i = 0; i < repo_count; i++) {
		const GitRepoInfo *const repo = &all_repos[i];

		for (uint32_t j = 0; j < repo->count; j++) {
			efree((void*)repo->files[j].path);
		}

		efree((void*)repo->files);
		efree((void*)repo->root);
		git_repository_free(repo->repo_obj);
	}

	efree(all_repos);

	if (!did_init) return;
	if (git_libgit2_shutdown() != 0) debug(WARNING, "libgit2 not fully shut down");
	did_init = false;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const GitInfo *getGitInfo(const FileStat *const pFS) {
	printf("file      : %s", pFS->abspath);

	// initialise `libgit2`'s global state
	//	note: this state will be released by `main`, at the end of the program
	initGitState();

	/* ——————————————————————————————————————————————————————— */

	/** A pointer to the `GitInfo` object we're creating, which will be returned by the function. */
	const GitInfo *git_info_obj = NULL;

	git_repository	*repo	= NULL; /** Repr. of an existing git repo, including all its object contents. */
	git_reference	*head	= NULL; /** Information about the current branch of a repo. */
	git_object		*commit	= NULL; /** Info about the commmit that the branch `head` is at. */

	// note: this is defined earlier than it needs to be, so that the `goto LABEL_RETURN` statement works correctly
	git_status_list *status_list = NULL; /** The statuses of all ignored/modified/new/etc files in a repo. */

	/* ——————————————————————————————————————————————————————— */

	const char *repo_root; /** The path to the repo's `.git/` directory. */
	hash_t		repo_hash; /** The unique ID of the repo, based on the path to the repo's `.git` directory. */

	// fill out the repo, branch, and commit info, returning `NULL` if one of them can't be found
	if (getRepo(&repo, &repo_root, &repo_hash, pFS->path) != 0) RETURN;

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	// from this point on, we know for a fact that we're in a git repo
	/// @todo now check if the repo already exists
	///			based on that, branch off to either creating a new repo, or assigning one to a file

	GitRepoInfo *current_repo = NULL;

	for (size_t i = 0; i < repo_count; i++) {
		if (all_repos[i].hash == repo_hash) {
			current_repo = &all_repos[i];
			break;
		}
	}

	/* ——————————————————————————————————————————————————————— */

	if (current_repo != NULL) { // repo already exists!
		puts(" \33[33m( repo exists )\33[m");
		printf("from repo : %s\n", current_repo->root);

		if (strcmp(current_repo->root, pFS->abspath) == 0 ||
			strcmp(			repo_root, pFS->abspath) == 0
		) {
			// file is root of repo
		}

		for (uint32_t i = 0; i < current_repo->count; i++) {
			const GitInfo *const file = &current_repo->files[i];

			if (strends(pFS->abspath, file->path)) {
				git_info_obj = file;
				setLen(FI_git_info, /*TEMP:*/10);

				RETURN;
			}
		}

		RETURN;
	}

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */
	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	/// @todo if the repo doesn't exist, start creating a new one...

	/** The name of the branch. May be the alnum name (e.g. `main`), or the branch hash. */
	const char *branch_name;
	size_t status_count;

	if (getRepoInfo(&head, &commit, &branch_name, &status_list, &status_count, repo) != 0) RETURN;
	/*TEMP:*/ printf("\nfrom repo : %s\non branch : %s\nrepo hash : %llu\n", repo_root, branch_name, repo_hash);

	/* ——————————————————————————————————————————————————————— */

	if (repo_count + 1 > repo_alloc) {
		all_repos = erealloc(all_repos, MULT_BY_1_5(repo_alloc) * sizeof(GitRepoInfo));
	}

	GitRepoInfo *const repo_info = &all_repos[repo_count++];
	*repo_info = (GitRepoInfo){
		.root		= getRepoDirname(repo_root),
		.hash		= repo_hash,
		.branch		= branch_name,
		.repo_obj	= repo,
	};

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	uint32_t alloc = 0;

	for (size_t i = 0; i < status_count; ++i) {
		const git_status_entry *const entry = git_status_byindex(status_list, i);

		// check for errors, i.e. whether the entry we got, or its diff object, is `NULL`
		//	however, I don't actually know how I would catch/handle it - I think I'll just ignore it for now
		if (entry == NULL || entry->index_to_workdir == NULL) continue;

		const git_status_t status = entry->status;

		/* ——————————————————————————————————————————————————————— */

		if (repo_info->count + 1 > alloc) {
			repo_info->files = erealloc(repo_info->files, MULT_BY_1_5(alloc) * sizeof(GitInfo));
		}

		repo_info->files[repo_info->count++] = (GitInfo){
			.rp_hash = repo_info->hash,
			.status = status,
			.repo = repo_info,
			.path = estrdup(entry->index_to_workdir->old_file.path),
		};
	}

	/* —— */ LABEL_RETURN: /* ——————————————————————————————————————————————————————————————————————— */

	// free all allocations
	//	note: usually I wouldn't check for `NULL` when freeing things, but I don't know how these functions work, so
	//		I'd rather be safe than sorry
	if (commit		!= NULL) git_object_free(commit);
	if (head		!= NULL) git_reference_free(head);
	if (status_list	!= NULL) git_status_list_free(status_list);

	/* ——————————————————————————————————————————————————————— */

	/*TEMP:*/ dline();
	return git_info_obj;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char *getRepoDirname(const char *const repo_root) {
	const size_t root_len = strlen(repo_root);
	char *const root_end = memcpy(ecalloc(1, root_len + 1), repo_root, root_len + 1);

	char *const last_char = &root_end[root_len - 1];
	if (*last_char == '/') *last_char = '\0';

	char *const git_dir = strrchr(root_end, '/');
	if (git_dir != NULL) *git_dir = '\0';

	return root_end;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_git_info(const FileStat *const pFS) {
	if (pFS->f == NULL || pFS->f->git == NULL) {
		putspaces(getLen(FI_git_info));
		return;
	}

	printf("%s%*d", getcol(RESET_ALL), getLen(FI_git_info), pFS->f->git->status);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
