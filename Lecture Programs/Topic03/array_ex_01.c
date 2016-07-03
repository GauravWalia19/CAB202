/*
 *	array_ex_01.c: Demomstration program which shows how to read a list of 
 *		non-negative values and store them in an array. 
 *
 *	Copyright 2016 Queensland University of Technology.
 *
 *	Author: Lawrence Buckingham.
 *
 *	Revision History:
 *	15-Mar-2016 - Created.
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 100

int read_array( double values[], int max_size );
double array_sum( double values[], int size );
double array_sum_squared( double values[], int size );
double array_min( double values[], int size );
double array_max( double values[], int size );

int main( void ) {
	double values[N] = { 0 };

	int n = read_array( values, N );

	double sum = array_sum( values, n );
	double sum_sq = array_sum_squared( values, n );
	double min = array_min( values, n );
	double max = array_max( values, n );

	printf( "mean = %f\n", sum / n );
	printf( "std  = %f\n", sqrt( sum_sq - sum ) / n );
	printf( "min  = %f\n", min );
	printf( "max  = %f\n", max );

	return 0;
}

int read_array( double values[], int maxSize ) {
	int n = 0;

	while ( n < maxSize ) {
		printf( "Please enter a numeric value (negative to exit): " );

		double t = 0;
		int values_scanned = scanf( "%lf", &t );

		if ( values_scanned <= 0 || t < 0 ) {
			break;
		}

		values[n] = t;
		n++;

		printf( "So far you have entered %d values\n", n );
	}
	
	return n;
}

double array_sum( double values[], int size ) {
	double sum = 0;

	for ( int i = 0; i < size; i++ ) {
		sum += values[i];
	}

	return sum;
}

double array_sum_squared( double values[], int size ) {
	double sum = 0;

	for ( int i = 0; i < size; i++ ) {
		double t = values[i];
		sum += t * t;
	}

	return sum;
}

double array_min( double values[], int size ) {
	double min = HUGE_VAL;

	for ( int i = 0; i < size; i++ ) {
		double t = values[i];

		if ( t < min ) {
			min = t;
		}
	}

	return min;
}

double array_max( double values[], int size ) {
	double max = - HUGE_VAL;

	for ( int i = 0; i < size; i++ ) {
		double t = values[i];

		if ( t > max ) {
			max = t;
		}
	}

	return max;
}
