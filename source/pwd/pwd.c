/// @file pwd/pwd.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../model/stat-model.h"

int printPWD(void) {
	char *PWD = malloc(MAX_PATH_LEN);

	if (PWD == NULL)						{			 perror("malloc"); return 1; }
	if (getcwd(PWD, MAX_PATH_LEN) == NULL)	{ free(PWD); perror("getcwd"); return 1; }

	puts(PWD); free(PWD);
	return 0;
}
