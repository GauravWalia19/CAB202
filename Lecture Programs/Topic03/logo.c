/*
 *	logo.c: A rudimentary zombie turtle graphics program.
 *			Refer: http://el.media.mit.edu/logo-foundation/what_is_logo/history.html
 *
 *	Copyright 2015 Queensland University of Technology.
 *
 *	Author: Lawrence Buckingham.
 *
 *	Revision History:
 *	18-Jul-2015 -- Created.
 */

#include <stdlib.h>
#include <unistd.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"

int main( void ) {
	setup_screen();

	int x = screen_width() / 2;
	int y = screen_height() / 2;
	int max_x = screen_width() - 1;
	int max_y = screen_height() - 1;

	draw_char( x, y, 'Z' );
	draw_string( 0, max_y, "Menu: 2 = Down; 4 = Left; 6 = Right; 8 = Up; q = Quit." );

	int key = get_char();

	while ( key != 'q' ) {
		if ( key == '4' ) {
			x = x - 1;
		}
		else if ( key == '6' ) {
			x = x + 1;
		}
		else if ( key == '8' ) {
			y = y - 1;
		}
		else if ( key == '2' ) {
			y = y + 1;
		}

		draw_char( x, y, 'Z' );

		show_screen();
		timer_pause( 20 );
		key = get_char();
	}

	save_screen();

	draw_line( 0, max_y, max_x, max_y, ' ' );
	draw_string( 0, screen_height() - 1, "Press any key to exit..." );
	wait_char();

	cleanup_screen();
	return 0;
}
