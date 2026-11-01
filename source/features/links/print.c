/// @file features/links/print.c

#include <stdio.h>
#include <string.h> // strerror(), strncpy()

#include "malloc.h"
#include "output/output.h"
#include "options/options.h" // LINKS_TO_LINKS()
#include "features/features.h" // getBasename(), print_mount()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void print_link_internal(const TargetInfo *const target, const suff_t suffix, const error_t err_no) {

	if (target == NULL && suffix != SYMLINK_SUFFIX) return;

	/* —— Target Error ———————————————————————————————————————— */

	if (target == NULL) {
		const char
			*const arrow_ansi = getcol(INVALID_ARROW_COLOUR	),
			*const punct_ansi = getcol(LINK_ERR_PUNCT_COL	),
			*const error_ansi = getcol(LINK_ERR_MSG_COL		);

		printf("%s%s%s[ "
			/**/		"%serror %"ERROR_T_FMT"%s:"
			/**/								  "%s %s %s]",
			arrow_ansi, EACCES_ARROW	, punct_ansi,
			error_ansi, err_no			, punct_ansi,
			error_ansi, strerror(err_no), punct_ansi
		);

		setActive(LINK_ERR_PUNCT_COL);
		return;
	}

	/* —— Invalid Target —————————————————————————————————————— */

	const char *const arrow = target->is_apple ? APPLE_ARROW : SYMLINK_ARROW;
	const char *const path  = target->abspath + target->path_off;

	// if this is an invalid link
	if (target->suffix == INVALID_LINK) {
		const char *const arrow_ansi = getcol(INVALID_ARROW_COLOUR);

		printf("%s%s", arrow_ansi, arrow);
		printEscdName(path, INVALID_LINK_COLOUR, false);

		return;
	}

	/* —— Print & Colour Target ——————————————————————————————— */

	const char *const basename = getBasename(path);

	// print the arrow - different based on whether it's an apple link or normal symlink
	printf("%s%s", getcol(VALID_ARROW_COLOUR), arrow);

	// if we found a basename, then print the dirname and basname sequentially
	if (basename != NULL) {
		// copy the path up to where the basename starts
		path_t dirname = {0};
		strncpy(dirname, path, (basename + 1) - path);

		printEscdName(dirname, LINK_PATH_COLOUR, false);
		printEscdName(basename + 1, file_colour_esc[target->colour], false);

	} else {
		// if we didn't find a basename, then the path is relative, and we should just print it all at once
		printEscdName(path, file_colour_esc[target->colour], false);
	}

	/* —— Print Suffix & Mount Info ——————————————————————————— */

	// if the path should have a suffix, then reset colours and print the suffix
	if (target->suffix != '\0') printf("%s%c", getcol(RESET_ALL), target->suffix);

	// print info about the target's mount device / mounted filesystems
	print_mount(target->mount);

	/* —— Recurse ————————————————————————————————————————————— */

	if (LINKS_TO_LINKS()) {
		print_link_internal(target->target, target->suffix, err_no);
		efree(target->target);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_link(const FileStat *const pFS) {
	if (pFS->f != NULL) print_link_internal(pFS->f->target, pFS->mode, pFS->err_no);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
