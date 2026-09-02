/// @file features/mode/mode.h

#ifndef MODE_INITIALISED
#define MODE_INITIALISED

#include "model/types.h"

#define TYPE_MASK S_IFMT	/// A mask to keep just the type information from the Unix octal mode - (0o170000).
#define PERM_MASK 0000777	/// A mask to keep just the permission  info from the Unix octal mode - (0o000777).
#define EXEC_MASK 0000111	/// A mask to tell whether a file is an executable or not.

#ifndef NULL
#	define NULL ((void *)0)
#endif

void getMode(modestr mode_str, const mode_t oct_mode);
bool checkACL(const path_t path);
bool checkXattr(const path_t path);

char getTypeSuffix(const mode_t mode);

#endif /* !MODE_INITIALISED */
