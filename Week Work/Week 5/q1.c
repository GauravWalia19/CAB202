/*	CAB202: Tutorial 4
*	Question 1 - Template
*
*	B.Talbot, August 2015
*	Queensland University of Technology
*/
#include <stdbool.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"

/*
* Defined constants - you should make use of these when implementing the draw function!!!
*/
#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1
#define DIRECTION_UP 2
#define DIRECTION_DOWN 3

#define CHAR_DIRECTION_LEFT '<'
#define CHAR_DIRECTION_RIGHT '>'
#define CHAR_DIRECTION_UP '^'
#define CHAR_DIRECTION_DOWN 'v'

#define NUM_BULLETS 3

/*
* Struct type declaration
*/
// TODO: Declare type 'bullet_t' as a struct with the appropriate member variables
typedef struct {
	int x;
	int y;
	int direction;
	bool is_mega;
} bullet_t;

/*
* Function declarations:
* 	- Complete 'draw_bullet()' so that it draws the bullet at the correct location,
*	with the correct characters
*/
void draw_bullet(bullet_t bullet);

/*
* Main:
* 	- Creates, and initialises, the 3 bullets for the required run
*	- Loops through 'shooting' the bullets until they go off screen
*/
int main() {

	// Initialise the graphics environment
	setup_screen();

	// Initialise the bullet array and store screen width and height for ease of use
	bullet_t bullets[NUM_BULLETS];
	int w = screen_width();
	int h = screen_height();

	// Run the test driver forever (infinitely creating 3 bullets for each type and moving them until off screen)
	long n = 0;
	bool done = false;
	while(1) {
		// Initialise each of the three bullets such that:
		// - their start position is on an edge of the screen (based on n).
		// - their direction goes towards the opposite edge
		// - the middle bullet of the 3 is a 'mega' bullet
		for (int i = 0; i<NUM_BULLETS; i++) {
			// This rough and dirty code figures out x and y starting coordinates (apologies in advance...you can just pretend it never happened if you like...)
			bullets[i].x = (n % 4 >= DIRECTION_UP) ? (w/(NUM_BULLETS*2)*(1+i*2)) : (n % 4 == DIRECTION_RIGHT) ? 0 : w-1;
			bullets[i].y = (n % 4 <= DIRECTION_RIGHT) ? (h/(NUM_BULLETS*2)*(1+i*2)) : (n % 4 == DIRECTION_UP) ? h-1 : 0;

			// Calculate direction and make the middle bullet 'mega'
			bullets[i].direction = (n % 4);
			bullets[i].is_mega = (i == 1) ? true : false;
		}

		// Draw the bullet motion sequence
		done = false;
		while (!done) {
			// Loop through, drawing and updating each bullet
			clear_screen();
			for (int i = 0; i<NUM_BULLETS; i++) {
				// Draw the bullet
				draw_bullet(bullets[i]);

				// Update the position - dirty syntax again for move up, down, left, or right
				bullets[i].x += (bullets[i].direction <= DIRECTION_RIGHT) ? (bullets[i].direction == DIRECTION_RIGHT) ? 1 : -1 : 0;
				bullets[i].y += (bullets[i].direction >= DIRECTION_UP) ? (bullets[i].direction == DIRECTION_UP) ? -1 : 1 : 0;

				// Evaluate if done - compound assignment operator checking if 'already done' OR this bullet is outside the screen
				done |= (bullets[i].x < 0) || (bullets[i].x >= w) || (bullets[i].y < 0) || (bullets[i].y >= h);
			}
			show_screen();
			timer_pause((n % 4 > 1) ? 100 : 50);
		}


		// Increment n
		n++;
	}

	// Cleanup and exit (although we'll never reach here...)
	cleanup_screen();
	return 0;
}

/*
* Function implementations
*/
void draw_bullet(bullet_t bullet) {
	// TODO get the character based on direction, then draw either the single
	// character or mega version 

	//create temp char variable 
	char c;

	//assign appropriate character to variable depending on direction 
	switch (bullet.direction) {
	case DIRECTION_LEFT:
		c = CHAR_DIRECTION_LEFT;
		break;
	case DIRECTION_RIGHT:
		c = CHAR_DIRECTION_RIGHT;
		break;
	case DIRECTION_UP:
		c = CHAR_DIRECTION_UP;
		break;
	case DIRECTION_DOWN:
		c = CHAR_DIRECTION_DOWN;
	}

	//if mega, draw 3 * 3 grid, else draw simple character
	if (bullet.is_mega) {
		draw_line(bullet.x - 1, bullet.y - 1, bullet.x + 1, bullet.y - 1, c);
		draw_line(bullet.x - 1, bullet.y, bullet.x + 1, bullet.y, c);
		draw_line(bullet.x - 1, bullet.y + 1, bullet.x + 1, bullet.y + 1, c);

	}
	else {
		draw_char(bullet.x, bullet.y, c);
	}
	

}
