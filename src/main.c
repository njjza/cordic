#include <stdio.h>
#include <stdlib.h>
#include "../include/libs/Cordic/Cordic.h"

void print_integer(int x, int y, int z);
void print_float(double x, double y, double z);

int main (int argc, char** argv)
{
    if (argc != 4) {
        return 0;
    }

    double  x = atof(argv[1]);
    double  y = atof(argv[2]);
    int     z = atoi(argv[3]);

    print_float(x, y, (double) z);

    struct Vector v;

    v.x = x;
    v.y = y;
    v.z = z;

    cordic(&v);
    print_float(v.x, v.y, v.z);

    return 0;
}

void print_float(double x, double y, double z)
{
    printf("Printout Double Results\n");
    printf("\tThe x result equals = %f\n", x);
    printf("\tThe y result equals = %f\n", y);
    printf("\tThe z result equals = %f\n", z);
}