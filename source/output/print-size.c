/// @file graphics/print-size.c

#include <stdio.h>
#include <string.h>

#include "../graphics/graphics.h"
#include "../options/options.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define PRINT_SIZE_W_COLOUR(un) \
	do { \
		printf( \
			"%s%.*s%s%c" RESET FIELD_PAD, \
			size_colour_esc[SC_B##un], \
			(int)strlen(size_str) - 1, size_str, \
			size_colour_esc[SC_U##un], unit \
		); \
	} while(0)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void printSize(const sizestr size_str, const char unit) {
	if (!do_size_str) return;

	const int len = (int)strlen(size_str);
	printf("%*c", (int)(field_lengths.size_str - len) + 1, ' ');
	int i = 0;
	
	switch (unit) {
		case '-': printf(PUNCT "%s" RESET FIELD_PAD, size_str); break;
		case ',':
			while (i < __INT_MAX__) {
				if (size_str[i] == ',') break; // break from the while loop
				putchar(size_str[i++]);
			}

			printf(PUNCT "," MIN_COL "%s" RESET FIELD_PAD, size_str + i+1);
			break;

		case 'b':
			if (DO_BYTES) PRINT_SIZE_W_COLOUR(b);
			else printf(" %s%.*s" RESET FIELD_PAD, size_colour_esc[SC_Bb], (int)strlen(size_str) - 1, size_str);
			break;

		case 'k': PRINT_SIZE_W_COLOUR(k); break;
		case 'm': PRINT_SIZE_W_COLOUR(m); break;
		case 'g': PRINT_SIZE_W_COLOUR(g); break;
		default	: PRINT_SIZE_W_COLOUR(t); break;
	}
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
