/// @file output/tree.c

#include <stdio.h>
#include <string.h>

#include "form/formatting.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_tree(lines_t new_lines, const lines_t lines, const uint8_t depth, const bool is_last) {
	// for depth 0 (the original inputs), there aren't any tree levels to print
	if (depth == 0) return;

	colprint(PUNCT);

	for (int level = 0; level < depth - 1; level++) {
		printf("%*s" "%s",
			level == 0 ? TREE_LV1_PAD : TREE_PAD, "", // add 2 spaces of padding on every level except the 1ˢᵗ one
			lines[level] ? TREE_VERT : " " // only if this level needs a line should you print one
		);
	}

	printf("%*s" "%s%s",
		// add 2 spaces of padding on every level except the 1ˢᵗ one
		depth == 1 ? TREE_LV1_PAD : TREE_PAD, "",
		// print `├` before every file except the last one, where we print `└`
		is_last ? TREE_CORNER : TREE_BRANCH,
		TREE_HORI
	);

	if (new_lines == NULL) return;

	// populate the new line array with the contents of the old one
	memcpy(new_lines, lines, sizeof(lines_t));
	// then set the most recent line to `true` _iff_ there are more files to print on this level
	new_lines[depth - 1] = !is_last;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
