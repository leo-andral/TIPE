#include <assert.h>
#include <stdio.h>

#include "image.h"
#include "math2.h"
#include "gen_DC.h"


Image* matrice_to_image(Matrice* mat) {
    // printf("Conversion Matrice->Image début\n"); // DEBUG
    Image* img = creerImageCarre(mat->taille);

    for (int i = 0; i < mat->taille; i += 1) {
        for (int j = 0; j < mat->taille; j += 1) {
            uint8_t v = minColor + (maxColor - minColor)*mat->tab[i][j];
            setPix(img, i, j, v);
            // printf("Pixel (%d,%d) = %d\n", i, j, v); // DEBUG
        }
    }
    return img;
}


int main() {
    Matrice* test = creer_matrice(2);
    test->tab[0][1] = 0.5;
    detruit_matrice(test);

    random_setseed(67);

    Matrice* test_gen = creer_matrice(10);
    generation_DC(test_gen, 2);
    Image* img = matrice_to_image(test_gen);
    bool successful_export = exporterImage(img, "testResults/test.pgm");
    assert(successful_export);
    detruireImage(img);
    detruit_matrice(test_gen);
}