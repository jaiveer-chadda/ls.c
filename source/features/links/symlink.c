/// @file features/links/symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils/malloc.h"
#include "model/stat-model.h"
#include "features/path/path.h"
#include "features/mode/mode.h"

#include "debugging/debugging.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path) {
	path_t target_path = "";

	// TODO: handle this
	const ssize_t target_path_len = readlink(link_path, target_path, sizeof(path_t));
	target_path[target_path_len != -1 ? target_path_len : 0] = '\0';

	/* ————————————————————————————————————————————————————— */

	// this memory is freed once the target is printed (in `printSymlink()`)
	// ReSharper disable once CppLocalVariableMayBeConst
	link_t target_str = emalloc(sizeof(path_t));

	abbrPath(target_str, target_path);
	return target_str;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
