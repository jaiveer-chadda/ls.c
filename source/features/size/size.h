/// @file features/size/size.h

#ifndef SIZE_INITIALISED
#define SIZE_INITIALISED

#include "../../model/stat-model.h"

void parseSize(sizestr size_str, char *size_unit, off_t *size, const dev_t rdev);

#endif /* !SIZE_INITIALISED */
