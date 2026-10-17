/// @file parsing/parse-file.h

#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include "model/stat-model.h"

#define DO_RECURSE	 true
#define DONT_RECURSE false

void parseFile(FileStat *const pfile);

#endif /* !PARSE_FILE_H */
