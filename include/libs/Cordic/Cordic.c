#include "./Cordic.h"
int AngleTable[PRECISION] = {
                                13176794, 7778716, 4110059, 2086330, 
                                1047213, 524117, 262122, 131069, 
                                65535, 32767, 16383, 8191, 
                                4095, 2047, 1023, 511, 
                                255, 127, 63, 31, 
                                15, 7, 3, 1                       
                            };

void cordic_kernel(int* x, int* y, int* z);

void cordic(struct Vector * v)
{
    int x_i, y_i, z_i;
    x_i = (int) (v -> x * (1 << PRECISION));
    y_i = (int) (v -> y * (1 << PRECISION));
    z_i = (int) v -> z;

    cordic_vector(&x_i, &y_i, &z_i);

    v -> x = (double) (x_i >> EXTENTION) / (1 << DESIRED_PRECISION);
    v -> y = (double) (y_i >> EXTENTION) / (1 << DESIRED_PRECISION);
    v -> z = (double) (z_i >> EXTENTION) / (1 << DESIRED_PRECISION);
}

void cordic_kernel(int* x, int* y, int* z) 
{
    int x_temp_1, y_temp_1, z_temp;
    int x_temp_2, y_temp_2;
    int i;

    x_temp_1 = *x;
    y_temp_1 = *y;
    z_temp = *z;

    for( i=0; i < PRECISION; i++) {
        if( y_temp_1 >= 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += AngleTable[i];
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -= AngleTable[i];
        }
            
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }

    *x = x_temp_1;
    *y = y_temp_1;
    *z = z_temp;
}
