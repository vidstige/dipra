#include "bbox.h"
#include <limits.h>
#include <math.h>

bbox_t make_bbox(double *x, double *y, const size_t n) {
    int min_x = INT_MAX, max_x = INT_MIN;
    int min_y = INT_MAX, max_y = INT_MIN;
    for (size_t i = 0; i < n; i++) {
        int xf = (int)(floor(x[i]));
        int xc = (int)(ceil(x[i]));
        if (xc > max_x) max_x = xc;
        if (xf < min_x) min_x = xf;

        int yf = (int)(floor(y[i]));
        int yc = (int)(ceil(y[i]));
        if (yc > max_y) max_y = yc;
        if (yf < min_y) min_y = yf;
    }
    return (bbox_t) {min_x, min_y, max_x, max_y};
}

int bbox_width(bbox_t *bbox) {
    return bbox->x1 - bbox->x0;
}

int bbox_height(bbox_t *bbox) {
    return bbox->y1 - bbox->y0;
}

int bbox_area(bbox_t *bbox) {
    return bbox_width(bbox) * bbox_height(bbox);
}
