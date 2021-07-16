#ifndef CORDIC_H
#define CORDIC_H

#define DESIRED_PRECISION 17
#define EXTENTION 7
#define PRECISION (DESIRED_PRECISION + EXTENTION)

struct Vector {double x; double y; double z;};
void cordic(struct Vector * v);

#endif
