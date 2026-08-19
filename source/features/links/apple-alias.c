/// @file features/links/apple-alias.c

#include <stdio.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "apple-alias.h"

#include "debugging/debugging.h"

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t alias_path) {
	dfunc(resolveAppleAlias);
	*is_valid_alias = false;

	/* ——————————————————————————————————————————————————————————— */

	debug(DEBUG, "alias_path: \33[31m%s", alias_path);
	debug(INFO, "assigning alias_url");

	// convert `alias_path` to a CFURL object
	const CFURLRef alias_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ NULL,
		/* buffer		*/ (const UInt8 *)alias_path,
		/* bufLen		*/ (CFIndex)strlen(alias_path),
		/* isDirectory	*/ false
	);


	if (alias_url == NULL) {
		debug(ERROR, "alias_url == NULL - file is not apple alias");
		return false;
	}

	debug(SUCCESS, "alias_url != NULL");

	/* ——————————————————————————————————————————————————————————— */

	debug(INFO, "assigning bookmark_data");
	// read the alias file into a bookmark `CFData` object
	const CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ NULL,
		/* fileURL	 */ alias_url,
		/* errorRef	 */ NULL
	);
	debug(INFO, "releasing alias_url");
	CFRelease(alias_url);
	debug(SUCCESS, "released alias_url");

	if (bookmark_data == NULL) {
		debug(ERROR, "bookmark_data == NULL - file is not apple alias");
		return false;
	}

	debug(SUCCESS, "bookmark_data != NULL");

	/* ——————————————————————————————————————————————————————————— */

	debug(INFO, "assigning alias_string");
	// extract the stored metadata
	const CFStringRef alias_string = CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ NULL,
		/* key		 */ kCFURLPathKey,
		/* bookmark	 */ bookmark_data
	);
	debug(INFO, "releasing bookmark_data");
	CFRelease(bookmark_data);
	debug(SUCCESS, "released bookmark_data");

	/* ——————————————————————————————————————————————————————————— */

	if (alias_string != NULL) {
		debug(SUCCESS, "alias_string != NULL");
		// path_t target_path;

		// if (CFStringGetFileSystemRepresentation(
		// 	/* string	 */ alias_string,
		// 	/* buffer	 */ target_path,
		// 	/* maxBufLen */ sizeof(target_path)
		// )) {
		// 	debug(SUCCESS, "file is avalid alias");
		// 	strcpy(target_buffer, target_path);
		// 	*is_valid_alias = FILE_EXISTS(target_path);
		// } else {
		// 	debug(WARNING, "file is an invalid apple alias");
		// }

		CFStringGetFileSystemRepresentation(
			/* string	 */ alias_string,
			/* buffer	 */ target_buffer,
			/* maxBufLen */ sizeof(path_t)
		);

		debug(SUCCESS, "file is a valid alias");

		// strcpy(target_buffer, target_path);
		*is_valid_alias = FILE_EXISTS(target_buffer);

	} else {
		debug(WARNING, "alias_string == NULL - file is an invalid apple alias");
	}

	debug(INFO, "releasing alias_string");
	CFRelease(alias_string);
	debug(SUCCESS, "released alias_string");

	/* ——————————————————————————————————————————————————————————— */

	return true;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
