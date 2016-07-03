#include "game.h"

// Screen dimensions, used to detect resize events.
int previous_screen_width, previous_screen_height;

bool resize_detected( void );

void setup_game() {
	setup_screen();

	get_screen_size( previous_screen_width, previous_screen_height );

	player_setup();
	zombie_setup();
	show_screen();
}


void reset_game() {
	get_screen_size( previous_screen_width, previous_screen_height );

	player_reset();
	zombie_reset();
	show_screen();
}


void cleanup_game( void ) {
	cleanup_screen();
	player_cleanup();
	zombie_cleanup();
}


int play_turn() {

	// fprintf( stderr, "play_turn\n" );

	int result = TURN_OK;

	if ( resize_detected() ) {
		reset_game();
		return result;
	}

	/* If we have a key, process it immediately. */
	int key_code = get_char();

	if ( key_code == 'q' || key_code == 'Q' ) {
		return TURN_GAME_OVER;
	}
	else if ( key_code == 'r' || key_code == 'R' ) {
		reset_game();
		return TURN_OK;
	}

	if ( player_dead() ) {
		// Player was already dead, so don't process player or zombies.
		return TURN_OK;
	}

	//	These are the only events that can cause the display to change from 
	//	the previous iteration.
	if ( player_update( key_code ) ) {
		result = TURN_SCREEN_CHANGED;
	}
	else if ( zombie_update() ) {
		result = TURN_SCREEN_CHANGED;
	}
	
	// Always check after move by either player or zombie.
	player_check_died();

	return result;
}


bool resize_detected( void ) {
	int new_width = screen_width();
	int new_height = screen_height();
	
	bool resized = new_width != previous_screen_width
		|| new_height != previous_screen_height;

	previous_screen_width = new_width;
	previous_screen_height = new_height;

	return resized;
}


/**
 *	Renders a new frame in the game view.	
 */

void draw_game( void ) {
	clear_screen( );
	draw_zombies( );
	player_draw( );
	show_screen( );
}
