
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "player.h"
#include "cab202_sprites.h"
#include "cab202_graphics.h"
#include "zombie.h"

// Sprites used to display player and banner.
sprite_id player = NULL, banner = NULL;

// Keep track of whether the hero is dead or alive.
bool player_is_dead = false;

// 1 x 1 bitmap used to display living hero.
char * normal_image = "H";

// 1 x 1 bitmap used to display dead hero.
char * dead_image = "@";

// ? x 3 bitmap used to display banner.
char * banner_image =
	"+---------------------------------------------------------+"
	"|       You are zombie food! Press 'r' to try again.      |"
	"+---------------------------------------------------------+";

/*
 *	Initialises the player-related aspects of the game,
 *	creating the icon for the player and initialising other state related
 *	to the player.
 */
void player_setup() {
	player = sprite_create( 0, 0, 1, 1, normal_image );

	int banner_width = strlen( banner_image ) / 3;
	int banner_height = 3;

	banner = sprite_create( 0, 0, banner_width, banner_height, banner_image );

	player_reset();
}

/*
*	Restores the player to its original position and appearance.
*/
void player_reset() {
	int width = screen_width();
	int height = screen_height();

	// Position the player's avatar in the centre of the screen.
	sprite_move_to( player, width / 2, height / 2 );

	// Make the player look alive.
	player_is_dead = FALSE;
	sprite_show( player );
	sprite_set_image( player, normal_image );

	// Restore the banner.

	int banner_width = strlen( banner_image ) / 3;
	int banner_height = 3;
	sprite_move_to( banner, ( width - banner_width ) / 2, ( height - banner_height ) / 2 );
	sprite_hide( banner );
}

/*
*	Tests to see if any of the monsters are in the same screen
*	location as the player. If yes, a message is displayed and subsequent calls
*	to player_dead() will return TRUE until the game is restarted.
*/
void player_check_died() {
	sprite_id zombie = zombie_at( sprite_x(player), sprite_y(player) );

	if ( zombie == NULL ) {
		return;
	}

	player_is_dead = TRUE;
	sprite_set_image( player, dead_image );
	sprite_show(banner);
}

/*
*	Returns true if and only if the player is dead.
*/
bool player_dead() {
	return player_is_dead;
}

/**
 *	Draw the player.
 */
void player_draw( void ) {
	sprite_draw( player );
	sprite_draw( banner );
}


/**
*	Clean up the player.
*/
void player_cleanup( void ) {
	sprite_destroy( player );
	sprite_destroy( banner );
	player = NULL;
	banner = NULL;
}

// This comes last because I do not want the namespace to be contaminated 
// with curses definitions. curses is included for one reason only to gain access to the key 
// codes for the arrow keys.
#include "curses.h"

bool player_update( int key_code ) {

	// fprintf( stderr, "player_update\n" );

	bool player_moved = true;

	int width = screen_width();
	int height = screen_height();
	double x = sprite_x( player );
	double y = sprite_y( player );

	if ( key_code == KEY_UP && y > 0 ) {
		sprite_move( player, 0, -1 );
	}
	else if ( key_code == KEY_DOWN && y < height - 1 ) {
		sprite_move( player, 0, +1 );
	}
	else if ( key_code == KEY_LEFT &&  x > 0 ) {
		sprite_move( player, -1, 0 );
	}
	else if ( key_code == KEY_RIGHT && x < width - 1 ) {
		sprite_move( player, +1, 0 );
	}
	else {
		player_moved = false;
	}

	return player_moved;
}
