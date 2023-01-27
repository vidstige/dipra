#ifndef BBOX_H_
#define BBOX_H_

#include <stdlib.h>

typedef struct {
    int x0, y0, x1, y1;
} bbox_t;

bbox_t make_bbox(double *x, double *y, const size_t n);
size_t area(bbox_t *bbox);

#endif // BBOX_H_