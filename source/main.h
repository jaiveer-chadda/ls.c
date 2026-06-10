/// @file main.h

/// The maximum length a path can be on Darwin (MacOS/some BSD) machines.
#define MAX_PATH_LEN __DARWIN_MAXPATHLEN
/// The maximum length a filename can be on Darwin (MacOS/some BSD) machines.
#define MAX_NAME_LEN MAXNAMLEN

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )
