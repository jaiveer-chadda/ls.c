/// @file features/links/apple-alias.c

#include <stdio.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "apple-alias.h"

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t file_path) {
	bool is_apple_alias = false;
	*is_valid_alias = false;

	// convert `file_path` to a CFURL object
	const CFURLRef alias_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ kCFAllocatorDefault,
		/* buffer		*/ (const UInt8 *)file_path,
		/* bufLen		*/ (CFIndex)strlen(file_path),
		/* isDirectory	*/ false
	);

	if (!alias_url) return is_apple_alias;

	// read the alias file into a bookmark `CFData` object
	CFErrorRef error_;
	const CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ kCFAllocatorDefault,
		/* fileURL	 */ alias_url,
		/* errorRef	 */ &error_
	);

	// we don't care about the error, but I also don't want to cause memory leaks
	if (error_) CFRelease(error_);

	if (!bookmark_data) {
		CFRelease(alias_url);
		return is_apple_alias;
	}

	// extract the stored metadata
	const CFStringRef orig_path_ref = CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ kCFAllocatorDefault,
		/* key		 */ kCFURLPathKey,
		/* bookmark	 */ bookmark_data
	);

	if (orig_path_ref) {
		is_apple_alias = true;

		path_t target_path;

		// using `FileSystemRepresentation` here to ensure that APFS Unicode normalisation is handled safely
		if (CFStringGetFileSystemRepresentation(
			/* string	*/ orig_path_ref,
			/* buffer	*/ target_path,
			/* maxBufLen*/ sizeof(target_path)
		)) {
			// printf("target: %s\n", target_path);
			strcpy(target_buffer, target_path);

			*is_valid_alias = FILE_EXISTS(target_path);
		}

		CFRelease(orig_path_ref);
	}

	// clean up the rest of the allocated CoreFoundation memory
	CFRelease(bookmark_data);
	CFRelease(alias_url);

	return is_apple_alias;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
