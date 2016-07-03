/*	CAB202: Tutorial 4
*	Question 2 - Odds and ends
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
//Lib
#include <stdbool.h>
#include <ncurses.h>

#include "cab202_graphics.h"
#include "cab202_sprites.h"
#include "cab202_timers.h"

/*
* Defines
*/
#define BUCKET_LEFT screen_width()-10
#define BUCKET_RIGHT screen_width()-3
#define BUCKET_TOP screen_height()-4
#define BUCKET_BOTTOM screen_height()-1

#define STEP_CHANGE 1

#define LOOP_STEP 50

#define X_0 5
#define Y_0 20

#define GRAVITY 9

//Global

sprite_id ball_id;
float dx_0, dy_0;
bool shooting;

void draw_game(void);
void process_key_press(int key_in);
void perform_timestep(void);

/*
* Function implementations
*/

void perform_timestep(void) {
	ball_id->x += ball_id->dx * LOOP_STEP / 1000.0;
	ball_id->y += ball_id->dy * LOOP_STEP / 1000.0;
	ball_id->dx += 0;
	ball_id->dy += GRAVITY * LOOP_STEP / 1000.0;

	shooting = ball_id->y < BUCKET_BOTTOM;

	if (!shooting) {
		ball_id->x = X_0;
		ball_id->y = Y_0;
	}
}

void draw_game(void) {
	// Clear the screen
    clear_screen();

	// Display the current "throw velocities"
    draw_string(0, 0, "THROW VELOCITIES:");
    draw_formatted(0, 1, "Horizontal: %.2f", dx_0);
    draw_formatted(0, 2, "Vertical:   %.2f", dy_0);

	// Draw the ball and the bucket
    sprite_draw(ball_id);
    draw_line(BUCKET_LEFT, BUCKET_BOTTOM, BUCKET_RIGHT, BUCKET_BOTTOM, '_');
    draw_line(BUCKET_LEFT, BUCKET_TOP, BUCKET_LEFT, BUCKET_BOTTOM, '|');
    draw_line(BUCKET_RIGHT, BUCKET_TOP, BUCKET_RIGHT, BUCKET_BOTTOM, '|');
}

void process_key_press(int key_in) {
	// Process the arrow keys (noting the direction for 'dy'), and the shoot press
    if (key_in == KEY_UP) {
        dy_0 -= STEP_CHANGE;
    } else if (key_in == KEY_DOWN) {
        dy_0 += STEP_CHANGE;
    } else if (key_in == KEY_LEFT) {
        dx_0 -= STEP_CHANGE;
    } else if (key_in == KEY_RIGHT) {
        dx_0 += STEP_CHANGE;
    } else if (key_in == ' ') {
		// Start the shooting process, and set the initial velocities
        shooting = true;
		ball_id->dx = dx_0;
		ball_id->dy = dy_0;
    }
}

int main() {
	//Setup
	setup_screen();

	//Initialise Sprite
	ball_id = sprite_create(X_0, Y_0, 1, 1, "o");

	//Initialise Timer

	timer_id timer = create_timer(LOOP_STEP);

	shooting = false;

	//Main Loop
	while (1) {
		draw_game();
		show_screen();

		if (!shooting) process_key_press(get_char());
		else perform_timestep();

		while (!timer_expired(timer));
	}

	//Clean up 
	cleanup_screen();

	return 0;
}
