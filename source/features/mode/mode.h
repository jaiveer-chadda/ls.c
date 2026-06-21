/// @file features/mode/mode.h

#include "../../model/stat-model.h"

#define TYPE_MASK S_IFMT	/// A mask to keep just the type information from the Unix octal permissions - (0o170000).
#define EXEC_MASK 0000111	/// A mask to tell whether a file is an executable or not.

#ifndef NULL
#define NULL ((void *)0)
#endif

void getMode(modestr mode_str, const mode_t oct_mode);
void checkACL(bool *has_ext_perms, const path_t path);
void checkXattr(bool *has_xattr, const path_t path);

char getTypeSuffix(const mode_t mode);
