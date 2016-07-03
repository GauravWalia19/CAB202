#include <avr/io.h>  
#include <util/delay.h>
#include "cpu_speed.h"


int main(void) {
	//Set clock speed to 8MHz
	set_clock_speed(CPU_8MHz);

	//Switches are connected to port F. Configure them as Input(0)
	DDRF = 0b00000000;

	//The LEDs are connected to portB. Configure LEDs to output
	DDRB = 0b00001100;

	//Turn off LEDs
	PORTB = 0b00000000;

	while (1) {
		if (PINF & 0b00100000) {
			PORTB = 0b00001000;
		}

		if (PINF & 0b01000000) {
			PORTB = 0b00000100;
		}

		//Press DOWN
		if (PINB & 0b10000000) {
			PORTB = 0b00000000;
		}

		//Press UP
		if (PIND & 0b00000010) {
			PORTB = 0b00001100;
		}

		//Press CENTER
		if (PINB & 0b00000001) {
			PORTB ^= 1 << 3;
			PORTB ^= 1 << 2;
			_delay_ms(500);
		}
	}
	return 0;
}