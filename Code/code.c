#include "code.h"

float abso(float a, float b){
    if(a-b>0)
        return a-b;
    return b-a;
}

float nappe_courant_y(float i, float longueur, float largeur){
    float surface = longueur*largeur;
    float j = i/surface;
    return j/2;
}

float courant_inverse(float x, float z){
    float r1 = sqrt(pow(x-POSITION_FIL1_X,2)+pow(z-POSITION_FIL1_Z,2));
    float H1 = INTENSITY/(4*PI*r1);

    float r2 = sqrt(pow(x-POSITION_FIL2_X,2)+pow(z-POSITION_FIL2_Z,2));
    float H2 = INTENSITY/(4*PI*r2);

    float champ = H1 + H2;   
    //printf("Champ est : %.6f\n",champ);
    return champ; 
}

float dipole_magnetique(float i, float x, float y, float z, float diam){
    float S = 2*PI*pow(diam,2);
    float m = i*S;
    float r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    float Hx = (m/4*PI)*((3*z*x)/pow(r,5));
    float Hy = (m/4*PI)*((3*z*y)/pow(r,5));
    float Hz = (m/4*PI)*(1/pow(r,3))*(((3*pow(z,2))/pow(r,2))-1);
    float H = sqrt(pow(Hx,2)+pow(Hy,2)+pow(Hz,2));
    printf("Hx = %.6f, Hy = %.6f, Hz = %.6f, H = %.6f\n",Hx,Hy,Hz,H);
    return H;
}

float eta(float x,float cham){
    return ((CHI1-CHI2)/(2*G*(RHO1-RHO2)))*cham*cham;
}

float fonction(float x,float eta,float champ){
    //printf("Champ : %f\n",champ);
    return (RHO1-RHO2)*G*eta + 0.5*(CHI1-CHI2)*pow(champ,2);
}

float dichotomie(float deb, float fin,float x0,float z){
    float n0 = deb;
    float n1 = fin;
    float temp = 0;
    float n= (n0+n1)/2;
    int iteration = 0;
    float champ = courant_inverse(x0,z);
    //float champ = nappe_courant_y(INTENSITY,LONGUEUR,LONGUEUR);
    printf("Champ est %f\n",champ);
    while(abso(n,temp)>pow(10,-9)){
        //printf("Valeur de n : %.9f\n",n);
        temp = n;
        //printf("Fonction vaut : %f\n",fonction(x0,n,champ));
        if(fonction(x0,n,champ)>0){
            n1 = n;
        }
        else{
            n0 = n;
        }
        n = (n0 + n1)/2;
        iteration++;
        //printf("Les valeurs absolues sont : %.9f\n",abso(n,temp));
    }
    printf("Nombre d'iterations : %d\n",iteration);
    return n;
}

float picard(float n){
    float x = n;
    float temp = 0;
    while(abso(temp,x)>pow(10,-5)){
        temp = x;
        //x = fonction(x,n);
        //printf("Les valeurs absolues sont : %.9f\n",abso(n,temp));
    }
    return temp;
}

void iteration_sur_x(float deb, float fin, float x){
    for(float i = deb; i<fin; i=i+PAS){
        float eta = dichotomie(deb,fin,x,i);
        printf("Valeur obtenue est : %.15f\n\n",eta);
    }
}

void affiche_fonction(float deb,float fin, float x){
    for(float i=deb;i<fin+PAS;i=i+PAS){
        //float champ = courant_inverse(x,i);
        float champ = nappe_courant_y(INTENSITY,LONGUEUR,LONGUEUR);
        printf("Fonction = %f en z = %f\n",fonction(x,i,champ),i);
    }
}