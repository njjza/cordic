#include "./Cordic.h"

//void cordic(long int* x, long int* y, long int* z, long int* angles, int prec) 
void cordic(int* x, int* y, int* z, int* angles, int prec) 
{
    int x_temp_1, y_temp_1, z_temp;
    int x_temp_2, y_temp_2;
    int i;

    x_temp_1 = *x;
    y_temp_1 = *y;
    z_temp = *z;

    for( i=0; i<prec; i++) {
        if( y_temp_1 >= 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += angles[i];
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -= angles[i];
        }
            
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }

    *x = x_temp_1;
    *y = y_temp_1;
    *z = z_temp;
}
