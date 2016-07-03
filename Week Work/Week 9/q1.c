#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#include <stdio.h>

#include "cpu_speed.h"
#include "graphics.h"
#include "sprite.h"

#include "lcd.h"

int main(void) {
	//set the cpu speed to 8MHz (also make sure to compile at 8MHz)
	set_clock_speed(CPU_8MHz);

	//set the led for the display to output
	DDRC = 0b10000000;

	//turn the backlight of the screen on
	PORTC = 0b10000000;

	//initialize the LCD
	lcd_init(LCD_DEFAULT_CONTRAST);

	//clear any characters that may have been written on the screen
	clear_screen();

	//draw a vertical line on the right edge of the screen 
	draw_line(82, 0, 82, 48);

	//draw my name
	draw_string(24, 15, "Tom");
	
	//draw student number
	draw_string(24, 25, "9499776");

	// Create a sprite
	Sprite sqaure;

	////create the bitmap

	//the bitmap we want to create/draw
	unsigned char bm[] = {
		0b11111111, 
		0b10000001, 
		0b10000001, 
		0b10000001, 
		0b10000001, 
		0b10000001, 
		0b10000001,
		0b11111111		
	};

	////initialise the sprite at a given position and with a given size
	init_sprite(&sqaure, 0, 0, 8, 8, bm);

	////draw the sprite
	draw_sprite(&sqaure);

	//show the screen
	show_screen();

	return 0;
}