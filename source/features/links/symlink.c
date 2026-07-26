/// @file features/links/symlink.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../mode/mode.h"
#include "../../model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

link_t getLink(const path_t link_path) {
	path_t link;

	const ssize_t path_len = readlink(link_path, link, sizeof(path_t));
	link[path_len] = '\0';

	/* ————————————————————————————————————————————————————— */

	// this memory is freed once the link is printed (in `printSymlink()`)
	link_t link_str = malloc(sizeof(char) * MAX_PATH_LEN);

	if (link_str == NULL) {
		perror(ERROR "malloc:link_str");
		exit(EXIT_FAILURE);
	}

	/* ————————————————————————————————————————————————————— */

	const char *HOME = getenv("HOME");
	const int home_len = strlen(HOME);

	int bytes_written;

	if (HOME != NULL
		&& home_len > 0
		&& home_len < path_len
		&& strncmp(HOME, link, home_len) == 0
	) {
		bytes_written = sprintf(link_str, "~%s", link + home_len);
	} else {
		bytes_written = sprintf(link_str, "%s", link);
	}

	link_str[bytes_written] = '\0';

	/* ————————————————————————————————————————————————————— */

	return link_str;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
