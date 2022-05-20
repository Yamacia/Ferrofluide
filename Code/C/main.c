#include "code.h"

int main(){
    //float x=0.1;
    //float z = 0.01;
    /*
    float champ3 = courant_inverse(i,x,z,POSITION_FIL1,POSITION_FIL2);
    float champ2 = nappe_courant_y(i,LONGUEUR,LONGUEUR);
    float champ4 = dipole_magnetique(i,x,0,z,0.005);
    float hauteur1 = eta(x,champ1);
    float hauteur2 = eta(x,champ2);
    float hauteur3 = eta(x,champ3);
    float hauteur4 = eta(x,champ4);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ1,hauteur1);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ2,hauteur2);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ3,hauteur3);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ4,hauteur4);
    */
    printf("\n");
    printf("Preuve que c'est la version C\n");
    iteration_sur_x(0,LONGUEUR,0,20);
    //affiche_fonction(0,LONGUEUR,0.01);
    return 0;
}