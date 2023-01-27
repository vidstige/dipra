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
} render_t;

render_t create_render(size_t n);
void destroy_render(const render_t* render);

bbox_t polygon_bbox(const polygon_t *polygon);
void dipra_render(const polygon_t *polygon, const bbox_t *bbox, render_t *output);

#endif // DIPRA_H_