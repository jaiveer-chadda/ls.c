/// @file tests/graphics/colour-object.c

#include <stdio.h>
#include "graphics/colour-object.h"

#define COLPRINT(...) colprint((Colour){ __VA_ARGS__ });

#define test_x ((Colour){ .style = G_ALL			, .fg = 999, .bg = G_BLU})
#define test_y ((Colour){ .fg = -10})
#define test_z ((Colour){ .fg = 999})
//
#define test_a ((Colour){ .bg = -498})
#define test_b ((Colour){ .bg = 3728})
#define test_c ((Colour){ .style = G_ALL + 1 })
//
#define test_1 ((Colour){ .style = G_BOLD | G_UNDER	, .fg = 125, .bg = G_BLU})
#define test_2 ((Colour){ .style = G_DIM  | G_UNDER	, .fg =  20, .bg = G_RED})
#define test_3 ((Colour){ .style = G_NONE			, .fg = 218, .bg = G_BLK})
#define test_4 ((Colour){ .style = G_NONE			, .fg =  20, .bg = G_BLK})
//
#define test_5 ((Colour){ .style = G_BOLD | G_ITALIC })
#define test_6 ((Colour){ .style = G_BOLD | G_UNDER })

int main(const int argc, const char* argv[]) {
	#ifdef DEBUG_MODE
		puts("———————————————————————— DEBUG ————————————————————————");
	#else
		putchar('\n');
	#endif

	// colprint(test_1);
	// colprint(test_2);
	// colprint(test_3);
	// colprint(test_2);
	// colprint(test_4);
	// colprint(RESET_ALL);
	// colprint(test_x);
	// colprint(test_5);
	// colprint(test_6);
	// colprint(test_z);
	// colprint(test_y);
	// colprint(test_y);
	// colprint(test_a);
	// colprint(test_b);
	// colprint(RESET_ALL);
	// colprint(test_c);

	#define black	G_BLK
	#define red		G_RED
	#define green	G_GRN
	#define yellow	G_YEL
	#define blue	G_BLU
	#define magenta	G_MAG
	#define cyan	G_CYN
	#define white	G_WHT
	#define lblack	G_BBLK
	#define lred	G_BRED
	#define lgreen	G_BGRN
	#define lyellow G_BYEL
	#define lblue	G_BBLU
	#define lmagent G_BMAG
	#define lcyan	G_BCYN
	#define lwhite	G_BWHT
	//
	#define none	G_NONE
	#define reset	G_RESET
	#define bold	G_BOLD
	#define dim		G_DIM
	#define italic	G_ITALIC
	#define under	G_UNDER
	#define blink	G_BLINK
	#define invert	G_INVERT
	#define invis	G_INVIS
	#define strike	G_STRIKE
	#define dunder	G_DUNDER
	#define all		G_ALL

	COLPRINT(bold, red, lblue)
	COLPRINT(bold, red)

	// COLPRINT(reset)
	

	return 0;
}
