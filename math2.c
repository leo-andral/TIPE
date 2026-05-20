#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "math2.h"

float smoothstep(float x) {
    if (x <= 0) return 0.0;
    if (1 <= x) return 1.0;
    return x*x * (3.0 - 2.0 * x);
}

float smootherstep(float x) {
    if (x <= 0) return 0.0;
    if (1 <= x) return 1.0;
    return x * x * x * (x * (6.0 * x - 15.0) + 10.0);
}

const int globalPrecision = 6; // i.e. nombre de chiffre apres la vigule du flaot/double

/*
    Renvoie un double entre 0 et 1 (inclus) de précision `precision` 
    i.e. un double entre 0 et 1 avec `precision` chiffres après la virgule
*/
double random_double(int precision) {
    int ordre_grandeur = pow(10, precision);
    int random = rand() % (ordre_grandeur+1);
    // printf("OdG = %d, Rdm = %d, RdmD = %f\n", ordre_grandeur, random, (double)random/ordre_grandeur); // DEBUG
    return (double)random / ordre_grandeur;
}

// Renvoie un double entre 0 et 1 (inclus) de précision `globalPrecision`
double random_double_global() {
    return random_double(globalPrecision);
}

// Renvoie aléatoirement 1 ou -1
int random_pos_neg() {
    int random = rand()%2;
    if (random == 1) return 1;
    else return -1;
}

// Controle la seed d'aléatoire
void random_setseed(int seed) {
    srand(seed);
}

// Met une seed aléatoire (basé sur le temps)
void random_randomseed() {
    random_setseed(time(NULL));
}