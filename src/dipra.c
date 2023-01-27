#include "dipra.h"
#include <math.h>

#define EPSILON 2.2204460492503131e-16

render_t create_render(size_t n) {
    render_t render;
    render.x = malloc(n * sizeof(render.x));
    render.y = malloc(n * sizeof(render.y));
    render.alpha = malloc(n * sizeof(render.alpha));
    render.n = 0;
    render.capacity = n;
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

typedef struct {
    double x;
    double y;
} vec2;


static vec2 minus(vec2 a, vec2 b) {
    return (vec2) {a.x - b.x, a.y - b.y};
}

static double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

static double magnitude2(vec2 v) {
    return dot(v, v);
}

static double distance2(vec2 a, vec2 b) {
    vec2 delta = minus(b, a);
    return magnitude2(delta);
}

static double distance(vec2 a, vec2 b) {
    return sqrt(distance2(a, b));
}

static vec2 add(vec2 a, vec2 b) {
    return (vec2){a.x + b.x, a.y + b.y};
}

static vec2 scale(double k, vec2 v) {
    return (vec2){k * v.x, k * v.y};
}

static double linesgment_distance(vec2 a, vec2 b, vec2 p) {
    const vec2 lsv = minus(b, a); // line segment vector from a to b
    const float l2 = magnitude2(lsv);
    if (l2 < EPSILON) return distance(a, p); // a == b
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line. 
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    // We clamp t from [0,1] to handle points outside the segment vw.
    const double t = fmax(0, fmin(1, dot(minus(p, a), scale(1.0 / l2, lsv))));
    const vec2 projection = add(a, scale(t, lsv));
    return distance(p, projection);
}

static double sdf(const polygon_t *polygon, vec2 p) {
    return 0.0;
}

void dipra_render(const polygon_t *polygon, const bbox_t *bbox, render_t *output) {
    for (int y = bbox->y0; y < bbox->y1; y++) {
        for (int x = bbox->x0; x < bbox->x1; x++) {
            vec2 p = {x, y};
            double sd = sdf(polygon, p);
        }
    }
}