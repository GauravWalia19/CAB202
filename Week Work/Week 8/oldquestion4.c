// AVR header file for all registers/pins
#include <avr/io.h>  
#include <util/delay.h>
#include "cpu_speed.h"

int main(void) {
	//set the cpu speed to 8MHz (also make sure to compile at 8MHz)
	set_clock_speed(CPU_8MHz);

	//set the switches to take input 
	//the 5 way push button is connected to pin F6 (port F)
	//set all the bits for input (0)
	DDRF = 0b00000000;


	//set both the LEDS for output (1)
	//LED0 is connected to pin B2 (port B)
	//LED1 is connected to pin B3 (port B)
	DDRB = 0b00001100;

	//turn off all the LEDs to start with
	PORTB = 0b00000000;

	while (1) {
		//read the input from port F (the 5 way switch) (F6)

		//if the left button pushed (port B1) 
		if (PINB & 0b00000010) {
			//turn the left LED on and the right led off
			PORTB = 0b00000100;
		}

		//if right
		if (PIND & 0b00000001) {
			//turn the right led on and the left led off
			PORTB = 0b00001000;
		}

		//if up
		if (PIND & 0b00000010) {
			//turn both leds on
			PORTB = 0b00001100;
		}

		//if down
		if (PINB & 0b10000000) {
			//turn both leds off
			PORTB = 0b00000000;
		}

		//if center press
		if (PINB & 0b00000001) {
			//toggle the state of both leds with a delay after 
			PORTB ^= 1 << 3;
			PORTB ^= 1 << 2;
			_delay_ms(500);
		}

	}
	return 0;
}