#include "cab202_graphics.h"

void draw_lines( void ) {
	draw_line( 7, 21, 35, 21, '@');   //bottom
	draw_line( 58, 14, 50, 10, '@'); //Top
	draw_line( 50, 10, 7, 21, '@'); //Left side
	draw_line( 35, 21, 58, 14, '@'); //right side 


	show_screen( );
}

int main( void ) {
	setup_screen( );

	draw_lines( );

	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char( );
	cleanup_screen( );
	return 0;
}
