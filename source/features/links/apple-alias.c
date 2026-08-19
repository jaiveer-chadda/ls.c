/// @file features/links/apple-alias.c

#include <stdio.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "apple-alias.h"

#include "debugging/debugging.h"

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t alias_path) {
	*is_valid_alias = false;

	/* ——————————————————————————————————————————————————————————— */

	// convert `alias_path` to a CFURL object
	const CFURLRef alias_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ NULL,
		/* buffer		*/ (const UInt8 *)alias_path,
		/* bufLen		*/ (CFIndex)strlen(alias_path),
		/* isDirectory	*/ false
	);

	if (alias_url == NULL) return false;

	/* ——————————————————————————————————————————————————————————— */

	// read the alias file into a bookmark `CFData` object
	const CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ NULL,
		/* fileURL	 */ alias_url,
		/* errorRef	 */ NULL
	);
	CFRelease(alias_url);

	if (bookmark_data == NULL) return false;

	/* ——————————————————————————————————————————————————————————— */

	// extract the stored metadata
	const CFStringRef alias_string = CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ NULL,
		/* key		 */ kCFURLPathKey,
		/* bookmark	 */ bookmark_data
	);
	CFRelease(bookmark_data);

	/* ——————————————————————————————————————————————————————————— */

	if (alias_string != NULL) {
		// TODO: handle this
		CFStringGetFileSystemRepresentation(
			/* string	 */ alias_string,
			/* buffer	 */ target_buffer,
			/* maxBufLen */ sizeof(path_t)
		);

		*is_valid_alias = FILE_EXISTS(target_buffer);
	}

	CFRelease(alias_string);

	/* ——————————————————————————————————————————————————————————— */

	return true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
