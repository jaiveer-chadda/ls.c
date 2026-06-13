/// @file mode.h

void getMode(const struct stat info, char mode_str[MAX_MODE_LEN]);

char getTypeSuffix(const mode_t mode);
