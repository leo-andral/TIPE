#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "image.h"

/*
    Bibliothèque pour la manipulation d'images
*/

// Couleur "vide" sur 8 bits
const uint8_t minColor = 0;
// Couleur "pleine" sur 8 bits
const uint8_t maxColor = 255;

// Renvoie la valeur sur 8 bits du pixel (`i`, `j`) sur l'image `img`
uint8_t getPix(Image* img, int i, int j){
    assert(img != NULL);
    assert(i >= 0 && i < img->haut);
    assert(j >=0 && j < img->larg);

    int indice = i * img->larg + j;
    return(img->pixels[indice]);
}

// Défini le pixel (`i`, `j`) sur l'image `img` à `v`
void setPix(Image* img, int i, int j, uint8_t v){
    assert(img != NULL);
    assert(i >= 0 && i < img->haut);
    assert(j >=0 && j < img->larg);

    int indice = i * img->larg + j;
    img->pixels[indice] = v;
}

// Ajoute `v` de couleur au pixel (`i`, `j`) sur l'image `img`
void addPix(Image* img, int i, int j, uint8_t v) {
    assert(img != NULL);
    assert(i >= 0 && i < img->haut);
    assert(j >=0 && j < img->larg);

    int valeur = v + getPix(img, i, j);
    if (valeur > maxColor) valeur = maxColor;
    setPix(img, i, j, valeur);
}

// Crée une `Image` dans le tas de taille `haut` * `larg`
Image* creerImage(int haut, int larg) {
    Image* n_image = (Image*) malloc(sizeof(Image));
    n_image->haut = haut;
    n_image->larg = larg;
    n_image->pixels = (uint8_t*) malloc(haut*larg*sizeof(uint8_t));
    
    for (int i = 0; i < haut; i += 1) {
        for (int j = 0; j < larg; j += 1) {
            setPix(n_image, i , j, minColor);
        }
    }
    
    return n_image;
}

// Crée une `Image` carré dans le tas de taille `taille` * `taille`
Image* creerImageCarre(int taille) {
    Image* img = creerImage(taille, taille);
    return img;
}

// Libére l'espace mémoire alloué par `creerImage` ou `creerImageCarre`
void detruireImage(Image* img) {
    free(img->pixels);
    free(img);
}

// Ecrit l'image sur la sortie `stdout`
void printImage(Image* img) {
    int n = img->haut;
    int p = img->larg;
    int ind = 0;
    printf("-------IMAGE-------\n");
    for (int i = 0; i < n; i+=1){
        for (int j = 0; j < p; j += 1){
            printf("%u ", img->pixels[ind]);
            ind += 1;
        }
        printf("\n");
    }
    printf("-------FIN-------\n");
}

/*
    Import / Export
*/

// Importe le fichier `filename` de format `.ppm`. Renvoie NULL en cas d'erreur
Image* importerImage(char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier \"%s\"\n", filename);
        return NULL;
    }

    int n;
    int p;
    int couleur_max;
    if (fscanf(f, "P2\n%d %d\n%d\n", &p, &n, &couleur_max) != 3) {
        fprintf(stderr, "Fichier \"%s\" invalide (en-tête mal formaté)\n", filename);
        return NULL;
    }

    Image* img = creerImage(n, p);
    int x = 0;
    int couleur;
    while (fscanf(f, "%d\n", &couleur) == 1) {
        setPix(img, x/p, x%p, couleur);
        x += 1;
    }
    
    fclose(f);
    return img;
}

// Exporte `img` en tant que fichier `filename` (format .ppm ). Renvoie false en cas d'erreur, true sinon
bool exporterImage(Image* img, char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Impossible d'ecrire le fichier \"%s\"\n", filename);
        return false;
    }

    int n = img->haut;
    int p = img->larg;

    fprintf(f, "P2\n%d %d\n%d", p, n, maxColor);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < p; j += 1) {
            fprintf(f,"\n%d", getPix(img, i, j));
        }
    }
    fprintf(f, "\n"); // Dernière ligne nécessaire pour dernier pixel

    fclose(f);
    return true;
}


/**
*  Traitement d'image 
**/

/* Redimensionne l'image (nouvelle image) */
// Redimentionnement guez : ne garde pas les proportions A MODIFIER BIEN SUR
Image* redimentionneImage(Image* img, int n_haut, int n_larg) {
    Image* n_img = creerImage(n_haut, n_larg);
    int haut = img->haut;
    int larg = img->larg;
    float ratio_haut = (float)n_haut/haut;
    float ratio_larg = (float)n_larg/larg;
    for (int i = 0; i < n_haut; i += 1) {
        for (int j = 0; j < n_larg; j += 1) {
            setPix(n_img, i, j, getPix(img, i/ratio_haut, j/ratio_larg));
        }
    }
    return n_img;
}