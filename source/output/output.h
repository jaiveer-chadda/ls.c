/// @file output/output.h

#include "../model/stat-model.h"

void printHeader(void);
void printFields(const FileInfo *all_files, const int *count);

void printNLink(const nlink_t *nlink, const mode_t *mode, bool *hardln_hl);
void printSize(const sizestr size_str, const char unit);
void printModeStr(const modestr str);
