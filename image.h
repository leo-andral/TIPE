#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
#include <stdbool.h>

// Matrice "image" de taille `haut`*`larg` avec valeurs entre minColor et maxColor 
typedef struct s_image {
    int haut;
    int larg;
    uint8_t* pixels;
} Image;

extern const uint8_t minColor;
extern const uint8_t maxColor;

// Modification d'images
uint8_t getPix(Image* img, int i, int j);
void setPix(Image* img, int i, int j, uint8_t v);
void addPix(Image* img, int i, int j, uint8_t v);

// Creation, destruction et transformation d'images
Image* creerImage(int haut, int larg);
Image* creerImageCarre(int taille);
void detruireImage(Image* img);
Image* redim(Image* img, int n_haut, int n_larg);

// Import, export des images en fichier  
Image* importerImage(char* filename);
bool exporterImage(Image* img, char* filename);

// Debug des images
void printImage(Image* img);

#endif