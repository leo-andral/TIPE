#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Matrice de taille `taille` avec des valeurs entre 0 et 1
typedef struct s_matrice {
    int taille;
    double** tab; // Remplacer par des floats = OK (si couleurs dessinees entre 0 et 255)
} Matrice;

// Initialise par -1 une matrice carré de taille 2^ `n` +1
Matrice* creer_matrice(int n) {
    assert(n >= 1);
    Matrice* new_mat = malloc(sizeof(Matrice));

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

// Modifie la valeur de la matrice à la position `i` `j` par `e` (valeur entre 0 et 1) si la case n'est pas déjà intialisé
void set_val_libre(Matrice* mat, int i, int j, double e) {
    assert(0 <= i && i < mat->taille);
    assert(0 <= j && j < mat->taille);
    assert(0 <= e && e <= 1);

    if (mat->tab[i][j] == -1)
        mat->tab[i][j] = e;
}

// Renvoie un double entre 0 et 1 (inclus)
double random_double() {
    int precision = 6; // Possible d'extraire la variable mais précision uniforme pour toute les valeur = mieux

    int ordre_grandeur = pow(10, precision);
    double random = rand() % (ordre_grandeur+1);
    return random / ordre_grandeur;
}

// Genère le terrain sur la matrice `mat` en utilisant l'algorithme Diamant-Carré
void generation_DC(Matrice* mat) {
    assert(mat != NULL);
    
    // Definit les quatres coins de valeurs aléatoires
    set_val_libre(mat, 0, 0, random_double());
    set_val_libre(mat, 0, mat->taille -1, random_double());
    set_val_libre(mat, mat->taille -1, 0, random_double());
    set_val_libre(mat, mat->taille -1, mat->taille -1, random_double());

    // Répétition des étapes DIAMANT - CARRÉ jusqu'à une matrice remplie
    for (int etape = 1; etape < mat->taille; etape += 1) {
        // Distance entre les milieux
        int dist = pow(2, etape);

        /* Etape DIAMANT : aucun problème d'accéssibilité, tout les milieux se trouve dans le carré */
        // TODO : Changer le calcul tq (i,j) soit le point à calculer
        
        for (int i = 0; i < mat->taille; i += dist) {
            for (int j = 0; j < mat->taille; j += dist) {
                // La case (i,j) est le coin supérieur gauche du carré qui forme le middle

                // Calcul de la valeur 
                double val_moy = (
                      mat->tab[i][j]      + mat->tab[i][j+dist]
                    + mat->tab[i+dist][j] + mat->tab[i+dist][j+dist]
                ) /4;

                // Ecriture de la valeur
                // TODO : Ajouter la valeur aléatoire
                mat->tab[i + dist/2][j + dist/2] = val_moy;
            }
        }

        /* ETAPE CARRÉ : problème d'accéssibilité sur les bords -> faire la moyenne de 3 points seulement */
        
        bool offset = false;
        for (int i = 0; i < mat->taille; i += dist) {
            if (offset) offset = false;
            else offset = true;

            for (int j = offset*dist; j < mat->taille; j += dist) {
                // Calcul de la valeur
                double somme_val = 0;
                int nbr_val = 0;
                
                // En haut du middle (2eme cond inutile)
                if (0 <= i-dist && i-dist < mat->taille) {
                    somme_val += mat->tab[i-dist][j];
                    nbr_val += 1;
                }
                // A gauche du middle (2eme cond inutile)
                if (0 <= j-dist && j-dist < mat->taille) {
                    somme_val += mat->tab[i][j-dist];
                    nbr_val += 1;
                }
                // En bas du middle (1ere cond inutile)
                if (0 <= i+dist && i+dist < mat->taille) {
                    somme_val += mat->tab[i+dist][j];
                    nbr_val += 1;
                }
                // A droite du middle (1ere cond inutile)
                if (0 <= j+dist && j+dist < mat->taille) {
                    somme_val += mat->tab[i][j+dist];
                    nbr_val += 1;
                }
                
                // Ecriture de la valeur
                // TODO : ajouter la valeur aléatoire
                mat->tab[i][j] = somme_val/nbr_val;
            }
        }        
    }
    printf("Fin de la génération DC\n");
}





int main() {
    Matrice* test = creer_matrice(5);
    test->tab[0][1] = 0.5;
    detruit_matrice(test);

    Matrice* test_gen = creer_matrice(2);
    generation_DC(test_gen);
    detruit_matrice(test_gen);
}