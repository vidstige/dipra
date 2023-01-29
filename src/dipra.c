#include <math.h>
#include "dipra/dipra.h"


#define EPSILON 2.2204460492503131e-16

raster_t create_raster(size_t n) {
    raster_t raster;
    raster.x = malloc(n * sizeof(raster.x));
    raster.y = malloc(n * sizeof(raster.y));
    raster.alpha = malloc(n * sizeof(raster.alpha));
    raster.n = 0;
    raster.capacity = n;
    return raster;
}

void destroy_raster(const raster_t* raster) {
    free(raster->x);
    free(raster->y);
    free(raster->alpha);
}

bbox_t polygon_bbox(const polygon_t *polygon) {
    return make_bbox(polygon->x, polygon->y, polygon->n);
}

static double clamp(double lo, double hi, double value) {
    return fmax(lo, fmin(hi, value));
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

static double sign(double x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return x;
}

static double linesgment_distance(vec2 a, vec2 b, vec2 p) {
    const vec2 lsv = minus(b, a); // line segment vector from a to b
    const float l2 = magnitude2(lsv);
    double side = sign((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x));
    if (l2 < EPSILON) return side * distance(a, p); // a == b
    // Consider the line extending the segment, parameterized as v + t (w - v).
    // We find projection of point p onto the line. 
    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
    // We clamp t from [0,1] to handle points outside the segment vw.
    const double t = clamp(0, 1, dot(minus(p, a), scale(1.0 / l2, lsv)));
    const vec2 projection = add(a, scale(t, lsv));
    return side * distance(p, projection);
}

static double sdf(const polygon_t *polygon, vec2 p) {
    double min_d = INFINITY;
    for (size_t i = 0; i < polygon->n; i++) {
        vec2 a = {polygon->x[i], polygon->y[i]};
        vec2 b = {polygon->x[(i + 1) % polygon->n], polygon->y[(i + 1) % polygon->n]};
        double d = linesgment_distance(a, b, p);
        if (d < min_d) min_d = d;
    }

    return min_d;
}

static void raster_add(raster_t *raster, double x, double y, double alpha) {
    raster->x[raster->n] = x;
    raster->y[raster->n] = y;
    raster->alpha[raster->n] = alpha;
    if (raster->n < raster->capacity) raster->n++;
}

void dipra_rasterize(const polygon_t *polygon, const bbox_t *bbox, raster_t *output) {
    output->n = 0;
    for (int y = bbox->y0; y < bbox->y1; y++) {
        for (int x = bbox->x0; x < bbox->x1; x++) {
            vec2 p = {x, y};
            double alpha = clamp(0, 1, sdf(polygon, p));
            //double alpha = sdf(polygon, p) + 0.5;
            raster_add(output, x, y, alpha);
        }
    }
}