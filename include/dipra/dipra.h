#ifndef DIPRA_H_
#define DIPRA_H_

#include <stdlib.h>
#include "bbox.h"
#include "polygon.h"

typedef struct {
    int *x;
    int *y;
    double *alpha;
    size_t n;
    size_t capacity;
} raster_t;

raster_t create_raster(size_t n);
void destroy_raster(const raster_t* raster);

bbox_t polygon_bbox(const polygon_t *polygon);
void dipra_rasterize(const polygon_t *polygon, const bbox_t *bbox, raster_t *output);

#endif // DIPRA_H_