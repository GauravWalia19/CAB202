#include "cab202_graphics.h"

void running_zombie( void ) {
	// MODIFY THIS PART TO PLACE ZOMBIE
	int x = screen_width( ) / 2;
	int y = (screen_height( ) / 100) * 60;

	// INSERT VARIABLE TO COUNT ELAPSED TURNS

	int count = 0;
	int score = 0;

	// MODIFY THE FOLLOWING TO DISPLAY SCORE
	draw_string( 20, 0, "Score:");
	draw_string( 0, screen_height( ) - 1, "Menu: 8 = N; 2 = S; 6 = E; 4 = W; 9 = NE; 3 = SE; 7 = NW; 1 = SW; q = Quit." );
	draw_char( x, y, 'Z' );

	show_screen( );

	// CHANGE NEXT LINE TO WAIT FOR KEY PRESS (done)
	int key = wait_char( );

	while ( key != 'q' && key >= 0 ) {
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

		// INSERT ADDITIONAL LOGIC TO MOVE DIAGONALLY AND COUNT ELAPSED TURNS


			else if ( key == '1') {
				y = y + 1;
				x = x - 1;
			}
			else if ( key == '3' ) {
				y = y + 1;
				x = x + 1;
			}
			else if ( key == '7' ) {
				y = y - 1;
				x = x - 1;
			}
			else if ( key == '9') {
				y = y - 1;
				x = x + 1;
			}
			count = count + 1;
			if (count == 7) {
				score++;
				count = 0;
			}

		// MODIFY TO CLEAR THE SCREEN, THEN REDRAW DISPLAY
		clear_screen();
		draw_char( x, y, 'Z' );
		draw_char(x, y, score);

		// DON'T MESS WITH THE NEXT LINE
		show_screen( );

		// CHANGE NEXT LINE TO WAIT FOR KEY PRESS (done)
		key = wait_char( );
	}
}

int main( void ) {
	setup_screen( );
	running_zombie( );
	cleanup_screen( );
	return 0;
}
