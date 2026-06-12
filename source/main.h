/// @file main.h

/// The maximum length a path can be on Darwin (MacOS/some BSD) machines.
#define MAX_PATH_LEN __DARWIN_MAXPATHLEN
/// The maximum length a filename can be on Darwin (MacOS/some BSD) machines.
#define MAX_NAME_LEN MAXNAMLEN

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )

#define PRINT_HEADER \
	printf("%-12s nlink\tsize\tuid\tgid\t%-10s  %-20s  name\n", "mode", "flags", "mtime")

#define PRINT_FILE_INFO(file) \
	printf("%-12s %d\t\t%lld\t%d\t%d\t%-10d  %-20s  %s%c\n", \
		file.mode_str, file.nlink, file.size, file.uid, file.gid, file.flags, file.time_str, \
		file.name, file.suffix \
	)
