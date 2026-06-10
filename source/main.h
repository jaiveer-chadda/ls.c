/// @file main.h

/// The maximum length a path can be on Darwin (MacOS/some BSD) machines.
#define MAXPATHLEN __DARWIN_MAXPATHLEN
/// The length of the human-readable permissions string (e.g. `drwxr-xr-x`).
#define PERMS_LEN 16 // 12

/// A mask to keep just the type information from the Unix octal permissions - (0o170000).
#define TYPE_MASK S_IFMT
/// A mask to keep just the permission information from the Unix octal permissions - (0o007777).
#define PERM_MASK 0007777

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )
