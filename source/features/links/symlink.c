/// @file features/links/symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../mode/mode.h"
#include "../path/path.h"
#include "../../model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path) {
	path_t link;

	const ssize_t path_len = readlink(link_path, link, sizeof(path_t));
	link[path_len] = '\0';

	/* ————————————————————————————————————————————————————— */

	// this memory is freed once the link is printed (in `printSymlink()`)
	// ReSharper disable once CppLocalVariableMayBeConst
	link_t link_str = malloc(sizeof(char) * MAX_PATH_LEN);

	if (link_str == NULL) {
		perror(ERROR "malloc:link_str");
		exit(EXIT_FAILURE);
	}

	abbrPath(link_str, link);

	return link_str;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
