#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"

void Init(void);
void InterruptInit(void);

//GLOBAL VARIABLES, volatile because I would like to share these bewteen my interrupt routine and main program.
volatile int heroX = LCD_X/2;
volatile int heroY = LCD_Y-20;


int previousButton = 0;

int main(void)
{
    //set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);
    
    
    //call initialisation routines
	Init();	
	

	clear_screen();
	draw_string(10,10,"Interrupt Demo");
	show_screen();
	//
	InterruptInit();

    //stops for 2 secs
    _delay_ms(2000);
    
    //do nothing. stop main program from exiting
    while(1);
	
	
	return 0;
}


//setup and initialise ports and LCD
void Init()
{
	DDRB |= (1<<PINB2)|(1<<PINB3);	//LED0 and LED1 as outputs
	DDRF &= ~((1<<PINF5)|(1<<PINF6));	//Switch2 and Switch3 as input
	PORTB = 0x00; 	// Turn everything off to start with
	lcd_init( LCD_DEFAULT_CONTRAST );
	clear_screen();
	
}


//setup and initialise interrupts
void InterruptInit(void)
{
	//Set to Normal Timer Mode using TCCR0B
    TCCR0B &= ~((1<<WGM02));
    
    //Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(ClockSpeed/Prescaler)
    //Prescaler = 1024
    //Timer Speed = 128 nano seconds
    //Timer Overflow Speed = 32640 nano seconds (Timer Speed * 255) - (255 since 8-bit timer)
    TCCR0B |= (1<<CS02)|(1<<CS00);
    TCCR0B &= ~((1<<CS01));	
    
    //enable interrupt overflow
    TIMSK0 |= (1 << TOIE0);
	
    //Ensure to enable global interrupts as well.
    sei();

}

//implements main code to be execute when interrupt is called
ISR(TIMER0_OVF_vect)
{

    //check pin change. in this case pin 5
	if ((PINF>>PINF5)&1){
		heroX = heroX+1;
	} else if ((PINF>>PINF6)&1){ //check state pin 6
		heroX = heroX-1;
	}
	clear_screen();
	draw_string(heroX,heroY,"^");
	show_screen();
	
	
	PORTB ^= (1<<PINB3);        // toggle LED 1 at a frequency
    PORTB ^= (1<<PINB2);        // toggle LED 2 at a frequency
	
}
