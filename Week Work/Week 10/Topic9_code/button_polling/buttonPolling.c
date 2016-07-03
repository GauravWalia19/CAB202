


#include <avr/io.h> 
#include <util/delay.h> 


#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

void Init(void);
void checkButtons(void);

//GLOBAL VARIABLES
unsigned char heroX = LCD_X/2;
unsigned char heroY = LCD_Y-7;
int button = 0;
int previousButton = 0;

int main(void) {
    
    //set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);

    //initialise ports and lcd screen
	Init();	
    
    //draw an initial character
	clear_screen();
	draw_string(heroX,heroY,"*");
	show_screen();

	while(1){
        
	    checkButtons();
        
		clear_screen();
		draw_string(heroX,heroY,"*");
		show_screen();
	}

	return 0;
}	

//setup  and initialise ports and LCD
void Init(){
	DDRB |= (1<<PINB2)|(1<<PINB3);	//LED0 and LED1 as outputs
	DDRF &= ~((1<<PINF5)|(1<<PINF6));	//Switch2 and Switch3 as input
	DDRB |= (1<<PINB7) |(1<<PINB1) ;	//
	
	PORTB = 0x00; 	// Turn everything off to start with
	lcd_init( LCD_DEFAULT_CONTRAST );
	clear_screen();
	show_screen();
}


//this function checks whether a button has been pressed or not. 
//NOTE: No debouncing is implemeted
void checkButtons(){

    
	if ((PINF>>PINF5)&1){
		heroY = heroY-1;
	}
	if ((PINF>>PINF6)&1){
		heroX = heroX+1;
	}
	
	if ((PINB>>PINB7)&1){
		heroY = heroY+1;
	}
	if ((PINB>>PINB1)&1){
		heroX = heroX-1;
	}
}
