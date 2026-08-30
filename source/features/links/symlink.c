/// @file features/links/symlink.c

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> // errno_t

#include "utils/malloc.h"
#include "model/stat-model.h"
#include "features/path/path.h"

#include "debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path) {
	path_t target_path = "";

	const ssize_t target_path_len = readlink(link_path, target_path, sizeof(path_t));
	const errno_t readlink_errno = errno;

	if (target_path_len == -1) {
		debug(WARNING, "%s: %s", link_path, strerror(readlink_errno));

		switch (readlink_errno) {
			case EACCES	: return NULL;
			default		: target_path[0] = '\0';
		}
	} else {
		target_path[target_path_len] = '\0';
	}

	/* ————————————————————————————————————————————————————— */

	// this memory is freed once the target is printed (in `printSymlink()`)
	// ReSharper disable once CppLocalVariableMayBeConst
	link_t target_str = emalloc(sizeof(path_t));

	abbrPath(target_str, target_path);
	return target_str;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
