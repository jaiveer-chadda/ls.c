/// @file output/output.h

#ifndef OUTPUT_H
#define OUTPUT_H

#include "strings.h" // putspaces()
#include "form/formatting.h" // getTotalLen()
#include "model/stat-model.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define NO_LINES ((const bool[RECURSION_LIMIT]){0})

#define LAST_TREE_BRANCH	 true
#define NOT_LAST_TREE_BRANCH false

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define print_empty_tree(lines, depth, is_last) do {	\
	putspaces(getTotalLen());							\
	print_tree(NULL, (lines), (depth), (is_last));		\
} while (0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printHeaders(void);
void printEscdName(const char *const name, const Colour colour, const bool do_padding);

void printFile(const FileStat *const pFS, const uint8_t depth, const bool is_last, const lines_t lines);
void print_tree(lines_t new_lines, const lines_t lines, const uint8_t depth, const bool is_last);

bool  dirEmpty(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines);
bool fileError(const FileStat *const pFS, const uint8_t depth, const lines_t new_lines);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !OUTPUT_H */
