/// @file icons/icon-config.c

#include <string.h>

#include "debugging.h"
#include "features/features.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define DEFAULT_CONFIG_DIR_NAME	"looksee"
#define DEFAULT_ICON_FILE_NAME	"icons.conf"

#define XDG_CONFIG_HOME			"XDG_CONFIG_HOME"
#define LKS_CONFIG_DIR			"LKS_CONFIG_DIR"
#define LKS_ICON_CONFIG			"LKS_ICON_CONFIG"

/* ——————————————————————————————————————————————————————————————— */

#define GET_PATH(segment, func) \
	(( (segment) = (func) ) != NULL && (segment)[0] == '/')

#define SET_BUFFER_TO(path) (bufptr += strlcpy(buffer, (path), sizeof(buffer)))
#define ADD_TO_BUFFER(path) (bufptr += strlcpy(bufptr, (path), sizeof(buffer)))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const char *getIconConfigPath(void) {
	static const char *icon_conf_file, *lks_conf_dir, *xdg_conf_home, *home;
	static bool did_init = false;

	if (did_init) return icon_conf_file;
	did_init = true;

	/* ——————————————————————————————————————————————————————————————— */

	// note: `icon_conf_file` will point to `buffer` iff the `$LKS_ICON_CONFIG` environment variable is unset
	//			otherwise, `icon_conf_file` will just point to the `$LKS_ICON_CONFIG` variable itself

	static path_t buffer = {0};
	static char	 *bufptr = buffer;

	if (GET_PATH(icon_conf_file	, getenv(LKS_ICON_CONFIG) )) {								 goto complete	; }
	if (GET_PATH(lks_conf_dir	, getenv(LKS_CONFIG_DIR	) )) { SET_BUFFER_TO(lks_conf_dir ); goto mk_ic_path; }
	if (GET_PATH(xdg_conf_home	, getenv(XDG_CONFIG_HOME) )) { SET_BUFFER_TO(xdg_conf_home); goto mk_lks_dir; }
	if (GET_PATH(home			, getHOME(NULL)			  )) { SET_BUFFER_TO(home		  ); goto mk_xdg_dir; }

	return ( icon_conf_file = NULL ); // failure - no user config available - use default config

	/* ——————————————————————————————————————————————————————————————— */

	mk_xdg_dir: ADD_TO_BUFFER("/" ".config"				 ); // we have `$HOME`			  - append `/.config`
	mk_lks_dir: ADD_TO_BUFFER("/" DEFAULT_CONFIG_DIR_NAME); // we have `$XDG_CONFIG_HOME` - append `/looksee`
	mk_ic_path: ADD_TO_BUFFER("/" DEFAULT_ICON_FILE_NAME ); // we have `$LKS_CONFIG_DIR`  - append `/icons.conf`
	icon_conf_file = buffer;
	complete  :												// we have `$LKS_ICON_CONFIG` - success !

	/* ——————————————————————————————————————————————————————————————— */

	return icon_conf_file;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
