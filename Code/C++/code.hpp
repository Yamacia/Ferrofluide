#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <iostream> // Retirer pour convertir en C
#include <iomanip>

#define CHI1 3000e-6 // Suspecitibilité Magnétique Ferrite
// #define CHI2 -8.6e-6 // Suspectibilité Magnétique Eau
#define CHI2 0.38e-6
#define RHO1 2900 // Masse Volumique Ferrite
// #define RHO2 997 // Masse Volumique Eau
#define RHO2 1292
#define G 9.81
#define PI 3.1415926535
#define INTENSITY 10

#define POSITION_FIL1_X 0.05
#define POSITION_FIL2_X 0.15
#define POSITION_FIL1_Z 0
#define POSITION_FIL2_Z 0
#define RAYON 0.005
#define LONGUEUR 0.20
#define PAS 0.01
#define EPSILLON 1e-6
#define ACCROISSEMENT 0.001
#define NMAX 100

float abso(float a, float b);

float nappe_courant_y(float longueur, float largeur);

float courant_inverse(float x, float z);

float dipole_magnetique(float x, float y, float z, float diam);

float eta(float x,float cham);

float fonction(float x,float eta,float champ);

float dichotomie(float deb, float fin,float x0,float z);

float picard(float n);

void iteration_sur_x(float deb, float fin, float x,int nbr);

float newton(float z0, float x);

void affiche_tab(float tab[],int nbr);

void export_txt(int n, float* value, float* hauteur,const char* file);
