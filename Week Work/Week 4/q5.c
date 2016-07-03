#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

//double array_prod(double theArray[], int sizeOfArray) {
//	double product = 1;
//	int nonefinite = 0;
//
//	for (int i = 0; i <= sizeOfArray; i++) {
//		if (isfinite(theArray[i])) {
//			product = product * theArray[i];
//		}
//		else if (!isfinite(theArray[i])) {
//			//product = product * 1;
//			nonefinite++;
//		}
//	}
//	if (nonefinite == sizeOfArray) {
//		product = NAN;
//	}
//	if (sizeOfArray == 0) {
//		product = NAN;
//	}
//	return product;
//}

double array_prod(double theArray[], int lengthOfArray) {
	double product = 1;

	for (int i = 0; i < lengthOfArray; i++) {
		if (isfinite(theArray[i])) product *= theArray[i];
	}

	if (product == 1) return NAN;

	return product;
}

void call_function(const char * label, double x[], int count) {
	double prod = array_prod(x, count);
	printf("%s\n", label);
	printf("\tInput data:\n");

	for (int i = 0; i < count; i++) {
		printf("\t%d\t%f\n", i, x[i]);
	}

	printf("\tProduct = %f\n\n", prod);
}

int main(void) {
	double x1[] = { 0 };
	call_function("Count == 0", x1, 0);

	double x2[] = { NAN, +INFINITY, -INFINITY };
	call_function("No finite values", x2, 3);

	double x3[] = { 1, 2, 3, 4, 5, 6, 7 };
	call_function("Several finite values", x3, 7);

	double x4[] = { 2, M_PI, NAN, 3, INFINITY, 4 };
	call_function("A mix of finite values and infinities", x4, 6);

	double x5[] = { 751.882464, 189.015011, 538.658856, 326.276662, 909.438107, 246.239683, 807.379549, 356.780569, 265.542437, 962.057795, 637.070841, 238.920186, 248.962620, 925.586981, 898.062854, 586.912696, 318.236389, 277.164433 };
	call_function("fuck this bullshit", x5, 18);

	return 0;
}