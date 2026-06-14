/// @file main.h

/// Whether the specified `entry`'s filename is "." or "..".
#define DO_IGNORE_FILE(entry) \
	( strcmp(entry->d_name, "." ) == 0 || \
	  strcmp(entry->d_name, "..") == 0 )
