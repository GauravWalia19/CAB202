#include "cab202_graphics.h"

void draw_balls( void ) {
	draw_char( 33, 15, 'O' );
	draw_char( 67, 0, 'O' );
	draw_char( 72, 5, 'O' );
	draw_char( 11, 13, 'O' );

	show_screen();
}

int main( void ) {
	setup_screen();

	draw_balls();

	draw_string( 0, screen_height() - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}
