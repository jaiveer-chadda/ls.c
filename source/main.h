/// @file main.h

/// The maximum length a path can be on a Darwin (MacOS/BSD) machine.
#define MAXPATHLEN __DARWIN_MAXPATHLEN
/// The length of the human-readable permissions string (e.g. `drwxr-xr-x`).
#define PERMS_LEN 16 // 12

/// A mask to keep just the type information from the Unix octal permissions.
#define TYPE_MASK S_IFMT
/// A mask to keep just the permission information from the Unix octal permissions.
#define PERM_MASK 0007777

/// Check if a specified octal type matches a target mask.
#define IS_TYPE(oct_type, target_type) \
	((oct_type & target_type) != 00)

/// Get the character representing the filetype specified by an octal type integer.
#define GET_TYPE_CHAR(type, t_char) \
	if		IS_TYPE(type, S_IFIFO)	t_char = '|'; /* named pipe		('|' or 'p')	*/ \
	else if	IS_TYPE(type, S_IFCHR)	t_char = 'c'; /* char device					*/ \
	else if	IS_TYPE(type, S_IFDIR)	t_char = 'd'; /* directory						*/ \
	else if	IS_TYPE(type, S_IFBLK)	t_char = 'b'; /* block device					*/ \
	else if	IS_TYPE(type, S_IFREG)	t_char = '.'; /* regular 		('.' or '-')	*/ \
	else if	IS_TYPE(type, S_IFLNK)	t_char = 'l'; /* symbolic link					*/ \
	else if	IS_TYPE(type, S_IFSOCK)	t_char = 's'; /* socket							*/ \
	else if	IS_TYPE(type, S_IFWHT)	t_char = 'w'; /* whiteout						*/ \
	else							t_char = ' '  /* unknown						*/ 

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )
