#ifndef CORDIC_H
#define CORDIC_H

#define PRECISION 17
#define EXTENTION 8
#define SHIFT PRECISION + EXTENTION

//void cordic(long int* x, long int* y, long int* z, long int* angles, int prec);
void cordic(int* x, int* y, int* z, int* angles, int prec);

#endif
