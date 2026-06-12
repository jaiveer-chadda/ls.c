/// @file main.h

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )

#define PRINT_HEADER \
	printf("%-12s nlink %12s  uid\tgid\t%-10s  %-20s  name\n", "mode", "size", "flags", "mtime")

#define PRINT_FILE_INFO(file) \
	printf("%-12s %-5d %12lld  %d\t%d\t%-10s  %-20s  %s%c\n", \
		file.mode_str, file.nlink, file.size, file.uid, file.gid, file.flag_str, file.time_str, \
		file.name, file.suffix \
	)
