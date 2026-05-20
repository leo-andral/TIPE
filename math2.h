#ifndef _MATH2_H_
#define _MATH2_H_

// Fonctions de smoothing
float smoothstep(float x);
float smootherstep(float x);

// Précision pour les fonctions randoms
extern const int globalPrecision;

// Fonctions d'aléatoire
double random_double(int precision);
double random_double_global();
int random_pos_neg();
void random_setseed(int seed);
void random_randomseed();

#endif