/*
*	File:	blockhead.c
*	Author: Lawrence Buckingham, Queensland University of Technology.
*	Date:	27 April 2015.
*
*	Implementation of the blockhead walking sequence.
*/

#include <string.h>
#include <stdio.h>

#include "cab202_graphics.h"
#include "cab202_sprites.h"
#include "cab202_timers.h"

void do_the_walk( void );
void update_blockhead( sprite_id sprite );

void walk_the_walk( void ) {
	clear_screen();
	draw_string( 0, screen_height() - 1, "Click to walk..." );
	show_screen();
	wait_char();

	do_the_walk();

	clear_screen();
	draw_string( 0, 0, "Walk over." );
	draw_string( 0, 2, "Click to exit..." );
	show_screen();

	wait_char();
}

void do_the_walk() {
	char bitmap0[] = 
		"    11111    "
		"    1   1    "
		"    1   1    "
		"    11111    "
		"      1      "
		"    11111    "
		"   1  1  1   "
		"  1   1   1  "
		" 1    1    1 "
		"1     1     1"
		"      1      "
		"     1 1     "
		"    1   1    "
		"    1   1    "
		"    1   1    "
		"   1     1   "
		"   1     1   "
		"  1       1  "
		"  1       1  "
		"111       111"
	;
	char bitmap3[] =
		"    11111    "
		"    1   1    "
		"    1   1    "
		"    11111    "
		"      1      "
		"     111     "
		"    1 1 1    "
		"   1  1 1    "
		"   1  1  1   "
		"   1  1   1  "
		"      1      "
		"      11     "
		"      1 11   "
		"      1   1  "
		"      1 11   "
		"      11     "
		"    111      "
		"   1  1      "
		"   1  1      "
		"      111    ";
	char bitmap4[] = 
		"     11111   "
		"     1   1   "
		"     1   1   "
		"     11111   "
		"       1     "
		"      111    "
		"    11 1 1   "
		"  11   1  1  "
		"   1  1    11"
		"     1       "
		"     1       "
		"     111     "
		"     1  11   "
		"      1   11 "
		"       1    1"
		"       1   1 "
		"       1  1  "
		"      1   111"
		"     1       "
		"    111      "
	;
	char bitmap1[] = 
		"    11111    "
		"    1   1    "
		"    1   1    "
		"    11111    "
		"      1      "
		"     111     "
		"    1 1 1    "
		"   1  1 1    "
		"   1  1  1   "
		"   1  1   1  "
		"      1      "
		"     111     "
		"     1 1     "
		"     1  1    "
		"    1    1   "
		"    1     1  "
		"   1      1  "
		"   1      1  "
		"  1       1  "
		"  111     111"
	;
	char bitmap2[] = 
		"      11111  "
		"      1   1  "
		"      1   1  "
		"      11111  "
		"        1    "
		"       111   "
		"     11 1 1  "
		"   11   1  1 "
		"    1   1  11"
		"       1     "
		"       1     "
		"      111    "
		"      1  1   "
		"      1   1  "
		"      1    1 "
		"      1     1"
		"    11     1 "
		"  11       1 "
		"  1       1  "
		"          111"
	;

#define BITMAP_COUNT 4

	char *bitmaps[BITMAP_COUNT] = { bitmap1, bitmap2, bitmap3, bitmap4 };

	const int width = 13;
	const int height = strlen( bitmap0 ) / width;

	// Place blockhead in the center of the screen.
	sprite_id blockhead= sprite_create( 
		(screen_width() - width) / 2, 
		(screen_height() - height) / 2, width, height, bitmap0 );

	// Blockhead walks to the right.
	sprite_turn_to( blockhead, 1, 0 );

	clear_screen();
	sprite_draw( blockhead );
	draw_string( 0, screen_height() - 1, "Press 'q' to quit..." );
	show_screen();

	int current_image = 0;
	int walk_counter = 0;
	int key = 0;
	
	while ( key != 'q' ) {
		walk_counter++;

		if ( walk_counter % 4 == 0 ) {
			current_image = (current_image + 1 ) % BITMAP_COUNT;
			sprite_set_image( blockhead, bitmaps[current_image] );
		}

		update_blockhead( blockhead );
		
		clear_screen();

		// fprintf( stderr, "(x, y) = (%g, %g)\n", blockhead->x, blockhead->y );

		sprite_draw( blockhead );
		draw_string( 0, screen_height() - 1, "Press 'q' to quit..." );
		show_screen();

		timer_pause( 30 );
		key = get_char();
	}
}

void update_blockhead( sprite_id shape ) {
	sprite_step( shape );

	if ( shape->x >= screen_width() ) {
		sprite_move_to( shape, -sprite_width(shape), sprite_y(shape) );
	}

	if ( shape->y >= screen_height() ) {
		sprite_move_to( shape, sprite_x( shape ), -sprite_height( shape ) );
	}
}
