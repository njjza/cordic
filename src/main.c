#include <stdio.h>
#include "../include/libs/Cordic/Cordic.h"
#include <math.h>

//int gen_angleTable(long int *z, int prec);
int gen_angleTable(int *z, int prec);

//long int angleTable[prec];
int angleTable[SHIFT];
int main (void)
{
    int result, x_i, y_i;
    double x = 0.85, y = 0.76; 

    x_i = (int)(x * (1 << SHIFT));
    y_i = (int)(y * (1 << SHIFT));
    result = 0;

    
    gen_angleTable(angleTable, SHIFT);
    cordic(&x_i, &y_i, &result, angleTable, SHIFT);
	
    /*
    printf("The x result equals = %ld\n", x_i);
    printf("The y result equals = %ld\n", y_i);
    printf("The z result equals = %ld\n", (result));
    */

    printf("The x result equals = %i\n", x_i);
    printf("The y result equals = %i\n", y_i);
    printf("The z result equals = %i\n", (result >> EXTENTION));
}

//int gen_angleTable(long int *z, int prec) 
int gen_angleTable( int *z, int prec) 
{
    for (int i=0; i<prec; i++) 
    {
        z[i] = (int)(atan(pow(2.0, (double)(-i))) * (1 << prec));
    }
}

/*
    // hand crafted angle table for performance increase
    int angleTable [ACCURACY] = {   102943, 60771, 32109, 16299, 
                                    8181, 4094, 2047, 1023, 
                                    511, 255, 127, 63, 31, 
                                    15, 7, 3, 1
                                };

    int angleTable [ACCURACY] = {   25735, 15192, 8027, 4074, 
                                    2045, 1023, 511, 255, 
                                    127, 63, 127, 63, 31, 
                                    15, 7, 3, 1
                                };
    */