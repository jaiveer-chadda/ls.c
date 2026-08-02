/// @file utils/string.c

#include <string.h>
#include "string.h"

/**
 * @brief Find out whether a given string ends in another substring.
 *
 * With thanks to portfoliocourses (https://github.com/portfoliocourses)
 * https://github.com/portfoliocourses/c-example-code/blob/main/endswith.c
 *
 * @return true if `inp` ends with the substring `end`, and false otherwise.
 */
bool strends(const char *inp, const char *end) {
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
