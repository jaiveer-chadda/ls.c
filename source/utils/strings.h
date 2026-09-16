/// @file utils/strings.h

#ifndef STRING_INITIALISED
#define STRING_INITIALISED

#include <stdio.h>
#include "model/types.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

bool strends(const char *const inp, const char *const end);
void fputspaces(const size_t n, FILE *const file);
const char *getspaces(const size_t n);

#define putspaces(n) fputspaces((n), stdout)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void arg1__toLower(char *str);
void arg2__toLower(char *str_out, const char *str_in);

#define toLower__DISPATCH(_1, _2, NAME, ...) NAME
#define toLower(...) toLower__DISPATCH(__VA_ARGS__, arg2__toLower, arg1__toLower, DUMMY)(__VA_ARGS__)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STRING_INITIALISED */
