#include <stdlib.h>
#include "dipra.h"

int main(int argc, const char* argv[]) {
    polygon_t polygon;
    polygon.n = 3;
    polygon.x = malloc(polygon.n * sizeof(polygon.x));
    polygon.y = malloc(polygon.n * sizeof(polygon.y));
    polygon.x[0] = 2.0; polygon.y[0] = 1.0;
    polygon.x[1] = 4.0; polygon.y[1] = 3.0;
    polygon.x[2] = 1.0; polygon.y[2] = 2.0;
    bbox_t bbox = polygon_bbox(&polygon);
    render_t output = create_render(bbox_area(&bbox));
    dipra_render(&polygon, &bbox, &output);
    destroy_render(&output);
    return 0;
}