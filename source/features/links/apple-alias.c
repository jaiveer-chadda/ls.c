/// @file features/links/apple-alias.c

#include <stdio.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "apple-alias.h"

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t alias_path) {
	*is_valid_alias = false;

	// convert `alias_path` to a CFURL object
	const CFURLRef alias_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ kCFAllocatorDefault,
		/* buffer		*/ (const UInt8 *)alias_path,
		/* bufLen		*/ (CFIndex)strlen(alias_path),
		/* isDirectory	*/ false
	);

	if (!alias_url) return false; //= is not an apple alias

	// read the alias file into a bookmark `CFData` object
	CFErrorRef error_;
	const CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ kCFAllocatorDefault,
		/* fileURL	 */ alias_url,
		/* errorRef	 */ &error_
	);

	// we don't care about the error, but I also don't want to cause memory leaks lol
	if (error_) CFRelease(error_);

	if (!bookmark_data) {
		CFRelease(alias_url);
		return false; //= is not an apple alias
	}

	// extract the stored metadata
	const CFStringRef alias_path_ref = CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ kCFAllocatorDefault,
		/* key		 */ kCFURLPathKey,
		/* bookmark	 */ bookmark_data
	);

	if (alias_path_ref) {
		path_t target_path;

		// using `FileSystemRepresentation` here to ensure that APFS Unicode normalisation is handled safely
		if (CFStringGetFileSystemRepresentation(
			/* string	 */ alias_path_ref,
			/* buffer	 */ target_path,
			/* maxBufLen */ sizeof(target_path)
		)) {
			strcpy(target_buffer, target_path);
			*is_valid_alias = FILE_EXISTS(target_path);
		}

		CFRelease(alias_path_ref);
	}

	// clean up the rest of the allocated CoreFoundation memory
	CFRelease(bookmark_data);
	CFRelease(alias_url);

	return true; //= IS an apple alias
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
