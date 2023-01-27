#include "dipra.h"

render_t create_render(size_t n) {
    render_t render;
    render.x = malloc(n * sizeof(render.x));
    render.y = malloc(n * sizeof(render.y));
    render.alpha = malloc(n * sizeof(render.alpha));
    render.n = n;
    return render;
}

void destroy_render(const render_t* render) {
    free(render->x);
    free(render->y);
    free(render->alpha);
}

bbox_t polygon_bbox(const polygon_t *polygon) {
    return make_bbox(polygon->x, polygon->y, polygon->n);
}

size_t dipra_render(const polygon_t *polygon, const bbox_t *bbox, render_t *output) {
}