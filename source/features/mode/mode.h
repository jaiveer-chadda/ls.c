/// @file features/mode/mode.h

#define TYPE_MASK S_IFMT	/// A mask to keep just the type information from the Unix octal permissions - (0o170000).
#define EXEC_MASK 0000111	/// A mask to tell whether a file is an executable or not.

void getMode(modestr mode_str, const mode_t oct_mode);
void checkXattr(bool *has_xattr, const path_t path);

char getTypeSuffix(const mode_t mode);
