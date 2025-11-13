#include <math.h>
#include <assert.h>
#include <stdlib.h>

// Matrice de taille `taille` avec des valeurs entre 0 et 1
typedef struct s_matrice {
    int taille;
    double** tab;
} Matrice;

// Initialise par -1 une matrice carré de taille 2^ `n` +1
Matrice* creer_matrice(int n) {
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

// Modifie la valeur de la matrice à la position `i` `j` par `e` si la valeur n'est pas "-1"
void set_val_libre(Matrice* mat, int i, int j, double e) {
    assert(0 <= i && i < mat->taille);
    assert(0 <= j && j < mat->taille);
    if (mat->tab[i][j] == -1)
        mat->tab[i][j] = e;
}

double random_double() {
    int precision = 6;
    return (rand()%precision +1) / pow(10, precision);
}

void generation_DC(Matrice* mat) {
    // Definit les quatres coins de valeurs aléatoires
    set_val_libre(mat, 0, 0, random_double());
    set_val_libre(mat, 0, mat->taille -1, random_double());
    set_val_libre(mat, mat->taille -1, 0, random_double());
    set_val_libre(mat, mat->taille -1, mat->taille -1, random_double());

    

}





int main() {
    Matrice* test = creer_matrice(5);
    test->tab[0][1] = 0.5;
    detruit_matrice(test);
}