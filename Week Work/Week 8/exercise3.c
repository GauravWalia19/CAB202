// AVR header file for all registers/pins


#include <avr/io.h>  

#include "cpu_speed.h"

int main(void) {
	//set the cpu speed to 8MHz (also make sure to compile at 8MHz)
	set_clock_speed(CPU_8MHz);

	//Sw3 is connected to pin F5. Configure all pins as Input(0)
	DDRF = 0b00000000;

	//set LED0 for output
	// LED 0 is connected to pin B2 (port B)
	// set PORTB pin 2 for output (on)
	DDRB = 0b00000100;

	//turn off the LED to start with
	PORTB = 0b00000000;

	while (1) {
		//read the input from portf (the sw3) if the bit changes to a 1 (high)
		//send a 1 to PORTB position 2 to turn the light on
		if (PINF & 0b00100000) {
			PORTB = 0b00000100;
		}
		//if the light is not on its off
		else {
			PORTB = 0b00000000;
		}
	}


	return 0;
}