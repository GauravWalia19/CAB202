/*
 *   File: blank.screen.c *   Description: C program for the ATMEL AVR
 microcontroller (ATmega32 chip) *   Write charactes on the the screen *
 * *  Includes (pretty much compulsory for using the Teensy this
 semester) * 	- avr/io.h: port and pin definitions (i.e. DDRB, PORTB,
 PB1, etc) *	- util/delay.h: '_delay_ms()' function *	-
 cpu_speed.h: macros for forcing the CPU speed to 8MHz (nothing else
 should ever be used!) *  - graphics.h: library to interact with the LCD
 */


#include <avr/io.h> include <util/delay.h>
#
#include "graphics.h"
#
#include "cpu_speed.h"
#
#
//wirte the main file
int main(void) {

    // Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
   

    //initialise the LCD screen
   

    //clear any characters that were written on the screen
   

    //fill a buffer (array) of characters with the string
    //"Microcontroller fun begins! - Happy Hacking", in the position x,y
    


    //write the string on the lcd
  


	return 0;
}
