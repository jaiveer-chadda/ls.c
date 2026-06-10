/// @file main.h

/// The maximum length a path can be on Darwin (MacOS/some BSD) machines.
#define MAX_PATH_LEN __DARWIN_MAXPATHLEN
/// The length of the human-readable mode string +1 (e.g. `drwxr-xr-x`).
#define MAX_MODE_LEN 12

#define EXT_MASK 0007000	/// A mask to get the extended bits (4,2,1 = uid, gid, sticky) from octal permissions.
#define USR_MASK S_IRWXU	/// A mask to get the user octal permissions.
#define GRP_MASK S_IRWXG	/// A mask to get the group octal permissions.
#define OTH_MASK S_IRWXO	/// A mask to get the other octal permissions.

/// A mask to keep just the type information from the Unix octal permissions - (0o170000).
#define TYPE_MASK S_IFMT

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )

#define SET_EXT_BIT(str, chr) /* exec == lowercase, non-exec == uppercase */ \
	str[2] = str[2] == 'x' ? chr : chr - ('a' - 'A')

#define PARSE_PERM(location, ext_char, type) \
	get_perm_str(type##_oct, type##_str); \
	if (ext_oct & location) SET_EXT_BIT(type##_str, ext_char)

typedef char ModeStr_t[4];
