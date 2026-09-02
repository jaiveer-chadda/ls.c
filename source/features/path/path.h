/// @file features/path/path.h

#ifndef PATH_INITIALISED
#define PATH_INITIALISED

#include "model/types.h"

int getDirPath(path_t out_path, const path_t path);
void abbrPath(path_t out_path, const path_t abs_path);

#endif /* !PATH_INITIALISED */
