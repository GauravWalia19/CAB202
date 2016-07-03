#include <time.h>
#include "cab202_timers.h"
#include "cab202_sprites.c"


void really_move( sprite_id sprite ) {
	sprite_step( sprite );

	if ( sprite->x < 0 ) sprite->dx = fabs( sprite->dx );
	if ( sprite->x >= screen_width() - sprite->width ) sprite->dx = -fabs( sprite->dx );

	if ( sprite->y < 0 ) sprite->dy = fabs( sprite->dy );
	if ( sprite->y >= screen_height() - sprite->height ) sprite->dy = -fabs( sprite->dy );
}

/// Returns true if and only if the two sprites are adjacent or overlapping.

bool isAdjacent( sprite_id s1, sprite_id s2 ) {

	if ( s1->x > s2->x ) {
		sprite_id t = s1; s1 = s2; s2 = t;
	}

	int x1 = round( s1->x );
	int x2 = round( s2->x );
	int y1 = round( s1->y );
	int y2 = round( s2->y );
	int w1 = s1->width;
	int h1 = s1->height;
	int h2 = s2->height;

	if ( x2 <= x1 + w1 // Horizontal overlap
		&& y2 <= y1 + h1 // vertical overlap
		&& y1 <= y2 + h2 // vertical overlap
	) {
#define DB false

#if DB
		fprintf( stderr, "s1->x = %f", s1->x );
		fprintf( stderr, "s1->y = %f", s1->y );
		fprintf( stderr, "s2->x = %f", s2->x );
		fprintf( stderr, "s2->y = %f", s2->y );
		fprintf( stderr, "s2->y = %f", s2->y );
		fprintf( stderr, "s2->x <= s1->x + s1->width  = %d", s2->x <= s1->x + s1->width );
		fprintf( stderr, "s2->y <= s1->y + s1->height = %d", s2->y <= s1->y + s1->height );
		fprintf( stderr, "s1->y <= s2->y + s2->height = %d", s1->y <= s2->y + s2->height );
		fprintf( stderr, "\n" );
#endif
		return true;
	}

	return false;
}

int main( void ) {
	srand( time( NULL ) );
	setup_screen();

	sprite_id sprite_1;
	sprite_id sprite_2;
	char * image = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

	sprite_1 = sprite_create( rand() % screen_width(), rand() % screen_height(), 10, 10, image );
	sprite_2 = sprite_create( rand() % screen_width(), rand() % screen_height(), 10, 10, image );

	sprite_1->dx = rand();
	sprite_1->dy = rand();
	double mag = sqrt( 1e-100 + sprite_1->dx * sprite_1->dx + sprite_1->dy * sprite_1->dy );
	sprite_1->dx /= 2 * mag;
	sprite_1->dy /= 2 * mag;

	sprite_2->dx = rand();
	sprite_2->dy = rand();
	mag = sqrt( 1e-100 + sprite_2->dx * sprite_2->dx + sprite_2->dy * sprite_2->dy );
	sprite_2->dx /= 2 * mag;
	sprite_2->dy /= 2 * mag;

	while ( 1 ) {
		clear_screen();
		sprite_draw( sprite_1 );
		sprite_draw( sprite_2 );

		show_screen();
		int key = get_char();

		if ( key > 0 ) break;

		really_move( sprite_1 );
		really_move( sprite_2 );

		if ( isAdjacent( sprite_1, sprite_2 ) ) {
			sprite_1->dx = sprite_1->dy = 0;
			sprite_2->dx = sprite_2->dy = 0;
		}

		timer_pause( 10 );
	}
	cleanup_screen();
}