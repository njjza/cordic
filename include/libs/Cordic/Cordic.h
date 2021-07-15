#ifndef CORDIC_H
#define CORDIC_H

#define DESIRED_PRECISION 17
#define EXTENTION 7
#define PRECISION (DESIRED_PRECISION + EXTENTION)

void cordic(int* x, int* y, int* z);

#endif
