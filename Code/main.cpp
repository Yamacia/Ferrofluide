#include "code.hpp"
using namespace std;


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
    */
    cout <<"\n";
    cout <<"Preuve que c'est la version C++\n";
    iteration_sur_x(0,LONGUEUR,0,20);
    //affiche_fonction(0,LONGUEUR,0.01);
    return 0;
}