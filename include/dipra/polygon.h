#ifndef POLYGON_H_
#define POLYGON_H_

#include <stdlib.h>

typedef struct {
    double *x;
    double *y;
    size_t n;
} polygon_t;

polygon_t create_polygon(size_t n);
void destroy_polygon(const polygon_t* polygon);

#endif // POLYGON_H_