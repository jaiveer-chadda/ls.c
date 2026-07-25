/// @file features/links/apple-alias.c

#include <stdio.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "apple-alias.h"

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void resolveAppleAlias(const path_t file_path) {
	// convert `file_path` to a CFURL object
	CFURLRef alias_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ kCFAllocatorDefault,
		/* buffer		*/ (const UInt8 *)file_path,
		/* bufLen		*/ strlen(file_path),
		/* isDirectory	*/ false
	);

	if (!alias_url) return;

	// read the alias file into a bookmark `CFData` object
	CFErrorRef error_;
	CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ kCFAllocatorDefault,
		/* fileURL	 */ alias_url,
		/* errorRef	 */ &error_
	);

	// we don't care about the error, but I also don't want to cause memory leaks
	if (error_) CFRelease(error_);

	if (!bookmark_data) {
		CFRelease(alias_url);
		return;
	}

	// extract the stored metadata
	CFStringRef orig_path_ref = (CFStringRef)CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ kCFAllocatorDefault,
		/* key		 */ kCFURLPathKey,
		/* bookmark	 */ bookmark_data
	);

	if (orig_path_ref) {
		path_t target_path;

		// using `FileSystemRepresentation` here to ensure that APFS unicode normalisation is handled safely
		if (CFStringGetFileSystemRepresentation(
			/* string	*/ orig_path_ref,
			/* buffer	*/ target_path,
			/* maxBufLen*/ sizeof(target_path)
		)) {
			printf("target: %s", target_path);
			if (!FILE_EXISTS(target_path)) printf(" (broken)"); // verify if the file is still actually there

			printf("\n");
		}

		CFRelease(orig_path_ref);
	}

	// clean up the rest of the allocated CoreFoundation memory
	CFRelease(bookmark_data);
	CFRelease(alias_url);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
