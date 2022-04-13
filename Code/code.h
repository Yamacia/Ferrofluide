#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CHI1 0.003
#define CHI2 0.00000038
#define RHO1 2900
#define RHO2 1292
#define G 9.81
#define PI 3.1415926535
#define INTENSITY 0.01

#define POSITION_FIL1_X 0.05
#define POSITION_FIL2_X 0.15
#define POSITION_FIL1_Z 0
#define POSITION_FIL2_Z 0
#define RAYON_FIL 0.001
#define LONGUEUR 0.20
#define PAS 0.01

float abso(float a, float b);

float nappe_courant_y(float i, float longueur, float largeur);

float courant_inverse(float x, float z);

float dipole_magnetique(float i, float x, float y, float z, float diam);

float eta(float x,float cham);

float fonction(float x,float eta,float champ);

float dichotomie(float deb, float fin,float x0,float z);

float picard(float n);

void iteration_sur_x(float deb, float fin, float x);

void affiche_fonction(float deb,float fin, float x);