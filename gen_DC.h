#ifndef _GEN_DC_H_
#define _GEN_DC_H_

// Matrice de taille `taille` = 2 ^ `n` + 1 avec des valeurs entre 0 et 1
typedef struct s_matrice {
    int n;
    int taille;
    double** tab; // Remplacer par des floats = OK (si couleurs dessinees entre 0 et 255)
} Matrice;

// Creation, destruction des images
Matrice* creer_matrice(int n);
void detruit_matrice(Matrice* mat);

// Generation Diamond-Square sur une matrice
void generation_DC(Matrice* mat, double scaling);

#endif