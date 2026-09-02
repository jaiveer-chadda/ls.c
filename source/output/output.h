/// @file output/output.h

#ifndef OUTPUT_H
#define OUTPUT_H

#include "model/types.h"

#define NO_LINES ((const bool[RECURSION_LIMIT]){0})

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines);

#endif /* !OUTPUT_H */
