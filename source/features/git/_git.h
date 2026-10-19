/// @file features/git/_git.h

#ifndef FEATURES_GIT_H_
#define FEATURES_GIT_H_

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#include <git2.h>

#include "hash.h"
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define E_BARE_REPO ((int)-2)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wundefined-internal"

/* ——————————————————————————————————————————————————————— */

static inline const char *getRepoDirname(const char *const repo_root);
static inline const char *getBranchName(const git_reference *const head);
static inline int getRepoInfo(
	git_reference **const head, git_object **const commit, const char **const branch_name,
	git_status_list **const status_list, size_t *status_count, git_repository *const repo
);
static inline int getRepo(
	git_repository **const repo, const char **const repo_root, hash_t *repo_hash, const char *const path
);
static inline const GitInfo *getFileInfo(
	const FileStat *const pFS, const GitRepoInfo *const repo, const char *const repo_root
);

/* ——————————————————————————————————————————————————————— */

#pragma GCC diagnostic pop

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !FEATURES_GIT_H_ */
