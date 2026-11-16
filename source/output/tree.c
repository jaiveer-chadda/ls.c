/// @file output/tree.c

#include <string.h>

#include "strings.h"
#include "form/formatting.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void print_tree(
	lines_t new_lines, const lines_t lines, const uint8_t depth, const bool is_last, size_t *const line_len
) {
	// for depth 0 (the original inputs), there aren't any tree levels to print
	if (depth == 0) return;

	colprint(PUNCT);

	/* ——————————————————————————————————————————————————————————————— */

	// print all leading lines
	for (int level = 0; level < depth - 1; level++) {
		// add 2 spaces of padding on every level except the 1ˢᵗ one, in which case, add 1
		const int leading_pad = (level == 0 ? TREE_LV1_PAD : TREE_PAD);
		putspaces(leading_pad);

		static const wchar_t *const vert_str = TREE_VERT;
		static const size_t vert_str_len = STRLEN(TREE_VERT);

		if (lines[level] == true) {
			printf("%ls", vert_str); // print a line if this level needs one
		} else {
			putspaces(vert_str_len); // otherwise, print an equivalent number of spaces
		}

		if (line_len != NULL) *line_len += leading_pad + vert_str_len;
	}

	/* ——————————————————————————————————————————————————————————————— */

	// add 2 spaces of padding on every level except the 1ˢᵗ one
	const int tree_pad = (depth == 1 ? TREE_LV1_PAD : TREE_PAD);
	putspaces(tree_pad);

	// print `├─` before every file, except the last one, where we print `└─`
	const wchar_t *const branch_str	= is_last ?		   TREE_CORNER	:		 TREE_BRANCH;
	const size_t branch_str_len		= is_last ? STRLEN(TREE_CORNER) : STRLEN(TREE_BRANCH);

	static const wchar_t *const horiz_str = TREE_HORI;
	static const size_t horiz_str_len = STRLEN(TREE_HORI);

	printf("%ls%ls", branch_str, horiz_str);

	// incrememt line length
	if (line_len != NULL) *line_len += tree_pad + branch_str_len + horiz_str_len;

	/* ——————————————————————————————————————————————————————————————— */

	if (new_lines != NULL) {
		// populate the new line array with the contents of the old one
		memcpy(new_lines, lines, sizeof(lines_t));
		// then set the most recent line to `true` _iff_ there are more files to print on this level
		new_lines[depth - 1] = !is_last;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
