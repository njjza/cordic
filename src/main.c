#include <stdio.h>
#include "../include/libs/Cordic/Cordic.h"

int main (void)
{
    int x_i, y_i, z_i;
    double x = 0.85, y = 0.76, z; 
    
    x_i = (int)(x * (1 << PRECISION));
    y_i = (int)(y * (1 << PRECISION));
    z_i = 0;

    cordic(&x_i, &y_i, &z_i);

    x_i = x_i >> EXTENTION;
    y_i = y_i >> EXTENTION;
    z_i = z_i >> EXTENTION;

    x = (double) x_i / (1 << DESIRED_PRECISION);
    y = (double) y_i / (1 << DESIRED_PRECISION);
    z = (double) z_i / (1 << DESIRED_PRECISION);

    printf("The x result equals = %i\n", x_i);
    printf("The y result equals = %i\n", y_i);
    printf("The z result equals = %i\n", z_i);
}