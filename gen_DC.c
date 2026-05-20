#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "gen_DC.h"
#include "math2.h"

// Initialise par -1 une matrice carré de taille 2^ `n` +1
Matrice* creer_matrice(int n) {
    assert(n >= 1);
    Matrice* new_mat = malloc(sizeof(Matrice));

    new_mat->n = n;
    new_mat->taille = pow(2, n) + 1;
    new_mat->tab = malloc((new_mat->taille)*sizeof(double*));

    // Création du tableau dans le tas avec initialisation à -1
    for (int i = 0; i < (new_mat->taille); i += 1) {
        new_mat->tab[i] = malloc((new_mat->taille)*sizeof(double));
        for (int j = 0; j < (new_mat->taille); j += 1) {
            new_mat->tab[i][j] = -1; // Initialisation des cases, à changer si pas ouf
        }
    }
    return new_mat;
}

// Detruit la matrice alloué dans le tas
void detruit_matrice(Matrice* mat) {
    for (int i = 0; i < mat->taille; i += 1) {
        free(mat->tab[i]);
    }
    free(mat->tab);
    free(mat);
}

/*
    Modifie la valeur de la matrice à la position `i` `j` par `e` (valeur entre 0 et 1) si la case n'est pas déjà intialisé
    Si `e` plus grand que 1, initialise a 1
    Si `e` plus petit que 0, initialise a 0
    Renvoie true si la case a été initialisé, false sinon
*/
bool set_val_libre(Matrice* mat, int i, int j, double e) {
    assert(0 <= i && i < mat->taille);
    assert(0 <= j && j < mat->taille);

    if (e < 0) e = 0;
    else if (1 < e) e = 1;

    if (mat->tab[i][j] == -1) {
        mat->tab[i][j] = e;
        return true;
    }
    return false;
}

/*
    Genère le terrain sur la matrice `mat` en utilisant l'algorithme Diamant-Carré
    L'importance de la valeur aléatoire ajouté selon l'étape est définit par `scaling` càd
    que chaque étape ajoutera `scaling` fois moins d'aléatoire
*/
void generation_DC(Matrice* mat, double scaling) {
    assert(mat != NULL);
    
    // Definit les quatres coins de valeurs aléatoires
    set_val_libre(mat, 0, 0, random_double_global());
    set_val_libre(mat, 0, mat->taille -1, random_double_global());
    set_val_libre(mat, mat->taille -1, 0, random_double_global());
    set_val_libre(mat, mat->taille -1, mat->taille -1, random_double_global());

    // Multiplicateur décroissant de la valeur d'aléatoire ajouté à chaque étape 
    double multiplicateur_aleatoire = 1/scaling;

    // Répétition des étapes DIAMANT - CARRÉ jusqu'à une matrice remplie ( `n` étape )
    for (int etape = 0; etape < mat->n; etape += 1) {
        // Distance entre les points déjà générés / les millieux consécutifs
        int dist = pow(2, mat->n - etape);
        int dist_2 = dist/2;
        
        // printf("Debut etape %d / Dist = %d\n", etape, dist); // DEBUG
        /*
            Etape DIAMANT : aucun problème d'accéssibilité, tout les milieux se trouve dans le carré
            Les milieux à calculer se trouvent dans un cadrillage carré, de distance `dist`, démarrant au point (`dist_2`, `dist_2`)
            Le point (i,j) est le milieu à calculer
        */
        // printf("Debut etape DIAMANT\n"); // DEBUG
        for (int i = dist_2; i < mat->taille; i += dist) {
            for (int j = dist_2; j < mat->taille; j += dist) {

                // Calcul de la valeur moyenne
                double val_moy = (
                    /* Les valeurs récupérés respectivement par rapport au milieu/point (i,j) :
                          Nord-Ouest + Nord-Est
                        + Sud-Ouest  + Sud-Est
                    */
                      mat->tab[i-dist_2][j-dist_2] + mat->tab[i-dist_2][j+dist_2]
                    + mat->tab[i+dist_2][j-dist_2] + mat->tab[i+dist_2][j+dist_2]
                ) /4;

                // Ecriture de la valeur
                // TODO : Ajouter VRAIMENT la valeur aléatoire
                set_val_libre(mat, i, j, val_moy + random_pos_neg()*multiplicateur_aleatoire);
                // printf("Point genere : (%d, %d) = %f \n", i, j, mat->tab[i][j]); // DEBUG
            }
        }

        /*
            ETAPE CARRÉ : problème d'accéssibilité sur les bords -> faire la moyenne de 3 points seulement
            Les milieux à calculer se trouvent dans un cadrillage diagonal, de distance `dist` , démarrant au point (0, `dist_2`)
            Le point (i,j) est le milieu à calculer
        */
        // printf("ETAPE CARRÉ\n"); // DEBUG
        bool offset = true; // Booléan sur le décallage du cadrillage
        for (int i = 0; i < mat->taille; i += dist_2) {
            for (int j = offset*dist_2; j < mat->taille; j += dist) {
                // Calcul de la valeur
                double somme_val = 0;
                int nbr_val = 0;
                
                // En haut du point (2eme cond inutile)
                if (0 <= i-dist_2 && i-dist_2 < mat->taille) {
                    somme_val += mat->tab[i-dist_2][j];
                    nbr_val += 1;
                }
                // A gauche du point (2eme cond inutile)
                if (0 <= j-dist_2 && j-dist_2 < mat->taille) {
                    somme_val += mat->tab[i][j-dist_2];
                    nbr_val += 1;
                }
                // En bas du point (1ere cond inutile)
                if (0 <= i+dist_2 && i+dist_2 < mat->taille) {
                    somme_val += mat->tab[i+dist_2][j];
                    nbr_val += 1;
                }
                // A droite du point (1ere cond inutile)
                if (0 <= j+dist_2 && j+dist_2 < mat->taille) {
                    somme_val += mat->tab[i][j+dist_2];
                    nbr_val += 1;
                }
                
                // Ecriture de la valeur
                // TODO : ajouter VRAIMENT la valeur aléatoire
                set_val_libre(mat, i, j, somme_val/nbr_val + random_pos_neg()*multiplicateur_aleatoire);
                // printf("Point genere : (%d, %d) = %f\n", i, j, mat->tab[i][j]); // DEBUG
            }
            // Le décallage du cadrillage se fait 1 fois sur 2
            offset = !offset;
        }
        // La valeur aléatoire est moins importante après chaque étape
        multiplicateur_aleatoire = multiplicateur_aleatoire/scaling;
    }
    // printf("Fin de la génération DC\n"); // DEBUG
}