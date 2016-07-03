#include "cab202_graphics.h"

void draw_border ( void ) {
	// INSERT CODE HERE
	int w = screen_width();
	int h = screen_height();

	draw_line( 4, 1, 4,  h - 4, '$' ); //left side
	draw_line( 4, h - 4, w - 4, h - 4, '$' ); //Bottom
	draw_line(4, 1, w - 3, 1, '$'); //top
	draw_line(w - 3, 1, w - 3, h - 4, '$');





	show_screen();
}

int main( void ) {
	setup_screen();
	draw_border( );
	wait_char();
	cleanup_screen();
	return 0;
}
