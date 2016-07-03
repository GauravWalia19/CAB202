/*
*	calc_sqrt: Sample code to demonstrate sentinal-controlled iteration, functions and iteration.
*
*	Copyright 2016 Queensland University of Technology.
*
*	Author: Lawrence Buckingham.
*
*	Revision History:
*	08-Mar-2016 -- Created.
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double my_sqrt( double x );

int main( void ) {
	double t = 0;

	while ( true ) {
		printf( "Please enter a numeric value (negative to exit): " );
		int values_scanned = scanf( "%lf", &t );

		if ( values_scanned <= 0 || t < 0 ) break;

		double y = my_sqrt( t );
		printf( "The square root of %f is approximately %.17f\n", t, y );
	}

	return 0;
}

double my_sqrt( double x ) {
	printf( "x = %f\n", x );

	double curr = x/2;
	double prev = x;

	#define TOLERANCE (1e-10)

	while ( fabs( curr - prev ) > TOLERANCE ) {
		prev = curr;
		curr = ( x / curr + curr ) / 2;
		printf( "curr = %.17f\n", curr );
	}

	return curr;
}
