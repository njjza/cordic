#include <stdio.h>
#include "../include/libs/Cordic/Cordic.h"

void print_integer(int x, int y, int z);
void print_float(double x, double y, double z);

int main (void)
{
    double x = 0.85, y = 0.76;
    int z;
    struct Vector v;

    v.x = x;
    v.y = y;
    v.z = z^z;

    cordic(&v);

    print_float(v.x, v.y, v.z);
}

void print_float(double x, double y, double z)
{
    printf("Printout Double Results\n");
    printf("\tThe x result equals = %f\n", x);
    printf("\tThe y result equals = %f\n", y);
    printf("\tThe z result equals = %f\n", z);
}