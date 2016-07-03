#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "cab202_timers.h"



void timer_practice() {

	timer_id timer = create_timer(1170); 
	int count = 0;
	                          
		while (count < 18) {
			if (timer_expired(timer)) {

				printf("The current system time is %f\n", get_current_time());
				count++;
			}
			timer_pause(21);
			
		}		
	


}




int main(void) {
	timer_practice();
	return 0;
}