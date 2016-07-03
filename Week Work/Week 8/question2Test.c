/*	CAB202: Tutorial 7
*	Question 2 - Template
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int byte = 00000000; 
int bit1 = 3;
int bit2 = 5;

int main() {
	byte |= (1 << bit1);
	printf("The byte is currently" + byte);
	byte ^= byte;
	printf("The byte is currently" + byte);
	int switchValue = (byte >> bit2) & 1;
	printf("The byte is currently" + switchValue);
	

	return 0;
}