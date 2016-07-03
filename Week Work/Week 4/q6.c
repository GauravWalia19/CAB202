#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

void create_hist(double theArray[], int useable_length, int output[16]) {
	//This resets all the values in the output array to zero 
	for (int i = 0; i < 16; i++) {
		output[i] = 0;
	}
	for (int i = 0; i < useable_length; i++) {


		if (theArray[i] < 1 && theArray[i] >= 0) {
			output[0]++;
		}
		if (theArray[i] < 2 && theArray[i] >= 1) {
			output[1]++;
		}
		if (theArray[i] < 3 && theArray[i] >= 2) {
			output[2]++;
		}
		if (theArray[i] < 4 && theArray[i] >= 3) {
			output[3]++;
		}
		if (theArray[i] < 5 && theArray[i] >= 4) {
			output[4]++;
		}
		if (theArray[i] < 6 && theArray[i] >= 5) {
			output[5]++;
		}
		if (theArray[i] < 7 && theArray[i] >= 6) {
			output[6]++;
		}
		if (theArray[i] < 8 && theArray[i] >= 7) {
			output[7]++;
		}
		if (theArray[i] < 9 && theArray[i] >= 8) {
			output[8]++;
		}
		if (theArray[i] < 10 && theArray[i] >= 9) {
			output[9]++;
		}
		if (theArray[i] < 11 && theArray[i] >= 10) {
			output[10]++;
		}
		if (theArray[i] < 12 && theArray[i] >= 11) {
			output[11]++;
		}
		if (theArray[i] < 13 && theArray[i] >= 12) {
			output[12]++;
		}
		if (theArray[i] < 14 && theArray[i] >= 13) {
			output[13]++;
		}
		if (theArray[i] < 15 && theArray[i] >= 14) {
			output[14]++;
		}
		if (theArray[i] < 16 && theArray[i] >= 15) {
			output[15]++;
		}
	}

}

void call_function(const char * label, double x[], int count) {
	int hist[15 + 1];
	create_hist(x, count, hist);
	printf("%s\n", label);
	printf("\tInput data:\n");

	for (int i = 0; i < count; i++) {
		printf("\t%d\t%f\n", i, x[i]);
	}

	printf("\tHistogram:\n");

	for (int i = 0; i <= 15; i++) {
		printf("\t%d\t%d\n", i, hist[i]);
	}

	printf("\n");
}

int main(void) {
	srand(time(NULL));

	double x1[] = { 0 };
	call_function("Count == 0", x1, 0);

	double x2[] = { 0, 0, 0 };
	call_function("Three equal values", x2, 3);

	double x3[15 + 1];
	for (int i = 0; i <= 15; i++) {
		x3[i] = i;
	}
	call_function("One value in each bucket", x3, 15 + 1);

	double x4[15 * 2 + 1];
	for (int i = 0; i <= 15 * 2; i++) {
		x4[i] = (15 + 1) * (double)rand() / RAND_MAX;
	}
	call_function("Random values", x4, 15 * 2 + 1);

	return 0;
}