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

void cordic(struct Vector_d * v, int mode)
{
    #ifndef CORDIC_KERNEL
    #define CORDIC_KERNEL(z, x, c, y, i) (z = x + c * (y >> i))
    #endif

    register int32_t x_i, y_i, z_i, x_temp_2, y_temp_2;
    //int32x2_t x_cal, y_cal, res;
    //struct Vector_int32x2_t x, y;
    register int temp, i;
    register int mul;
    double tmp;
    
    tmp = 1 << DESIRED_PRECISION;
    x_i = (int) (v -> x * (1 << PRECISION));
    y_i = (int) (v -> y * (1 << PRECISION));
    z_i = (int) (v -> z * (1 << PRECISION));
    tmp = 1 / tmp;
    /*
    x.a = x_i;
    x.b = ~x_i + 1;
    y.a = y_i;
    y.b = y_i;

    x_cal = vld1_s32(x.a);
    int32_t = 
    printf(x_cal)
    */
    switch (mode) {
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
        
        case 0:
            for( i ^= i; i < PRECISION; i+=2) {
                    temp = AngleTable[i];
                    mul = 1 + (y_i >> 31) - (-y_i >> 31) - 1;
                    //mul = (z_i < 0) ? 1 : -1;
                    CORDIC_KERNEL(x_temp_2, x_i, mul, y_i, i);
                    CORDIC_KERNEL(y_temp_2, y_i, (~mul + 1), x_i, i);
                    z_i += mul * temp;
                    temp = AngleTable[i + 1];

                    mul = 1 + (y_temp_2 >> 31) - (-y_temp_2 >> 31) - 1;
                    //mul = (z_i < 0) ? 1 : -1;
                    CORDIC_KERNEL(x_i, x_temp_2, mul, y_temp_2, (i+1));
                    CORDIC_KERNEL(y_i, y_temp_2, (~mul + 1), x_temp_2, (i+1));
                    z_i += mul * temp;
                }
            break;
    }

    x_i >>= EXTENTION;
    y_i >>= EXTENTION;
    z_i >>= EXTENTION;
    
    v -> x = (double) x_i * tmp;
    v -> y = (double) y_i * tmp;
    v -> z = (double) z_i * tmp;
    #undef CORDIC_KERNEL
}