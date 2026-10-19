/// @file features/git/git.c

#include <git2.h>
#include <stdio.h>
#include <assert.h>
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
	if (branch_name == NULL) return NULL;

	// if the branchname is formatted as, e.g., `origin/main`, or `ref/head/branch`, then only keep the final segment
	const char *const branch_basename = strrchr(branch_name, '/');
	if (branch_basename != NULL) branch_name = branch_basename + 1;

	return estrdup(branch_name);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define GIT_DIR_PATH "/.git"
#define GIT_DIR_LEN ((size_t)(sizeof(GIT_DIR_PATH) - 1))

private const char *getRelativePath(const char *const file, const char *root) {
	size_t root_len = strlen(root);

	// if the repo root ends with a `/`, then cut that slash off
	if (root[root_len - 1] == '/') root_len--;

	// if the repo root ends with `/.git`, then cut that off as well
	if (strncmp(&root[root_len - GIT_DIR_LEN], GIT_DIR_PATH, GIT_DIR_LEN) == 0) {
		root_len -= GIT_DIR_LEN;
	}

	/* ——————————————————————————————————————————————————————— */

	size_t i;
	for (i = 0; i < root_len; i++) {
		if (file[i] != root[i]) return NULL;
	}

	// `file` == `root` || `file` == `/.git`  then `file` is the root of the repo
	if (file[i] == '\0' || strncmp(file, GIT_DIR_PATH, GIT_DIR_LEN)) return "";

	// +1 to discard the leading `/`
	return file + i + 1;
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
	GitInfo *git_info_obj = NULL;

	git_repository *repo = NULL; /** Repr. of an existing git repo, including all its object contents. */
	git_reference  *head = NULL; /** Information about the current branch of a repo. */

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	// fill out the repo, branch, and commit info, returning `NULL` if any of them can't be found
	if (git_repository_open_ext(&repo, pFS->abspath, 0, NULL) != 0) RETURN(NULL); // open the repo
	if (git_repository_head(&head, repo) != 0) RETURN(NULL); // get the HEAD reference (current branch)

	/* ——————————————————————————————————————————————————————— */

	const char *const repo_root = git_repository_commondir(repo);
	if (repo_root == NULL) RETURN(NULL);

	const char *const rel_path = getRelativePath(pFS->abspath, repo_root);
	if (rel_path == NULL) RETURN(NULL);

	const bool file_is_root = (rel_path[0] == '\0');

	git_status_t status = -1;

	// if this file isn't the repo's root
	if (!file_is_root) {
		switch (git_status_file(&status, repo, rel_path)) {
			case  0				: break;
			case GIT_ENOTFOUND	: puts("file not in repo"); RETURN(NULL);
			case -1				: puts("other error"	 ); RETURN(NULL);
			default				: puts("unknown error"	 ); RETURN(NULL);

			case GIT_EAMBIGUOUS	: {
				if (S_ISDIR(pFS->mode)) {
					/// @todo find a way to determine the status(es) of all child files
				}
				puts("-- ambiguous --");
				RETURN(NULL);
			}
		}
	}

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	git_info_obj = emalloc(sizeof(GitInfo));
	*git_info_obj = (GitInfo){ .status = status };
	setLen(FI_git_info, /*TEMP:*/8);

	if (file_is_root) {
		git_info_obj->repo = emalloc(sizeof(GitRepoInfo));
		*git_info_obj->repo = (GitRepoInfo){
			.branchname = getBranchName(head),
			.status = GBR_UPTODATE /** @todo figure out the actual branch status */
		};
	}

	/* —————————————————————————————————————————————————————————————————————————————————————————————— */

	printf("relative  : %s\n", rel_path);
	printf("from repo : %s\n", repo_root);
	if ( file_is_root) printf("on branch : %s\n", git_info_obj->repo->branchname);
	if ( file_is_root) printf("repo stat : %d\n", git_info_obj->repo->status);
	if (!file_is_root) printf("file stat : %d\n", status);

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
	const GitInfo *const git_info = pFS->f->git;

	printf("%s%*d", getcol(RESET_ALL), getLen(FI_git_info), git_info->status);

	/* ——————————————————————————————————————————————————————— */

	if (git_info->repo != NULL) efree((void*)git_info->repo->branchname);
	efree((void*)git_info->repo);
	efree((void*)git_info);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /\bGIT_E\B|\\(?:e|0?33)\[[0-9;]*m\B/g
