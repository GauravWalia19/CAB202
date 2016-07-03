#include <stdio.h>

void list_integers( void ) {
	// INSERT CODE HERE
	printf("\nCounting from 38 up to 316... \n");
	
	int count = 38;
	while (count <= 316) {
		printf("%d \n", count);
		count++;
	}
}

int main( void ) {
	list_integers();
	return 0;
}
