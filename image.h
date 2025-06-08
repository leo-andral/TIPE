#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct s_image {
    int haut;
    int larg;
    uint8_t* pixels;
} Image;

extern const int maxColor;

uint8_t getPix(Image* img, int i, int j);
void setPix(Image* img, int i, int j, uint8_t v);

Image* creerImage(int haut, int larg);
void detruireImage(Image* img);
void printImage(Image* img);
Image* redim(Image* img, int n_haut, int n_larg);

Image* importerImage(char* filename);
bool exporterImage(Image* img, char* filename);

#endif