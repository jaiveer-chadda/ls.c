/// @file features/links/apple-alias.c

#include <stdio.h>
#include <magic.h>
#include <unistd.h>

#include "apple-alias.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void getType(const path_t file_path) {
	// init the magic cookie - `MAGIC_NONE` means we want standard text descriptions (like `/usr/bin/file`).
	magic_t magic_cookie = magic_open(
		MAGIC_NONE					// No special handling.
		| MAGIC_PRESERVE_ATIME		// Attempt to preserve the access time of files analysed.
		| MAGIC_COMPRESS_TRANSP		// Don't report on compression, only report about the uncompressed data.
		| MAGIC_NO_CHECK_COMPRESS	// Don't look inside compressed files.
		| MAGIC_NO_CHECK_ENCODING	// Don't check text encodings.
		| MAGIC_NO_CHECK_TEXT		// Don't check for various types of text files.
	);

	if (magic_cookie == NULL) return;

	// load the magic database (passing NULL tells it to load the default system database)
	if (magic_load(magic_cookie, NULL) != 0) {
		magic_close(magic_cookie);
		return;
	}

	const char *file_description = magic_file(magic_cookie, file_path);
	if (file_description == NULL) return;

	printf("%-42s\t\t%s\n", file_path, file_description);

	magic_close(magic_cookie);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
