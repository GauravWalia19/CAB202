/*
 *	logo2.c: A rudimentary zombie turtle graphics program.
 *			Refer: http://el.media.mit.edu/logo-foundation/what_is_logo/history.html
 *
 *	Copyright 2015 Queensland University of Technology.
 *
 *	Author: Lawrence Buckingham.
 *
 *	Revision History:
 *	18-Jul-2015 -- Created.
 *	08-Mar-2016 -- Refactor into event-loop form.
 *	16-Mar-2016 -- Add a zombie.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"
#include "cab202_sprites.h"

// ----------------------------------------------------------------
// Global variables containing "long-term" state of program
// ----------------------------------------------------------------

// The horizontal location of the turtle relative to the terminal window
int x;

// The vertical location of the turtle, relative to the terminal window.
int y;

// The largest visible horizontal location.
int max_x;

// The vertical location of the turtle, relative to the terminal window.
int max_y;

// Game-in-progress status: true if and only if the game is finished.
bool game_over;

sprite_id zombie;

// Zombie Timer
timer_id zombie_timer;

// ----------------------------------------------------------------
//	Configuration
// ----------------------------------------------------------------
#define LEFT '4'
#define RIGHT '6'
#define UP '8'
#define DOWN '2'
#define TURTLE 'H'
#define QUIT 'q'
#define ZOMBIE 'Z'

// ----------------------------------------------------------------
// Forward declarations of functions
// ----------------------------------------------------------------

void setup();
void event_loop();
void cleanup();
void pause_for_exit();
bool process_screen();

bool process_key();
bool process_timer();
void draw_all();
void draw_menu();
void draw_turtle();
void reset_turtle();

void setup_zombie();
bool process_zombie();
void draw_zombie();

//

// ----------------------------------------------------------------
// main function
// ----------------------------------------------------------------

int main( void ) {
	setup();
	event_loop();
	cleanup();
	return 0;
}

/*
 *	Set up the game. Sets the terminal to curses mode and places the turtle.
 */

void setup() {
	setup_screen();
	max_x = screen_width() - 1;
	max_y = screen_height() - 1;
	game_over = false;
	reset_turtle();
	setup_zombie();
}

/*
 *	Restore the terminal to normal mode.
 */
void cleanup() {
	cleanup_screen();
}

/*
 *	Processes keyboard timer events to progress game.
 */
void event_loop() {
	draw_all();

	while ( !game_over ) {
		bool must_redraw = false;

		must_redraw = must_redraw || process_screen();
		must_redraw = must_redraw || process_key();
		must_redraw = must_redraw || process_timer();

		if ( must_redraw ) {
			draw_all();
		}

		timer_pause( 20 );
	}

	pause_for_exit();
}

/*
 *	Turn-based screen processing. Tests for resize events,
 *	returning true if and only if the size has changed.
 */
bool process_screen() {
	int new_max_x = screen_width() - 1;
	int new_max_y = screen_height() - 1;

	bool size_changed = new_max_x != max_x || new_max_y != max_y;

	if ( size_changed ) {
		max_x = new_max_x;
		max_y = new_max_y;
	}

	return size_changed;
}

/*
 *	Process keyboard events, returning true if and only if the
 *	turtle's position has changed.
 */
bool process_key() {
	int key = get_char();

	if ( key == QUIT ) {
		game_over = true;
		return false;
	}

	// Remember original position
	int x0 = x;
	int y0 = y;

	// Update position
	if ( key == LEFT ) {
		x--;
	}
	else if ( key == RIGHT ) {
		x++;
	}
	else if ( key == UP ) {
		y--;
	}
	else if ( key == DOWN ) {
		y++;
	}

	// Make sure still inside window
	while ( x < 0 ) x++;
	while ( y < 0 ) y++;
	while ( x > max_x ) x--;
	while ( y > max_y ) y--;

	return x0 != x || y0 != y;
	/*
		Equivalently:

		if ( x0 != x || y0 != y ) {
		return true;
		}
		else {
		return false;
		}
		*/
}

/*
 *	Process timer events, returning true if and only if the
 *	screen must be updated as the result of time passing.
 */
bool process_timer() {
	bool something_happened = process_zombie();
	return something_happened;
}

/*
 *	Returns the turtle to the centre of the terminal window.
 */
void reset_turtle() {
	x = max_x / 2;
	y = max_y / 2;
}

/*
 *	Redraws the screen
 */
void draw_all() {
	clear_screen();
	draw_turtle();
	draw_zombie();
	draw_menu();
	show_screen();
}

/*
 *	Displays a messsage and waits for a keypress.
 */
void pause_for_exit() {
	draw_line( 0, max_y, max_x, max_y, ' ' );
	draw_string( 0, screen_height() - 1, "Press any key to exit..." );
	wait_char();
}

/*
 *	Displays a messsage and waits for a keypress.
 */
void draw_menu() {
	draw_line( 0, max_y, max_x, max_y, ' ' );
	draw_string( 0, max_y, "Menu: 2 = Down; 4 = Left; 6 = Right; 8 = Up; q = Quit." );
}

/*
 *	Draws the turtle.
 */
void draw_turtle() {
	draw_char( x, y, TURTLE );
}

/*
 * Places the zombie in it's intial position and sets up the timer.
 */
void setup_zombie() {
	static char * bitmap =
		"***"
		"* *"
		"***";
	time_t now = time( NULL );
	srand( now );

		zombie = sprite_create( rand() % screen_width(), rand() % screen_height()
			, 3, 3, bitmap );

		zombie->dx = 0.5;
		zombie->dy = 0.0;

	zombie_timer = create_timer( 30 );
}

/*
 * Tries to move the zombie; returns true iff the zombie moved.
 */
bool process_zombie() {
	if ( timer_expired( zombie_timer ) ) {
		sprite_step( zombie );

		if ( zombie->x >= screen_width() ) {
			zombie->dx = -1 * fabs( zombie->dx );
		}
		else if ( zombie->x < 0 ) {
			zombie->dx = 1 * fabs( zombie->dx );
		}

		if ( zombie->y >= screen_height() ) {
			zombie->dy = -1 * fabs( zombie->dy );
		}
		else if ( zombie->y < 0 ) {
			zombie->dy = 1 * fabs( zombie->dy );
		}

		return true;
	}
	else {
		return false;
	}
}


/*
 *	Draws the zombie.
 */
void draw_zombie() {
	sprite_draw( zombie );
}
