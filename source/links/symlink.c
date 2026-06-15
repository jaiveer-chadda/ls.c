/// @file links/symlinks.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../model/stat-model.h"
#include "../mode/mode.h"

#define ARROW " --> "

void getLink(char *link_str, path_t link_path) {
	path_t link;

	const ssize_t nbytes = readlink(link_path, link, sizeof(path_t));
	link[nbytes] = '\0';

	const char *HOME = getenv("HOME");

	const int home_len = strlen(HOME);
	const int path_len = strlen(link);

	if ( HOME != NULL
		&& home_len > 0
		&& home_len < path_len
		&& strncmp(HOME, link, home_len) == 0
	) {
		sprintf(link_str, ARROW "~%s", link + home_len);
	} else {
		sprintf(link_str, ARROW "%s", link);
	}
}
