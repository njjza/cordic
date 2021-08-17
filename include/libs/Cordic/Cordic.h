#ifndef CORDIC_H
#define CORDIC_H

#define DESIRED_PRECISION 17
#define EXTENTION 5
#define PRECISION (DESIRED_PRECISION + EXTENTION)

struct Vector_d {double x; double y; double z;};
void cordic(struct Vector_d * v, int mode);

#endif
