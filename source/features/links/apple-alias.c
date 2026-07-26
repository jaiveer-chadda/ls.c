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
	CFURLRef alias_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ kCFAllocatorDefault,
		/* buffer		*/ (const UInt8 *)file_path,
		/* bufLen		*/ strlen(file_path),
		/* isDirectory	*/ false
	);

	if (!alias_url) return is_apple_alias;

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
		return is_apple_alias;
	}

	// extract the stored metadata
	CFStringRef orig_path_ref = (CFStringRef)CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ kCFAllocatorDefault,
		/* key		 */ kCFURLPathKey,
		/* bookmark	 */ bookmark_data
	);

	if (orig_path_ref) {
		is_apple_alias = true;

		path_t target_path;

		// using `FileSystemRepresentation` here to ensure that APFS unicode normalisation is handled safely
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

link_t getPrintableAppleAlias(const path_t target_path) {
	// this memory is freed once the link is printed (in `printSymlink()`)
	link_t target_str = malloc(sizeof(link_t));

	if (target_str == NULL) {
		perror(ERROR "malloc:target_str");
		exit(EXIT_FAILURE);
	}

	/* ————————————————————————————————————————————————————— */

	const char *HOME = getenv("HOME");
	const int home_len = strlen(HOME);
	const int path_len = strlen(target_path);

	int bytes_written;

	if (HOME != NULL
		&& home_len > 0
		&& home_len < path_len
		&& strncmp(HOME, target_path, home_len) == 0
	) {
		bytes_written = sprintf(target_str, "~%s", target_path + home_len);
	} else {
		bytes_written = sprintf(target_str, "%s", target_path);
	}

	target_str[bytes_written] = '\0';

	/* ————————————————————————————————————————————————————— */

	return target_str;
}


/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
