#include <stdio.h>

void count_down( void ) {
	// INSERT CODE HERE
	printf("Listing integers in reverse, from 355 down to but not including 24 in steps of 6.\n");
	int count;
	count = 355;
	while(count <= 355 && count > 24) {
       printf("%d\n", &count);
       count--;
	}
}

int main( void ) {
	count_down();
	return 0;
}
