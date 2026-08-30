/// @file features/links/apple-alias.c

#include <stdio.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

#include "apple-alias.h"
#include "utils/malloc.h"

#include "debugging.h"

#define FILE_EXISTS(path) (access((path), F_OK) == 0)

#define DEFAULT_ALLOCATOR	NULL /** Also equivalent to `kCFAllocatorDefault`. */
#define IGNORE_ERRORS		NULL

#define FILE_IS_APPLE_ALIAS		true
#define FILE_IS_NOT_APPLE_ALIAS	false

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Checks whether an inputted path points to an Apple alias file, and resolves the alias if it does.
 *
 * @param target_buffer[out]
 *		The string in which the path to the target of the alias file will be stored, if the function succeeds.
 * @param is_valid_alias[out]
 *		Set to `true` if `alias_path` is an Apple alias file, and points to a file which exists.
 *			Set to `false` in all other cases.
 * @param alias_path[in] The path pointing to the file to be checked.
 *
 * @return `true` if the file at `alias_path` is an Apple alias file, `false` otherwise.
 */
bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t alias_path) {
	*is_valid_alias = false;

	/* ——————————————————————————————————————————————————————————— */

	// convert `alias_path` to a CF URL object
	//	this just reads the raw path and converts it into a format that the CF library can understand
	const CFURLRef path_url = CFURLCreateFromFileSystemRepresentation(
		/* allocator	*/ DEFAULT_ALLOCATOR,
		/* buffer		*/ (UInt8 *)alias_path,
		/* bufLen		*/ (CFIndex)strlen(alias_path),
		/* isDirectory	*/ false
	);

	if (path_url == NULL) {
		// if the function above fails, something's gone wrong, because it doesn't actually read the file -
		//	it just converts the path into a URL - it doesn't even check if the path passed exists.
		debug(ERROR, "'%s': failed to convert path into URL object", alias_path);
		return FILE_IS_NOT_APPLE_ALIAS;
	}

	/* ——————————————————————————————————————————————————————————— */

	// read the alias file into a bookmark `CFData` object
	//	this function is the one which opens and reads the file provided
	//	- it's also what causes the program to hang when reading `SF_DATALESS` files
	const CFDataRef bookmark_data = CFURLCreateBookmarkDataFromFile(
		/* allocator */ DEFAULT_ALLOCATOR,
		/* fileURL	 */ path_url,
		/* errorRef	 */ IGNORE_ERRORS // we don't care about catching any errors, so don't store the errorRef
	);
	CFRelease(path_url);

	if (bookmark_data == NULL) {
		// if this function failed, it's most likely because the file isn't actually an apple alias
		//	it's at this point that we're fully certain that `is_apple_alias` is false
		return FILE_IS_NOT_APPLE_ALIAS;
	}

	/* ——————————————————————————————————————————————————————————— */

	// extract the metadata stored in the bookmark, and convert it to a CF's string type
	const CFStringRef alias_string = CFURLCreateResourcePropertyForKeyFromBookmarkData(
		/* allocator */ DEFAULT_ALLOCATOR,
		/* key		 */ kCFURLPathKey, // tell the function that the bookmark contains a file system path
		/* bookmark	 */ bookmark_data
	);
	CFRelease(bookmark_data);

	if (alias_string == NULL) {
		// if we couldn't convert the bookmark to a string, there's no point trying to convert it into a C-string
		debug(ERROR, "'%s': failed to convert bookmark into CFString", alias_path);
		// however, we do still know that the file is an apple alias, so return true
		//	`is_valid_alias` will remain false, though, since we can't read the target path to check
		return FILE_IS_APPLE_ALIAS;
	}

	/* ——————————————————————————————————————————————————————————— */

	// convert the CF string into a C-string, and store it in `target_buffer`
	const bool conversion_success = (bool)CFStringGetFileSystemRepresentation(
		/* string	 */ alias_string,
		/* buffer	 */ target_buffer,
		/* maxBufLen */ (CFIndex)sizeof(path_t)
	);

	// if that's successful, then everything worked correctly
	if (conversion_success) {
		// finally, check whether the target file actually exists
		*is_valid_alias = FILE_EXISTS(target_buffer);
		// whether it does or it doesn't, clean up and return success
		goto return_1;
	}

	/* ——————————————————————————————————————————————————————————— */

	// one reason `CFStringGetFileSystemRepresentation` can fail, is because the provided buffer is
	//	too small to hold the string that's supposed to be assigned to it
	// ∴ find out how long the target length is, to see if that's the reason for failure
	const CFIndex target_path_len = CFStringGetMaximumSizeOfFileSystemRepresentation(alias_string);

	// check if the target path was too long to fit in the buffer
	if (target_path_len <= (CFIndex)sizeof(path_t))
		goto return_1; // if that wasn't the issue, then just clean up and return

	// allocate enough memory for the path
	char *temp_t_path = emalloc((size_t)(target_path_len + 1)); // +1 for the nullbyte

	// try assigning the path again, now with the larger buffer
	if (!CFStringGetFileSystemRepresentation(alias_string, temp_t_path, target_path_len))
		goto return_2;

	// if it succeeded, firstly check whether the file it points to is a valid file
	*is_valid_alias = FILE_EXISTS(temp_t_path);

	// then convert the C-string into a CF string
	const CFStringRef cf_t_path = CFStringCreateWithCString(
		/* alloc	*/ DEFAULT_ALLOCATOR,
		/* cStr		*/ temp_t_path,
		/* encoding	*/ (CFStringEncoding)kCFStringEncodingUTF8
	);

	if (cf_t_path == NULL)
		goto return_3;

	// now that we know whether the file exists or not, 
	//	truncate the path string so it'll fit in into `path_t`
	const CFStringRef trunc_t_path = CFStringCreateWithSubstring(
		/* alloc	*/ DEFAULT_ALLOCATOR,
		/* str		*/ cf_t_path,
		/* range	*/ (CFRange){ .location = 0, .length = (CFIndex)sizeof(path_t) }
	);

	// make sure that nothing went wrong with the truncation
	if (trunc_t_path == NULL)
		goto return_4;

	// finally, if everything worked out, re-assign the truncated path to the target buffer
	(void)CFStringGetFileSystemRepresentation(
		/* string	 */ trunc_t_path,
		/* buffer	 */ target_buffer,
		/* maxBufLen */ (CFIndex)sizeof(path_t)
	);
	
	/* ——————————————————————————————————————————————————————————— */

	return_4:
		CFRelease(trunc_t_path);
	return_3:
		CFRelease(cf_t_path);
	return_2:
		free(temp_t_path);
	return_1:
		CFRelease(alias_string);
		return FILE_IS_APPLE_ALIAS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
