/// @file features/mode/mode.h

#define TYPE_MASK S_IFMT	/// A mask to keep just the type information from the Unix octal permissions - (0o170000).

void getMode(FileInfo *file, const mode_t oct_mode);

char getTypeSuffix(const mode_t mode);
