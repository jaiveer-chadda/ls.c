/// @file utils/strings.c

#include <stddef.h>
#include <string.h>

#include "strings.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IS_UPPER(chr) ('A' <= (chr) && (chr) <= 'Z')

void arg1__toLower(char *str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (IS_UPPER(str[i])) str[i] += ('a' - 'A');
	}
}

void arg2__toLower(char *str_out, const char *str_in) {
	int i;
	for (i = 0; str_in[i] != '\0'; i++) {
		str_out[i] = str_in[i] + (IS_UPPER(str_in[i]) ? ('a' - 'A') : 0);
	}
	str_out[i] = '\0';
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Find out whether a given string ends in another substring.
 *
 * With thanks to [portfoliocourses](https://github.com/portfoliocourses)
 * ([source](https://github.com/portfoliocourses/c-example-code/blob/main/endswith.c))
 *
 * @return true if `inp` ends with the substring `end`, and false otherwise.
 */
bool strends(const char *const inp, const char *const end) {
	// get the lengths of both strings
	const int inp_len = strlen(inp), end_len = strlen(end);

	// if `end` is longer than `inp` itself, return false as it's impossible for `inp` to end with `end`
	if (end_len > inp_len) return false;

	// check the chars at the end of `inp` to see if any of them do no match the chars in `end`,
	//  if any don't, `inp` doesn't end with `end`, and we can return false
	for (int i = 1; i < end_len + 1; i++) {
		if (inp[inp_len - i] != end[end_len - i]) return false;
	}

	return true; // if we didn't find any non-matching chars, `inp` must end with `end`
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const char *getspaces(const size_t n) {
	static char SPACES[256] = {0};
	static const size_t SP_COUNT = sizeof(SPACES) - 1;

	if (SPACES[0] == '\0') memset(SPACES, ' ', SP_COUNT);

	if (n <= SP_COUNT) return SPACES + SP_COUNT - n;
	return NULL;
}

void fputspaces(const size_t n, FILE *const file) {
	flockfile(file);
	for (size_t i = 0; i < n; i++) putc_unlocked(' ', file);
	funlockfile(file);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
