/// @file features/links/symlink.c

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "utils/malloc.h"
#include "model/stat-model.h"
#include "features/path/path.h"

#include "debugging/debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path) {
	path_t target_path = "";

	const ssize_t target_path_len = readlink(link_path, target_path, sizeof(path_t));
	const int readlink_errno = errno;

	#ifndef DEBUG_MODE
	(void)readlink_errno; // `readlink_errno` will be unused when not in debug mode
	#endif

	if (target_path_len == -1) {
		debug(WARNING, "%s", strerror(readlink_errno));
		target_path[0] = '\0';
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
