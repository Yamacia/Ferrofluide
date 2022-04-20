#include "code.h"

float abso(float a, float b){
    if(a-b>0)
        return a-b;
    return b-a;
}

float nappe_courant_y(float longueur, float largeur){
    float surface = longueur*largeur;
    float j = INTENSITY/surface;
    return j/2;
}

float courant_inverse(float x, float z){
    float r1 = sqrt(pow(x-POSITION_FIL1_X,2)+pow(z-POSITION_FIL1_Z,2));
    float H1 = -INTENSITY/(2*PI*r1);
    if(abso(H1,0) > 500)
        H1 = -INTENSITY/(2*PI*RAYON);

    float r2 = sqrt(pow(x-POSITION_FIL2_X,2)+pow(z-POSITION_FIL2_Z,2));
    float H2 = INTENSITY/(2*PI*r2);
    if(abso(H2,0) > 500)
        H2 = INTENSITY/(2*PI*RAYON);
    float champ = H1 + H2;   
    //printf("Champ est : %.6f\n",champ);
    return champ; 
}

float dipole_magnetique(float x, float y, float z, float diam){
    float S = 2*PI*pow(diam,2);
    float m = INTENSITY*S;
    float r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    float Hx = (m/4*PI)*((3*z*x)/pow(r,5));
    float Hy = (m/4*PI)*((3*z*y)/pow(r,5));
    float Hz = (m/4*PI)*(1/pow(r,3))*(((3*pow(z,2))/pow(r,2))-1);
    float H = sqrt(pow(Hx,2)+pow(Hy,2)+pow(Hz,2));
    printf("Hx = %.6f, Hy = %.6f, Hz = %.6f, H = %.6f\n",Hx,Hy,Hz,H);
    return H;
}

/*
float eta(float x,float champ){
    return ((CHI1-CHI2)/(2*G*(RHO1-RHO2)))*pow(champ,2);
}

*/

float fonction(float x,float eta,float champ){
    //printf("Champ : %f\n",champ);
    return (RHO1-RHO2)*G*eta + 0.5*(CHI1-CHI2)*pow(champ,2);
}

float dichotomie(float deb, float fin,float x0,float z){
    float n0 = deb;
    float n1 = fin;
    float n= (n0+n1)/2;
    int iteration = 1;
    float champ = courant_inverse(x0,z);
    //float champ = nappe_courant_y(INTENSITY,LONGUEUR,LONGUEUR);
    printf("Champ est %f\n",champ);
    while(abso(fonction(x0,n,champ),0)>EPSILLON){
        //printf("Valeur de n : %.9f\n",n);
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

void iteration_sur_x(float deb, float fin, float x, int nbr){
    float pas = (fin - deb)/nbr;
    float tab_x[nbr];
    for(int i = 0; i < nbr; i++){
        tab_x[i]=deb + i*pas;
    }
    float eta1[nbr];
    float eta2[nbr];
    for(int i = 0; i < nbr; i++){
        printf("Iteration %d en x = %f\n",i,tab_x[i]);
        eta1[i] = dichotomie(deb,fin,tab_x[i],1);
        printf("Valeur obtenue est : %.15f\n\n",eta1[i]);
        eta2[i] = newton(1,tab_x[i]);
        //printf("Valeur obtenue est : %.15f\n\n",eta2[i]);
    }
    affiche_tab(eta1,nbr);
    export_txt(nbr,tab_x,eta2,"eta.txt");
    export_txt(nbr,tab_x,eta1,"eta1.txt");
}

float newton(float z0, float x){
    float zn = z0;
    int n = 0;
    float champ = courant_inverse(x,zn);
    float func = fonction(x,zn,champ);
    while ((abso(func,0)> EPSILLON)&&(n < NMAX)){
        champ = courant_inverse(x,zn);
        float fprime = (fonction(x,zn+ACCROISSEMENT,champ)-fonction(x,zn,champ))/ACCROISSEMENT;
        //printf("Champ : %f\n", champ);
        func = fonction(x,zn,champ);
        zn = zn - func/fprime;
        n++;
    }
    printf("Fonction = %f et N = %d, champ = %f\n",func,n,champ);
    return zn;
}

void affiche_tab(float tab[],int nbr){
    for (int i = 0; i < nbr; i++){
        printf("%f  ",tab[i]);
    }
}

void export_txt(int n, float* value, float* hauteur,const char* file){
    FILE* fichier;
    fichier=fopen(file,"w");
    for (int i=0;i<n;i++)
        fprintf(fichier,"%f %f\n",value[i],hauteur[i]);

    fclose(fichier);
}
