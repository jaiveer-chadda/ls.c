/// @file features/links/print.c

#include <stdio.h>
#include <assert.h>
#include <string.h> // strerror(), strncpy(), strlen()

#include "malloc.h"
#include "debugging.h"
#include "output/output.h"
#include "options/options.h" // LINKS_TO_LINKS()
#include "features/features.h" // getBasename(), print_mount()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline void print_link_internal(
	const TargetInfo *const target, const suff_t suffix, const error_t err_no,
	const lines_t lines, const uint8_t depth, size_t *const line_len
) {
	if (target == NULL && suffix != SYMLINK_SUFFIX) return;

	/* —— Target Error ———————————————————————————————————————— */

	if (target == NULL) {
		/*TEMP:*/ {
			putchar('\n');
			*line_len = getTotalLen(); // note: resetting the line len due to the newline
			print_empty_tree_addlen(lines, depth, LAST_TREE_BRANCH, line_len);
		}

		const char
			*const arrow_ansi = getcol(INVALID_ARROW_COLOUR	),
			*const punct_ansi = getcol(LINK_ERR_PUNCT_COL	),
			*const error_ansi = getcol(LINK_ERR_MSG_COL		);

		assert(0 <= err_no && err_no <= ELAST);

		const size_t errno_len = (
			err_no <  10 ?	1 :
			err_no < 100 ?	2 :
			/**/			3
		);
		const char *const errstr = strerror(err_no);
		const size_t errstr_len	 = strlen(errstr);

		printf("%s%s%s[ "
			/**/		"%serror %"ERROR_T_FMT"%s:"
			/**/								  "%s %s %s]",
			arrow_ansi, EACCES_ARROW, punct_ansi,
			error_ansi, err_no		, punct_ansi,
			error_ansi, errstr		, punct_ansi
		);

		*line_len += STRLEN("[ error :  ]") + ARROW_LEN + errno_len + errstr_len;

		setActive(LINK_ERR_PUNCT_COL);
		return;
	}

	/* —— Invalid Target —————————————————————————————————————— */

	const char *const arrow = target->is_apple ? APPLE_ARROW : SYMLINK_ARROW;
	const char *const path  = target->abspath + target->path_off;

	*line_len += ARROW_LEN;

	// if this is an invalid link
	if (target->suffix == INVALID_LINK) {
		const char *const arrow_ansi = getcol(INVALID_ARROW_COLOUR);

		printf("%s%s", arrow_ansi, arrow);
		printEscdNameLen(path, INVALID_LINK_COLOUR, false, line_len);

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

		printEscdNameLen(dirname, LINK_PATH_COLOUR, false, line_len);
		printEscdNameLen(basename + 1, file_colour_esc[target->colour], false, line_len);

	} else {
		// if we didn't find a basename, then the path is relative, and we should just print it all at once
		printEscdNameLen(path, file_colour_esc[target->colour], false, line_len);
	}

	/* —— Print Suffix & Mount Info ——————————————————————————— */

	// if the path should have a suffix, then reset colours and print the suffix
	if (do_suffix() && target->suffix != '\0') {
		printf("%s%c", getcol(RESET_ALL), target->suffix);
		(*line_len)++;
	}

	// print info about the target's mount device / mounted filesystems
	print_mount(target->mount, line_len);

	/* —— Recurse ————————————————————————————————————————————— */

	if (LINKS_TO_LINKS()) {
		// note: the `depth` doesn't change between recurses,
		//	since the subsequent links will all be printed on the same level
		print_link_internal(target->target, target->suffix, target->targ_err, lines, depth, line_len);
		efree(target->target);
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_link(const FileStat *const pFS, const lines_t lines, const uint8_t depth, size_t *const line_len) {
	if (pFS->f != NULL) print_link_internal(
		pFS->f->target, pFS->suffix, pFS->f->targ_err, lines, depth + 1, line_len
	);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
