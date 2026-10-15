/// @file features/git/_status.c

#include <stdio.h>
#include <assert.h>

#include "_git.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline int getGitStatusList(git_status_list **const status_list, git_repository *const repo) {
	const git_status_options opts = {
		.version = GIT_STATUS_OPTIONS_VERSION,
		.show	 = GIT_STATUS_SHOW_INDEX_AND_WORKDIR,
		.flags	 = (
			GIT_STATUS_OPT_INCLUDE_IGNORED			|
			GIT_STATUS_OPT_INCLUDE_UNTRACKED		|
			GIT_STATUS_OPT_INCLUDE_UNMODIFIED		|
			GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX	|
			GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS	|
			GIT_STATUS_OPT_RENAMES_INDEX_TO_WORKDIR
		)
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

static inline void parseStatuses(git_status_list *const status_list, const size_t status_count) {
	for (size_t i = 0; i < status_count; ++i) {
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
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#pragma GCC diagnostic pop
