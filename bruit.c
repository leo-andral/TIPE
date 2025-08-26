#include "image.h"
#include <assert.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*  Crée du bruit visuel (comme à la télé). 
    Renvoie une image de taille `haut` * `larg` */
Image* creerBruitTV(int haut, int larg) {
    Image* img = creerImage(haut, larg);
    for (int i = 0; i < haut; i += 1) {
        for (int j = 0; j < larg; j += 1) {
            if (rand()%2) setPix(img, i, j, maxColor); // Pixel noir
            else setPix(img, i, j, minColor);          // ou blanc
        }
    }
    return img;
}

/*  Crée un dégradé de couleur. Le pixel (0,0) sera en `maxColor` et le pixel (`haut`, `larg`) en `minColor`. 
    Renvoie une image de taille `haut` * `larg` */
Image* creerDegrade(int haut, int larg) {
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

// Dessine sur `img` un dégradé de couleur circulaire de rayon `r`  et de couleur maximale `couleur_pointe` appliqué au centre
void dessinerCerclesDegrade(Image* img, int r, int couleur_pointe) {
    /*
    rayon = longueur du centre jusqu'à l'extrémité (centre exclu)
    couleurPointe = couleur que prendra le centre du cercle (valeur incluse) 
    */
    int x_centre = rand()%img->haut;
    int y_centre = rand()%img->larg;

    /* Overview of algorith:
    Parcourir tout les pixels dans le carre de longueur 2r + 1 et de millieu le centre de cercle
    Ensuite, set la couleur du pixel en fonction de sa distance au centre */

    for (int i = 0; i < img->haut; i += 1) { // Je parcours toute l'image - A OPTIMISER
        for (int j = 0; j < img->larg; j += 1) {

            // Distance euclidienne du point au centre
            float distance_centre = sqrt((x_centre-i)*(x_centre-i) + (y_centre-j)*(y_centre-j));
            // Dégradé inversé où le milieu est le point culminant
            if (distance_centre <= r) { // Test nécessaire car on parcours toute l'image
                int v = (1 - distance_centre/r)*couleur_pointe + getPix(img, i, j);
                if (v > maxColor) v = maxColor;
                setPix(img, i, j, v);
            }
        }
    }
}

int main() {
    srand(time(NULL)); // Pour pouvoir avoir differents outputs

    Image* test = creerImageCarre(256);
    for (int x = 0; x < 10; x += 1) dessinerCerclesDegrade(test, 60, 125);

    assert(exporterImage(test, "testResults/bloubloublouyb.pgm"));
    detruireImage(test);
    printf("Fait !\n");
    return 0;
}