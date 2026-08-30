/// @file utils/strings.h

#ifndef STRING_INITIALISED
#define STRING_INITIALISED

#include <stdbool.h>

size_t cstrlen(const char *cstr);
bool strends(const char *inp, const char *end);

void arg1__toLower(char *str);
void arg2__toLower(char *str_out, const char *str_in);

#define DISPATCH(_1, _2, NAME, ...) NAME
#define toLower(...) DISPATCH(__VA_ARGS__, arg2__toLower, arg1__toLower, DUMMY)(__VA_ARGS__)

#endif /* !STRING_INITIALISED */
