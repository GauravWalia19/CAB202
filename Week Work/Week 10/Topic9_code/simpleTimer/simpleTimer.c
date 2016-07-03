


#include <avr/io.h> 
#include <util/delay.h> 
#include <stdio.h>


#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

#define FREQUENCY 8000000.0
#define PRESCALER 1024.0


void Init(void);
void TimerInit(void);



int main(void) {
    
    //set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);

    //initialise ports and LCD screen
	Init();
    
    //initialiase timer
    TimerInit();

 
    //initial mesasge
    clear_screen();
    draw_string(4,4,"Simple Timer");
    show_screen();
    
    //stop for 2 sec
    _delay_ms(2000);
    
    //temp buffer
    char buffer[80];
    double curr_time = 0.0;
    while (1)
    {
    
            
        clear_screen();
        PORTB ^= (1<<PINB3);        // toggle LED 1 at a frequency
        PORTB ^= (1<<PINB2);        // toggle LED 2 at a frequency
        curr_time = PRESCALER * TCNT0 / FREQUENCY;
        sprintf(buffer,"%f",curr_time); //
        draw_string(20,20,buffer);  // print value of the counter
        show_screen();
            
        _delay_ms(100);
       
    }
                

	return 0;
}	

void Init(){
	
    DDRB |= 1 << PINB3; //PIN 3 PORTB for LED1 = output
    PORTB ^= 1 << PINB3; // 
    DDRB |= 1 << PINB2;  // //PIN 2 PORTB for LED2 = output
    PORTB |= 1 << PINB2; //
    
    
	lcd_init( LCD_DEFAULT_CONTRAST ); // initliase LCD screen
	clear_screen(); //clear screen
	
}


void TimerInit(void)
{
    //Set to Normal Timer Mode using TCCR0B
    TCCR0B &= ~((1<<WGM02));
    
    //Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(Clock Speed/Prescaler)
    //Prescaler = 1024
    //Timer Speed = 128 nano seconds
    //Timer Overflow Speed = 32640 nano seconds (Timer Speed * 255) - (255 since 8-bit timer)
    TCCR0B |= (1<<CS02)|(1<<CS00);
    TCCR0B &= ~((1<<CS01));
}

