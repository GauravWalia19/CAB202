/*  CAB202 Tutorial 9
*	Question 3 - Solution
*
*	B.Talbot, May 2016
*	Queensland University of Technology
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

/*
* Useful defines you can use in your system time calculations
*/
#define FREQUENCY 8000000.0
#define PRESCALER 256.0

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
    draw_string(17, 12, "INTERRUPTS");
    draw_string(12, 20, "System time:");

    // Run the main loop
    char buff[80];
    double curr_time = 0.0;
    while (1) {
        // Call a debounced button checker
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

     // Initalising the push buttons as inputs
     DDRF &= ~((1 << PF5) | (1 << PF6));

     // Initialising the LEDs as outputs
     DDRB |= ((1 << PB2) | (1 << PB3));

     // Setup TIMER1 in "normal" operation mode
     // TODO
	 //figure 14.10.3 on page 132 of the data sheet
	 TCCR1B &= ~((1 << WGM12));
     // Set the prescaler for TIMER1 so that the clock overflows every ~2.1 seconds
     // TODO
	 //question 2 used a prescaler of 1024 which is 4x more than 256 8.3 / 4 = 2.075 (2.1 secs)
	 TCCR1B |= (1 << CS12);
	 TCCR1B &= ~((1 << CS11));
	 TCCR1B &= ~((1 << CS10));
     // Enable the Timer Overflow Interrupt for TIMER1
     // TODO
	 //page 136 and lecture demo for info on how to set this
	 TIMSK1 = (1 << TOIE1);

     // Globally enable interrupts
     // TODO
	 //found in lecture slides
	 sei();
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
		 


	 }
 }

double get_system_time(unsigned int timer_count) {
    // Based on the current count, frequency, and prescaler - return the current
    // count time in seconds
    // TODO
	double curr_time = PRESCALER / FREQUENCY;

	return timer_count * curr_time;
}

/*
* Interrupt service routines
*/
ISR(TIMER1_OVF_vect) {
    // Interrupt service routine for TIMER1. Toggle an LED everytime this ISR runs
    // TODO
	PORTB ^= 1 << 3; //whatever LED 1 is flip the bit at this position
	PORTB ^= 1 << 2; //whatever LED 0 is flip the bit at this position
}
