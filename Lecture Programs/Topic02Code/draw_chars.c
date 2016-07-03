/*
 *	draw_chars.c: Displays a table of character codes and their asssociated glyphs.
 *
 *	Copyright 2016 Queensland University of Technology.
 *
 *	Author: Lawrence Buckingham.
 *
 *	Revision History:
 *	08-Mar-2016 -- Created.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "cab202_graphics.h"
#include "cab202_timers.h"

// ----------------------------------------------------------------
// Global variables containing "long-term" state of program
// ----------------------------------------------------------------

// The largest visible horizontal location.
int max_x;				

// The vertical location of the turtle, relative to the terminal window.
int max_y;

// Game-in-progress status: true if and only if the game is finished.
bool game_over;

// ----------------------------------------------------------------
//	Configuration
// ----------------------------------------------------------------
#define QUIT 'q'

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
 *	screen must be updated as the result of a keypress.
 */
bool process_key() {
	int key = get_char();

	if ( key == QUIT ) {
		game_over = true;
	}

	return false;
}

/*
 *	Process timer events, returning true if and only if the 
 *	screen must be updated as the result of time passing.
 */
bool process_timer() {
	return false;
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
	draw_string( 0, max_y, "Menu: q = Quit." );
}

/*
 *	Redraws the screen
 */
void draw_all() {
	clear_screen();

	int x = 0;
	int y = 0;
	int current_char = ' ';

	while ( current_char < 256 && y <= max_y ) {
		while ( current_char < 256 && x <= max_x - 6 ) {
			draw_formatted( x, y, "%3d:", current_char );
			draw_char( x + 5, y, current_char );
			x += 10;
			current_char++;
		}
		y++;
		x = 0;
	}

	draw_menu();
	show_screen();
}
