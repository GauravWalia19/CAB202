// AVR header file for all registers/pins


#include <avr/io.h>  

#include "cpu_speed.h"

#include <util/delay.h>


int main(void) {
	//set the cpu speed to 8MHz (also make sure to compile at 8MHz)
	set_clock_speed(CPU_8MHz);

	// LED 0 is connected to pin B2 (port B)
	// set PORTB pin 2 for output (on)
	DDRB = (1 << 2);



	while (1) {	

		// turn ON LED by sending '1' to pin 2
		PORTB = 0b00000100;
		
		//pause for 500ms
		_delay_ms(500);

		// turn OFF LED by sending '0' to pin 2
		PORTB = 0b00000000;
		
		//pause for 500ms
		_delay_ms(500);

		}
		
	return 0;
}