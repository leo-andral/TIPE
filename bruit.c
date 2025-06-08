#include "image.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Image* creerBruitTV(int haut, int larg) {
    Image* img = creerImage(haut, larg);
    for (int i = 0; i < haut; i += 1) {
        for (int j = 0; j < larg; j += 1) {
            int pix = (rand()%2)*maxColor;   // Pixel noir ou blanc
            setPix(img, i, j, pix);
        }
    }
    return img;
}

Image* creerGradiant(int haut, int larg) {
    Image* img = creerImage(haut, larg);
    for (int i = 0; i < haut; i += 1) {
        for (int j = 0; j < larg; j += 1) {
            float x = (float)i/haut;
            float y = (float)j/larg;
            int pix = (x*maxColor + y*maxColor)/2;
            setPix(img, i, j, pix);
        }
    }
    return img;
}

int main() {
    Image* test = creerGradiant(16, 16);
    assert(exporterImage(test, "results/testGrad2.pgm"));
    detruireImage(test);
    printf("Fait !\n");
    return 0;
}