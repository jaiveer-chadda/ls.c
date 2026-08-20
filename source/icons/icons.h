/**
 * @file icons/icons.h
 *
 * ACKNOWLEDGEMENTS
 * ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *	- With great thanks to the [eza project](https://github.com/eza-community/eza), from whom many of the icon
 *	  definitions and mappings have been copied verbatim.
 *		- See the following file for the original source (accessed at commit 4a7bfa58fc864bed516678a8aa35fe3793f3b4a5):
 *		- <https://github.com/eza-community/eza/blob/main/src/output/icons.rs>
 *
 *	- Thanks in particular to [Robert Minsk](https://github.com/cfxegbert), who seems to have created most of the
 *	  icon mappings in eza's original `icons.rs`.
 *
 *	- The eza project is [licenced](https://github.com/eza-community/eza/blob/main/LICENSE.txt) under the
 *	  [European Union Public License v.1.2](https://eupl.eu/1.2/en/).
 */

#ifndef ICONS_INITIALISED
#define ICONS_INITIALISED

#include <wchar.h>
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

icon_t getIcon(const char *filename);
void printIcon(const icon_t icon, const FileColour file_col);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	char *match;
	wchar_t icon;
} Icon;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// An array containing the basenames of directories, and their associated icons.
/// This array should contain all the directories that have custom icons.
extern const Icon DIR_ICONS[];
/// Array containing full filenames & their icons.
extern const Icon FILENAME_ICONS[];
/// Array of lowercase file extensions and their icons.
extern const Icon EXT_ICONS[];

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !ICONS_INITIALISED */
