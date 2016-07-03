/* File: debouncing.c
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

void init_hardware(void);
int checkButtons(void);


int main(void) {
    
    //to check button state
    int Pressed = 0;
    int Pressed_Confidence_Level = 0; //Measure button press cofidence
    int Released_Confidence_Level = 0; //Measure button release confidence

    
    //set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);

    //initialise ports and LCD screen
	init_hardware();	

 
    //initial mesasge
    clear_screen();
    draw_string(4,4,"Debouncing");
    show_screen();
    
    //stop for 2 sec
    _delay_ms(2000);
    
    
    while (1)
    {
        
        if (checkButtons())
        {
            Pressed_Confidence_Level ++; //Increase Pressed Confidence
            Released_Confidence_Level = 0; //Reset released button confidence since there is a button press
            
         if(Pressed_Confidence_Level > 1000)
         {
             
          if (Pressed == 0) 
                {
                    //toggle the output between LED 0 and LED 1
                    PORTB ^= 1 << PINB3;
                    PORTB ^= 1 << PINB2;
                    
                    //clear screen before we draw on it
                    clear_screen();
                    
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
             //Zero it so a new pressed condition can be evaluated
             Pressed_Confidence_Level = 0;
         }
          
        }
        else
        {
            
            Released_Confidence_Level ++; //This works just like the pressed
            Pressed_Confidence_Level = 0; //Reset pressed button confidence since the button is released
            if (Released_Confidence_Level > 1000)
            {
                Pressed = 0;
                Released_Confidence_Level = 0;
            }
        }
    }
                

	return 0;
}	

void init_hardware(){
	
    DDRB |= 1 << PINB3; //PIN 3 PORTB for LED1 = output
    DDRB |= 1 << PINB2;  // //PIN 2 PORTB for LED0 = output
    
    DDRF &= ~(1 << PINF5);// PIN 5 PORT F for Switch 3 = input
    
    
	lcd_init( LCD_DEFAULT_CONTRAST ); // initliase LCD screen
	clear_screen(); //clear screen
	
}


//this function checks when the button has been pressed, but checking pin 1 in port B
int checkButtons(){
	int buttonPressed = 0;
    
    if(!bit_is_clear(PINF, 5)){
		buttonPressed = 1;
	}
	
	return buttonPressed;
}

