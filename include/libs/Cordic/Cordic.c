#include "./Cordic.h"
#include <arm_neon.h>
#include <stdio.h>

struct Vector_int32x2_t {int32_t a; int32_t b;};
int AngleTable[PRECISION] = {
                                3294198, 1944679, 1027514, 521582, 261803, 
                                131029, 65530, 32767, 16383, 8191, 4095, 
                                2047, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1
                            };

void cordic_kernel_vector(int x, int y, int z);
void cordic_kernel_rotation(int x, int y, int z);

/**
 *  Function    : cordic
 *  Input       : vector_d* v, int mode
 *  Description : This is the software implementation of the cordic algorithm.
 *                The mode input defined if the computation is going through either
 *                vector mode or rotation mode.
 *                
 *                If the mode equals 1, the vector mode will be executed;
 *                if the mode equals 0, the rotation mode will be executed.
**/
void cordic(struct Vector_d * v, int mode)
{
    register int32_t x_i, y_i, z_i, x_temp_2, y_temp_2;
    register int temp, i;
    register int mul;
    double tmp;
    
    tmp = 1 << DESIRED_PRECISION;
    x_i = (int) (v -> x * (1 << PRECISION));
    y_i = (int) (v -> y * (1 << PRECISION));
    z_i = (int) (v -> z * (1 << PRECISION));

    //computation power reduction, double division takes 67 cycles, and multiplication only takes 17
    tmp = 1 / tmp;

    // i persoanlly prefer to write two separate functions
    // but for the sake of the performance, we merged two different functions
    // into one huge switch case
    #ifndef CORDIC_KERNEL
    #define CORDIC_KERNEL(z, x, c, y, i) (z = x + c * (y >> i))
    #endif
    switch (mode) {
        // vector mode
        case 1:
                for( i ^= i; i < PRECISION; i+=2) {
                    temp = AngleTable[i];
                    mul = (y_i >= 0) ? 1 : -1;
                    
                    CORDIC_KERNEL(x_temp_2, x_i, mul, y_i, i);
                    CORDIC_KERNEL(y_temp_2, y_i, (~mul + 1), x_i, i);
                    z_i += mul * temp;
                    temp = AngleTable[i + 1];

                    mul = (y_temp_2 >= 0) ? 1 : -1;
                    CORDIC_KERNEL(x_i, x_temp_2, mul, y_temp_2, (i+1));
                    CORDIC_KERNEL(y_i, y_temp_2, (~mul + 1), x_temp_2, (i+1));
                    z_i += mul * temp;
                }
            break;
        
        // rotation mode
        case 0:
            for( i ^= i; i < PRECISION; i+=2) {
                    temp = AngleTable[i];
                    mul = (z_i < 0) ? 1 : -1;
                    CORDIC_KERNEL(x_temp_2, x_i, mul, y_i, i);
                    CORDIC_KERNEL(y_temp_2, y_i, (~mul + 1), x_i, i);
                    z_i += mul * temp;
                    temp = AngleTable[i + 1];

                    mul = (z_i < 0) ? 1 : -1;
                    CORDIC_KERNEL(x_i, x_temp_2, mul, y_temp_2, (i+1));
                    CORDIC_KERNEL(y_i, y_temp_2, (~mul + 1), x_temp_2, (i+1));
                    z_i += mul * temp;
                }
            break;
    }
    #undef CORDIC_KERNEL

    //convert from int back to double
    x_i >>= EXTENTION;
    y_i >>= EXTENTION;
    z_i >>= EXTENTION;
    
    v -> x = (double) x_i * tmp;
    v -> y = (double) y_i * tmp;
    v -> z = (double) z_i * tmp;
}