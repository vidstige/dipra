#include "dipra/polygon.h"

polygon_t create_polygon(size_t n) {
    polygon_t polygon;
    polygon.n = n;
    polygon.x = malloc(polygon.n * sizeof(double));
    polygon.y = malloc(polygon.n * sizeof(double));
    return polygon;
}

void destroy_polygon(const polygon_t* polygon) {
    free(polygon->x);
    free(polygon->y);
}
