/// @file features/links/symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils/malloc.h"
#include "model/stat-model.h"
#include "features/path/path.h"
#include "features/mode/mode.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path) {
	path_t link;

	const ssize_t path_len = readlink(link_path, link, sizeof(path_t));
	link[path_len] = '\0';

	/* ————————————————————————————————————————————————————— */

	// this memory is freed once the link is printed (in `printSymlink()`)
	// ReSharper disable once CppLocalVariableMayBeConst
	link_t link_str = emalloc(sizeof(char) * MAX_PATH_LEN);

	abbrPath(link_str, link);

	return link_str;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
