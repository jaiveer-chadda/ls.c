/// @file mode.h

/// The length of the human-readable mode string +1 (e.g. `drwxr-xr-x`).
#define MAX_MODE_LEN 12

void getMode(const struct stat info, char mode_str[MAX_MODE_LEN]);

char getTypeSuffix(const mode_t mode);
