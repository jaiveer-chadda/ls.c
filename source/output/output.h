/// @file output/output.h

#ifndef OUTPUT_H
#define OUTPUT_H

#include "model/types.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NO_LINES ((const bool[RECURSION_LIMIT]){0})

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printHeaders(void);

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines);
void print_tree(lines_t new_lines, const lines_t lines, const uint8_t depth, const bool is_last);

bool  dirEmpty(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines);
bool fileError(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !OUTPUT_H */
