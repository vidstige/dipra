#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "dipra/dipra.h"

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

void draw(image_t *image, const raster_t* raster) {
    for (size_t i = 0; i < raster->n; i++) {
        int x = raster->x[i];
        int y = raster->y[i];
        double alpha = raster->alpha[i];
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
    polygon_t polygon = create_polygon(3);
    polygon.x[0] = 0.0; polygon.y[0] = 0.0;
    polygon.x[1] = 9.0; polygon.y[1] = 5.0;
    polygon.x[2] = 2.0; polygon.y[2] = 8.0;
    bbox_t bbox = polygon_bbox(&polygon);
    raster_t raster = create_raster(bbox_area(&bbox));
    dipra_rasterize(&polygon, &bbox, &raster);
    destroy_polygon(&polygon);
    
    image_t image = create_image(bbox.x1, bbox.y1);
    draw(&image, &raster);
    FILE *f = fopen("images/0.pgm", "w");
    write_pgm(f, &image);
    fclose(f);
    destroy_image(&image);
    destroy_raster(&raster);
    return 0;
}