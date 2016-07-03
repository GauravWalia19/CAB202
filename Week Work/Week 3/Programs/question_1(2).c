/*	CAB202: Tutorial 2
*	Question 1 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/
#include <stdbool.h>
#include <math.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"

/*
* Function declarations:
* - implementation of 'draw_racer_at_start()' must be completed to draw the
* racers at the specified positions
*/
void draw_racer_at_start(int player_number);

/*
* Main - nothing needs to be changed in here
*/
int main() {
    // Setup the screen
    setup_screen();

    // Loop through drawing each of the players (with a small delay)
    int player = 1;
    while (player <= 5) {
        draw_racer_at_start(player++);
        show_screen();
        timer_pause(500);
    }

    // Communicate that we are ready, and wait indefinitely
    draw_string(screen_width()/2-8, screen_height()/2, "Ready to race...");
    show_screen();
    while(1);

    // Clean up the screen and return (we will NEVER make it here!)
    cleanup_screen();
    return 0;
}

/*
* Complete this function
*/
void draw_racer_at_start(int player_number) {
    // TODO
}
