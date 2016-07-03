/*	CAB202: Tutorial 1
*	Question 2 - Template
*
*	B.Talbot, February 2016
*	Queensland University of Technology
*/
#include <stdio.h>

int main() {
    // Count from 0 to 12
    printf("\nFROM 0 TO 12:\n");
    // TODO
    int x;
    for (x=0; x<13; x=x+1)
    {
      printf("%d\n" ,x);
    }

    // Count from 5 to 10
    printf("\nFROM 5 TO 10:\n");
    // TODO
    int i;
    for (i=5; i<11; i=i+1)
    {
      printf("%d\n" ,i);
    }

    // Count from 5 to 0
    printf("\nFROM 5 to 0:\n");
    // TODO
    int y;
    for (y=5; y>-1; y=y-1)
    {
      printf("%d\n" ,y);
    }

    // Count in 2's, from 10 to 30
    printf("\nIN 2's, FROM 10 to 30:\n");
    // TODO
    int w;
    for (w=10; w<31; w=w+2)
    {
      printf("%d\n" ,w);
    }

    // Count in 0.25's, from 0 to 2
    printf("\nIN 0.25's, FROM 0 to 2:\n");
    // TODO
    float q;
    for (q=0.0; q<2.25; q=q+0.25)
    {
      printf("%.2f\n" ,q);
    }

    // Return from main
    return 0;
}
