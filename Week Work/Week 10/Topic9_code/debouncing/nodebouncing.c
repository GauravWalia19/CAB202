/* File: nodebouncing.c
 * Description: C program for the ATMEL AVR microcontroller (ATmega32 chip)
 * test button press with no debouncing and Toggle  ON/OFF LED in the board
 
 * Teensy 
 
 * Includes (pretty much compulsory for using the Teensy this semester)
 * 	- avr/io.h: port and pin definitions (i.e. DDRB, PORTB, PB1, etc)
 *
 *	- cpu_speed.h: macros for forcing the CPU speed to 8MHz (nothing else should ever be used!)
 */


#include <avr/io.h> 
#include <util/delay.h> 
#include <stdio.h>


#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

void init_hardware(void);
int check_buttons(void);


int main(void) {
    
    //to check button state
    int Pressed = 0;
    
    //set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);

    //initialise ports and LCD screen
	init_hardware();	

 
    //initial mesasge
    clear_screen();
    draw_string(4,4,"No Debouncing");
    show_screen();
    
    //stop for 2 sec
    _delay_ms(2000);
    
    
    while (1)
    {
        
        if (check_buttons())
        {
            
         if (Pressed == 0)
                {
                    
                    //toggle LED
                    PORTB ^= 1 << PINB3;
                    PORTB ^= 1 << PINB2;
                    
                    //clear screen before we draw on it
                    clear_screen();
                    
                    //check state of PORTB (LEDS pins)
                    int toggle_port_pin_2 = PORTB&0x04;
                    int toggle_port_pin_3 = PORTB&0x08;
                    
                    //check whether pin 2 or 3 are active
                    if(toggle_port_pin_2 == 4){
                        //draw the characters on the screen
                        draw_string(10,20,"LED0");
                       
                    }
                    if(toggle_port_pin_3 == 8){
                        //draw the characters on the screen
                        draw_string(60,20,"LED1");
                        
                    }
                
                    show_screen();
                    Pressed = 1;
               }
          
        }
        else
        {
            
                Pressed = 0;
        }
    }
    

	return 0;
}	

void init_hardware(){
	
	// PIN 3 PORTB for LED1 = output
    DDRB |= 1 << PINB3; 
    // PIN 2 PORTB for LED0 = output 
    DDRB |= 1 << PINB2;  
    
    //set port f pins 5 and 6 as inputs
    DDRF |= (1 << PINF5) | (1 << PINF6);// 
    
    // initliase LCD screen
	lcd_init( LCD_DEFAULT_CONTRAST ); 
	//clear screen
	clear_screen(); 
	
}


//this function checks when the button has been pressed, but checking pin 1 in port B
int check_buttons(void){
	int buttonPressed = 0;
    
    if(!bit_is_clear(PINF, 5)){
		buttonPressed = 1;
	}
	
	if(!bit_is_clear(PINF, 6)){
		buttonPressed = 1;
	}
	
	
	return buttonPressed;
}

