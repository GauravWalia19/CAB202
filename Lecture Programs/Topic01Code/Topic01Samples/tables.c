#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

int main( void ) {
	printf( "x,sin(x),cos(x),tan(x)\n" );

	double lower_bound = -2 * M_PI;
	double upper_bound = 2 * M_PI;
	int steps = 100;

	for ( int i = 0; i <= steps; i++ ) {
		double x = lower_bound + i * ( upper_bound - lower_bound ) / steps;
		double sin_x = sin( x );
		double cos_x = cos( x );
		double tan_x = tan( x );
		printf( "%f,%f,%f,%f\n", x, sin_x, cos_x, tan_x );
	}

	return 0;
}