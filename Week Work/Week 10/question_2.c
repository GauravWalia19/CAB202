/*  CAB202 Tutorial 9
*	Question 2 - Solution
*
*	B.Talbot, May 2016
*	Queensland University of Technology
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

/*
* Useful defines you can use in your system time calculations
*/
#define FREQUENCY 8000000.0
#define PRESCALER 1024.0

/*
* Function declarations
*/
void init_hardware(void);

void pause_while_pressed(void);
double get_system_time(unsigned int timer_count);

/*
* Main - initialise the hardware and run the code that blocks for button holds,
* yet prints an up to date system time when not blocked.
*/
int main() {
    set_clock_speed(CPU_8MHz);

    // Setup the hardware
    init_hardware();

    // Draw the static information to the screen
    draw_string(27, 12, "TIMERS");
    draw_string(12, 20, "System time:");

    // Run the main loop
    char buff[80];
    double curr_time = 0.0;
    while (1) {
        // Pause if the right button is pressed
        pause_while_pressed();

        // Get the current system time
        // TODO
		//TCNT1 taken from page 134 
		curr_time = get_system_time(TCNT1);
        // String-ise the current time, and draw it to the screen
        sprintf(buff, "%5.4f", curr_time);
        draw_string(27, 28, buff);

        // Show the screen and have a short nap
        show_screen();
        _delay_ms(100);
    }

    // We'll never get here...
    return 0;
}

/*
* Function implementations
*/
void init_hardware(void) {
    // Initialising the LCD screen
    lcd_init(LCD_DEFAULT_CONTRAST);

    // Initalising the buttons as inputs
    DDRF &= ~((1 << PF5) | (1 << PF6));

    // Initialising the LEDs as outputs
    DDRB |= ((1 << PB2) | (1 << PB3));

    // Set the pins to GUARANTEE that TIMER1 is in "normal" operation mode
    // TODO
	//Set to Normal Timer Mode using  TCCR1B as seen in figure 14.10.3 on page 132 of the data sheet
	TCCR1B &= ~((1 << WGM12));

    // Set the prescaler for TIMER1 so that the clock overflows every ~8.3 seconds
    // TODO
	
	//To find what prescaler to use we do the following 
	
	//Clock Speed = 8000000 (8 mil)
	//Max is the highest value in decimal you can achieve using a particular timer (timer 0 is 8 bits, timer 1 and 3 are 16 bits and timer 4 is 10 bits) 
	//we have been told to use timer 1 which is a 16 bit timer with a Max = 65536
	 
	//for reference ^    8 bits = 11111111 Max = 256     10 bits = 1111111111 Max = 1024   16 bits = 1111111111111111 Max = 65536   (totals found using online binary to decimal calculator)

	////////prescaler = Clock speed / (Max / over flow time (8.3))

	// Max / over flow time = 7895.90

	//Clock speed / 7898.90 = 1013 (which is close to the prescaler of 1024 so we will use a prescaler of 1024
	
	//register and clock select bits are taken from page 132  figure 14.10.3 of data sheet.  Prescaler table (Clock Select Bit Description) used is on page 133 Table 14-6
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TCCR1B &= ~((1 << CS11));
}

void pause_while_pressed(void) {
    // This function should pause if the right button is pressed, and not return
    // until the button is released
    // TODO
	if (!bit_is_clear(PINF, 5)) {
		//a small delay to wait out the bounce effect
		_delay_ms(100);
		//remain in this state while the pin is in this state
		while ((PINF >> PF5) & 1);
		//trigger an interrupt?
		
	}
	
}

double get_system_time(unsigned int timer_count) {
    // Based on the current count, frequency, and prescaler - return the current
    // count time in seconds
    // TODO	
	
	double curr_time = PRESCALER / FREQUENCY;

	return timer_count * curr_time;
}
