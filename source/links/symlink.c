/// @file links/symlinks.c

#include <stdio.h>

#include "../model/stat-model.h"

void getLink(char *link_str, path_t link_path) {
	sprintf(link_str, " --> %s", link_path);
}
