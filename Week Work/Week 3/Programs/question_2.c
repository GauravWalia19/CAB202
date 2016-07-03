/*	CAB202: Tutorial 2
*	Question 2 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"

/*
* Function declarations:
*	- 'has_bomb_hit()' must be completed to return true if the bomb coordinates will hit the base, false if not
*	- 'draw_base()' simply draws the base with edges at 25% and 75% of both screen width and screen height
*/
bool has_bomb_hit(int bomb_x, int bomb_y);
void draw_base();

/*
* Main - nothing needs to be changed here
*/
int main() {
	// Seed the random number generator - based off the system clock so the seed is different every time
	time_t t;
	srand((unsigned) time(&t));

	// Initialise the graphics environment
	setup_screen();

	// Perform the main loop (draw base, then 'bomb' until the base has been hit)
	int bomb_x = 0, bomb_y = 0;
	draw_base();
	show_screen();
	while (!has_bomb_hit(bomb_x, bomb_y)) {
		bomb_x = rand() % screen_width();
		bomb_y = rand() % screen_height();
		draw_char(bomb_x, bomb_y, 'x');
		show_screen();
		timer_pause(750);
	}

	// Finish message
	draw_string(0, screen_height()-1, "The base has been hit!");
	show_screen();
	timer_pause(5000);

	// Tidy up
	cleanup_screen();
}

/*
* Complete this function
*/
bool has_bomb_hit(int bomb_x, int bomb_y) {
	// TODO
	int x_min, x_max;
	int y_min, y_max;
	int w, h;
	w = screen_width();
	h = screen_height();
	x_min = w / 4.f;
	x_max = w / 4.f * 3;
	y_min = h / 4.f;
	y_max = h / 4.f * 3;
	if(x_min <= bomb_x && x_max >= bomb_x && y_min <= bomb_y && y_max >= bomb_y)
	{
		return true;
	}
	return false;
}

/*
* Already complete - no changes needed
*/
void draw_base(int size) {
	float p_min = 0.25f, p_max = 0.75f;
	for (int i = screen_width()*p_min; i< screen_width()*p_max; i++) {
		for (int ii = screen_height()*p_min; ii< screen_height()*p_max; ii++) {
			draw_char(i, ii, 'H');
		}
	}
}
