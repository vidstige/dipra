#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "dipra.h"

typedef struct {
    uint8_t *pixels;
    size_t width;
    size_t height;
    size_t stride;
} image_t;


image_t create_image(size_t width, size_t height) {
    image_t image;
    image.width = width;
    image.height = height;
    image.stride = width;
    image.pixels = calloc(image.stride * image.height, sizeof(uint8_t));
    return image;
}

void destroy_image(const image_t *image) {
    free(image->pixels);
}

void draw(image_t *image, const render_t* render) {
    for (size_t i = 0; i < render->n; i++) {
        int x = render->x[i];
        int y = render->y[i];
        double alpha = render->alpha[i];
        printf("%d %d", x, y);
        image->pixels[x + image->stride * y] = (uint8_t)(alpha * 255.0);
    }
}

void write_pgm(FILE* file, image_t *image) {
    fprintf(file, "P5\n");
    fprintf(file, "%ld %ld\n", image->width, image->height);
    fprintf(file, "255\n");
    uint8_t *row = image->pixels;
    for (size_t y = 0; y < image->height; y++) {
        fwrite(row, sizeof(uint8_t), image->width, file);
        row += image->stride;
    }
}

int main(int argc, const char* argv[]) {
    polygon_t polygon;
    polygon.n = 3;
    polygon.x = malloc(polygon.n * sizeof(double));
    polygon.y = malloc(polygon.n * sizeof(double));
    polygon.x[0] = 2.0; polygon.y[0] = 1.0;
    polygon.x[1] = 4.0; polygon.y[1] = 3.0;
    polygon.x[2] = 1.0; polygon.y[2] = 2.0;
    bbox_t bbox = polygon_bbox(&polygon);
    render_t render = create_render(bbox_area(&bbox));
    dipra_render(&polygon, &bbox, &render);
    
    image_t image = create_image(bbox.x1, bbox.y1);
    draw(&image, &render);
    write_pgm(stdout, &image);
    destroy_image(&image);
    destroy_render(&render);
    return 0;
}