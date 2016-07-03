#include "cab202_graphics.h"

int main( void ) {

	setup_screen();

	draw_line(0,11.5,79,11.5, '-');

	draw_line(4, 11 , 4, 18, '~'); //left  increasing values pushes it down
	draw_line(75, 6, 75, 13, '~'); //right

	show_screen();

	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}
