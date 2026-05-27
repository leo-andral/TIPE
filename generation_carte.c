#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

void print_cli_help() {
    printf("Utilisation : generation_carte TAILLE FICHIER\n");
    printf("         ou : generation_carte TAILLE FICHIER ROUGHNESS SEED\n");
    printf("Genere une heightmap carré au format .ppm en utilisant l'algorithme Diamant-Carré\n");
    printf("\n");
    printf("Paramètres disponibles :\n");
    printf("    EXAMPLE (= valeur par défaut) : explication\n");
    printf("\n");
    printf("    TAILLE : entier superieur a 0 tel que l'image fasse (2^TAILLE)+1 de large.\n");
    printf("    FICHIER : le nom du fichier de sortie\n");
    printf("    ROUGHNESS (= 1.0) : float entre 0. et 1. définissant \"l'aléatoirité\" du terrain généré\n");
    printf("    SEED (= aléatoire) : entier étant la graine d'aléatoire utilisé\n");
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "generation_carte : parametres manquants pour la generation\n");
        print_cli_help();
        return 22;
    }
    else {
        int n = atoi(argv[1]);
        assert(n > 0);
        Matrice* terrain = creer_matrice(n);

        if (argc == 3) {
            random_randomseed();
            generation_DC(terrain, 1);
        } else if (argc == 5) {
            int seed = atoi(argv[4]);
            random_setseed(seed);
            double h = atof(argv[3]);
            generation_DC(terrain, h);        
        } else {
            fprintf(stderr, "generation_carte : nombre incorrect de parametres (%d)\n", argc-1);
            detruit_matrice(terrain);
            return 22;
        }
        
        Image* heightmap = matrice_to_image(terrain);
        detruit_matrice(terrain);
        bool successful_export = exporterImage(heightmap, argv[2]);

        if (!successful_export) {
            fprintf(stderr, "generation_carte : ecriture du fichier %s impossible\n", argv[2]);
            detruireImage(heightmap);
            return 9;
        } else {
            detruireImage(heightmap);
            return 0;
        }
            
    }
}