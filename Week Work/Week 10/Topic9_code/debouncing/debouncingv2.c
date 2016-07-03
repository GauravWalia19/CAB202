

/* File: debouncingv2.c
 * Description: C program for the ATMEL AVR microcontroller (ATmega32 chip)
 * test button debouncing and Toggle  ON/OFF LED in the board
 
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

//forward function declarations
void init_hardware(void);
static inline void debounce(void);

// Counter for number of button press 
static uint8_t press_count = 0;


int main(void) {
    

    
    //set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);

    //initialise ports and LCD screen
	init_hardware();	

 
    //initial mesasge
    clear_screen();
    draw_string(4,4,"Debouncing v2");
    show_screen();
    
    //stop for 2 sec
    _delay_ms(2000);
    
    char buff[80];
    while (1)
    {
 			//debounce buttons   
    	    debounce();
            
            //clear screen before we draw on it
            clear_screen();
            
             // Update the count on the screen with the global variable press_count
             sprintf(buff, "%04d", press_count);
             draw_string(32, 28, buff);
            
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
        
        _delay_ms(10);
        
        
    }
    

	return 0;
}

void init_hardware(){
	
    DDRB |= 1 << PINB3; //PIN 3 PORTB for LED1 = output
    DDRB |= 1 << PINB2;  // //PIN 2 PORTB for LED0 = output
     
    DDRF |= (1 << PINF5) | (1 << PINF6) ;// PINS 5 & 6 PORT F for buttons
   
	lcd_init( LCD_DEFAULT_CONTRAST ); // initliase LCD screen
	clear_screen(); //clear screen
	
}



static inline void debounce(void)
{
    
    if (!bit_is_clear(PINF, 5)) {
       _delay_ms(100);
       while((PINF >> PF5) & 1);
       PORTB ^= 1 << PINB3;
       press_count++;
    } else if (!bit_is_clear(PINF, 6)) {
        _delay_ms(100);
        while((PINF >> PF6) & 1);
       PORTB ^= 1 << PINB2;
        press_count--;
    }
}


