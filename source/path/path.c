/// @file path/path.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../model/stat-model.h"

int resolvePath(void) {
	char *PATH = malloc(MAX_PATH_LEN);

	if (PATH == NULL)						{			 perror("malloc"); return 1; }
	if (getcwd(PATH, MAX_PATH_LEN) == NULL)	{ free(PATH); perror("getcwd"); return 1; }

	puts(PATH); free(PATH);
	return 0;
}
