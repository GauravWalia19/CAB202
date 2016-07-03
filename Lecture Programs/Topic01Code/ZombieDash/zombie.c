#include <stdlib.h>
#include <math.h>

#include "zombie.h"
#include "cab202_sprites.h"
#include "cab202_timers.h"
#include "cab202_graphics.h"

#define ZOMBIE_COUNT (25)
#define ZOMBIE_UPDATE_TIME (100)
#define SLEEP_TIME (10)

sprite_id zombies[ZOMBIE_COUNT];
timer_id zombie_timer;

void zombie_reset() {
	int width = screen_width();
	int height = screen_height();

	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		sprite_id zombie = zombies[i];

		sprite_move_to( zombie, rand() % width, rand() % height );

		double direction = ( rand() % 360 ) * M_PI / 180;
		sprite_turn_to( zombie, cos( direction ), sin( direction ) );

		sprite_show( zombie );


		// fprintf( stderr, "( zombie->x, zombie->y ) = ( %g, %g )\n", zombie->x, zombie->y );
		// fprintf( stderr, "( zombie->dx, zombie->dy ) = ( %g, %g )\n", zombie->x, zombie->y );
		sprite_draw( zombie );
	}
}


void create_zombies() {
	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		zombies[i] = sprite_create( 0, 0, 1, 1, "Z" );
	}

	zombie_reset();
}


void zombie_setup() {
	create_zombies();
	zombie_timer = create_timer( ZOMBIE_UPDATE_TIME );
}

bool zombie_update() {

	// fprintf( stderr, "zombie_update\n" );

	if ( !timer_expired( zombie_timer ) ) {
		return FALSE;
	}

	// fprintf( stderr, "timer expired\n" );

	int width = screen_width();
	int height = screen_height();

	// fprintf( stderr, "( width, height ) = ( %d, %d )\n", width, height );

	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		sprite_id zombie = zombies[i];

		int new_x = (int) round( sprite_x( zombie ) + sprite_dx( zombie ) );
		int new_y = (int) round( sprite_y( zombie ) + sprite_dy( zombie ) );

		// fprintf( stderr, "( new_x, new_y ) = ( %d, %d )\n", new_x, new_y );
		double new_dx = sprite_dx( zombie );
		double new_dy = sprite_dy( zombie );

		if ( new_y < 0 || new_y >= height ) {
			new_dy = -new_dy;
		}

		if ( new_x < 0 || new_x >= width ) {
			new_dx = -new_dx;
		}

		sprite_turn_to( zombie, new_dx, new_dy );
		sprite_step( zombie );
	}

	return TRUE;
}

sprite_id zombie_at( double x, double y ) {
	x = (int) round( x );
	y = (int) round( y );

	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		sprite_id zombie = zombies[i];
		int zx = (int) round( sprite_x( zombie ) );
		int zy = (int) round( sprite_y( zombie ) );

		if ( zx == x && zy == y ) {
			return zombie;
		}
	}

	return NULL;
}


/**
*	Draw the zombies.
*/

void draw_zombies( void ) {
	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		sprite_draw( zombies[i] );
	}
}

/**
*	Clean up the zombies.
*/

void zombie_cleanup( void ) {
	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		free( zombies[i] );
	}
}
