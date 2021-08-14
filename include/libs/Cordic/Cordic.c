#include "./Cordic.h"
int AngleTable[PRECISION] = {
                                3294198, 1944679, 1027514, 521582, 261803, 
                                131029, 65530, 32767, 16383, 8191, 4095, 
                                2047, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1
                            };

void cordic_kernel(int* x, int* y, int* z);

void cordic(struct Vector * v)
{
    int x_i, y_i, z_i;
    x_i = (int) (v -> x * (1 << PRECISION));
    y_i = (int) (v -> y * (1 << PRECISION));
    z_i = (int) v -> z;

    cordic_kernel(&x_i, &y_i, &z_i);

    x_i >>= EXTENTION;
    y_i >>= EXTENTION;
    z_i >>= EXTENTION;

    v -> x = (double) x_i / (1 << DESIRED_PRECISION);
    v -> y = (double) y_i / (1 << DESIRED_PRECISION);
    v -> z = (double) z_i / (1 << DESIRED_PRECISION);
}

void cordic_kernel(int* x, int* y, int* z) 
{
    register int x_temp_1, y_temp_1, z_temp, x_temp_2, y_temp_2;
    register int temp, i;
    int mul;

    x_temp_1 = (int) *x;
    y_temp_1 = (int) *y;
    z_temp   = (int) *z;

    #ifndef CORDIC_KERNEL
    #define CORDIC_KERNEL(z, x, c, y, i) (z = x + c * (y >> i))

    for( i ^= i; i < PRECISION; i+=2) {
        temp = AngleTable[i];
        mul = (y_temp_1 >= 0) ? 1 : -1;
        CORDIC_KERNEL(x_temp_2, x_temp_1, mul, y_temp_1, i);
        CORDIC_KERNEL(y_temp_2, y_temp_1, (~mul + 1), x_temp_1, i);
        z_temp += mul * temp;
        temp = AngleTable[i + 1];

        mul = (y_temp_2 >= 0) ? 1 : -1;
        CORDIC_KERNEL(x_temp_1, x_temp_2, mul, y_temp_2, (i+1));
        CORDIC_KERNEL(y_temp_1, y_temp_2, (~mul + 1), x_temp_2, (i+1));
        z_temp += mul * temp;
    }

    #undef CORDIC_KERNEL
    #endif

    *x = x_temp_1;
    *y = y_temp_1;
    *z = z_temp;
}
