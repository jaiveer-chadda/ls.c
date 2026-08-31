/// @file features/size/size.h

#ifndef SIZE_INITIALISED
#define SIZE_INITIALISED

#include "model/types.h"

char *parseSize(char *const size_unit, const off_t size, const dev_t rdev);

#endif /* !SIZE_INITIALISED */
