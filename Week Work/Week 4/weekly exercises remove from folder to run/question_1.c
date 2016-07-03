/*	CAB202: Tutorial 3
*	Question 1 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/
#include <stdlib.h>
#include <time.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"

# define HISTORY_LENGTH 50
# define TIMER_LENGTH 950

/*
* Global variables
*/
int work_duration;
long work_total = 0;

/*
* Function declarations:
*	- 'work_for_actually_1s()' must be completed to do what the name says. Use the
* 	timer and get it as close to 1s as possible.
*	- 'work_for_hopefully_1s()' assumes 50ms for 'do_around_50ms_work()'. This is
*	nowhere near correct.
*	- 'do_around_50ms_work()' does some fake work (just sleeps) but takes a random
*	time which is biased differently during each frame duration.
*	- 'get_average()' is a short helper function for computing the average of an
*	array
*/
void work_for_actually_1s(timer_id timer);
void work_for_hopefully_1s();

void do_around_50ms_work();

double get_average(double values[], int length);

/*
* Main:
*	- Draws all of the static screens and then runs the main loop.
*	- The loop calls a work function, then computes frame rate stats and draws
*	them to the screen.
*	- The implementation currently calls the 'hopefully' function. CHANGE this to
*	your implementation of the 'actually' work function.
*/
int main() {
	// Seed the random number generator - (and pick an average work duration)
	time_t t;
	srand((unsigned) time(&t));

	// Initialise the graphics environment
	setup_screen();

	// Draw all of the static elements with a pretty title
	for (int i = 0; i<screen_width(); i++) {
		draw_char(i, 0, '-');
		draw_char(i, 1, '-');
		draw_char(i, 2, '-');
		draw_char(i, 3, '-');
	}
	draw_string(screen_width()/2-11, 1, " MY SUPER SMOOTH GAME ");
	draw_string(screen_width()/2-37, 2, " (when I don't know if my computer is working hard or hardly working...) ");
	draw_string(screen_width()/2-13, screen_height()/2-4, "The desired frame rate is:");
	draw_string(screen_width()/2-5, screen_height()/2-3, "1.000   FPS");
	draw_string(screen_width()/2-13, screen_height()/2-1, "The current frame rate is:");
	draw_string(screen_width()/2+2, screen_height()/2, " FPS");
	draw_string(screen_width()/2-13, screen_height()/2+2, "The average frame rate is:");
	draw_string(screen_width()/2+2, screen_height()/2+3, " FPS");
	draw_string(screen_width()/2-10, screen_height()/2+5, "Total work done is:");

	// Create all of the variables used in the game (including a timer *...hint hint hint...*)
	double fps_history[HISTORY_LENGTH];
	int iteration_count = 0;
	double fps_current, fps_average, last_time = get_current_time();

	// TODO UNCOMMENT THE LINE BELOW (commented to stop irritating "unused variable warning" being treated as an error...)
	//timer_id timer = create_timer(TIMER_LENGTH);

	// Run the game infinitely
	while(1) {
		// Biased our work duration for an entire frame for the sake of demonstration (value is 50+-49)
		work_duration = 1 + rand() % 98;

		// Get some work done while waiting for the next screen redraw TODO swap the commenting so 'work_for_actually_1s()' runs!
		// TODO comment the line below
		work_for_hopefully_1s();
		// TODO uncomment the line below
		//work_for_actually_1s(timer);

		// Calculate the new values for the statistics
		fps_current = 1 / (get_current_time()-last_time);
		fps_history[iteration_count % HISTORY_LENGTH] = fps_current;
		iteration_count++;
		fps_average = get_average(fps_history, (iteration_count > HISTORY_LENGTH) ? HISTORY_LENGTH : iteration_count);

		// Draw the updated values for the statistics
		draw_formatted(screen_width()/2-5, screen_height()/2, "%5.3f ", fps_current);
		draw_formatted(screen_width()/2-5, screen_height()/2+3, "%5.3f ", fps_average);
		draw_formatted(screen_width()/2-3, screen_height()/2+6, "%5.d", work_total);
		show_screen();

		// Save the end of loop time
		last_time = get_current_time();
	}

	// Cleanup and exit (although we'll never reach here...)
	cleanup_screen();
	return 0;
}

/*
* Complete this function
*/
void work_for_actually_1s(timer_id timer) {
	// TODO complete this so that you use the timer to exit this function after 1s is up!
}

/*
* Already complete - no changes are needed from this point onwards. All of these
* provide the functionality
*/
void work_for_hopefully_1s() {
	// Run 'around 50ms' of work 20 times for a total of 1 second
	for (int i = 0; i<20; i++) {
		do_around_50ms_work();
	}
}

void do_around_50ms_work() {
	work_total++; // Global work total that we display
	timer_pause(work_duration); // Let's just pretend this is real work for now.... (uses the biased global 'work_duration' variable)
}

double get_average(double values[], int length) {
	double total = 0;
	for (int i = 0; i<length; i++) {
		total += values[i];
	}
	return total / length;
}
