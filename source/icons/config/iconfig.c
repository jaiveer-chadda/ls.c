/// @file icons/config/iconfig.c

#include <stdio.h>

#include "iconfig.h"
#include "icons/icons.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void initIconConfig(void) {

	static bool did_init = false;

	if (did_init) return;
	did_init = true;

	/* ——————————————————————————————————————————————————————————————— */

	const char *const config_path = getIconConfigPath();

	printf("%s\n", config_path);

	/* ——————————————————————————————————————————————————————————————— */

}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
