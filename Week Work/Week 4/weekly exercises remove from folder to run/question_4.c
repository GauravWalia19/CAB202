/*	CAB202: Tutorial 3
*	Question 4 - Template
*
*	B.Talbot, March 2016
*	Queensland University of Technology
*/


#include <ncurses.h>
#include "cab202_graphics.h"

/*
*Globals go here
*/


//define name and number array 
char name_array[] = "Tom Stark";
char number_array[] = "n9499776";


//define name and number length
const int name_length = 9;
const int number_length = 8;

//initialise indices 

int name_ind = 0;
int number_ind = 0;

//Big comment here

int current_array = 0;


/*

*Function declarations

*/

void draw_screen();
void process_key_press(int key_in);

/*
*Main Function
*/

int main() {
	setup_screen();


	//Run through the main loop

	while (1) {
		//Draw the current state of things 
		draw_screen();

		//Wait for a key press, processing it when received
		process_key_press(wait_char());

	}

	//Clean and exit (although we'll never reach here...)

	clear_screen();
	return 0;

}

/*

*Function implementations

*/

void draw_screen() {
	//setup strings depending on value of current_array
	clear_screen();

	draw_string(0, 0, "Current Array is: ")
	draw_string(18, 0, (!current_array) ? "NAME" : "STUDENT NUMBER"); 
	draw_string(0, 1 "Current Array index is: ");
	draw_int(24, 1, (!current_array) ? name_ind : number_ind);

	//if current_array = 0 (name) else (number)

	if (!current_array) {
		draw_char(screen_width() / 2, screen_height() / 2, name_array[name_ind]);
	}
	else {
		draw_char(screen_width() / 2 - 4 + number_ind, screen_height() / 2, '*');
		draw_string(screen_width() / 2 - 4, screen_height() / 2 + 1, number_array);
	}

	//draw the current character in the middle of the show_screen


	//draw the student number and asterisk

	//show screen
	show_screen();
}

void process_key_press(int key_in) {
	//A long long series of nested conditions... could compact this down if we 
	// were interesed in using ternary operatiors....
	//if t then toggle between arrays
	if (key_in == 't') {
		current_array = !current_array;
	}
	else if (key_in == KEY_LEFT) {
		if (!current_array) {
			name_ind = (name_ind + name_length - 1) % name_length;
		}
		else {
			number_ind = (number_ind + number_length - 1) % number_length;
		}
	}
	else if (key_in == KEY == RIGHT) {
		if (!current_array) {
			name_ind = (name_ind + 1) % name_length;
		}
		else {
			number_ind = (number_ind + 1) % number_length;
		}
	}
	else if (current_array && key_in >= '0' && key_in <= '8') {
		char selected = number_array[number_ind];
		number_array[number_ind] = number_array[key_in - 0];
		number_array[key_in - '0'] = selected;
	}

	//Toggle between 1 and 0

	//else if left then move left, wrap with modulo operator

	//Bonas points for why we have to add the length when using the % operator...

	//else if right then move right, wrap with modulo operator 

	//else if number between 0 and 8 is pressed, create local copy and swap with index charater 

	//local copy to facilitae the swap 
}





