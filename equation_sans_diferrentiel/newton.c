#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi 3,141592653589
#define ro1 1.2
#define ro2 1000
#define xi1  1
#define xi2 1
#define g 9.81


float H(float x){
    return(2.2);
}

float f(float x){
    return(0.5*(1/g)*(xi1-xi2)/(ro1-ro2)*H(x)*H(x));
}
float derive(float h, float x){// h est la pas (il doit être petit devant 1)
    float fp;
    fp=(f(x)-f(x-h))/h;
    return fp;
}

float newton(float x0,float eps, float h){
    float x1;
    x1=x0-f(x0)/derive(h,x0);
    while (fabs(x1-x0)>eps){
        x0=x1;
        x1=x0-f(x0)/derive(h,x0);
    }
    return(x1);
}

float* eta(int deb, int fin,float h, float pas, float eps){ // h "pas" de la methode de newton, pas est le pas de x
    int taille= (fin-deb)/pas;
    float x0=deb;
    float* hauteur=(float*)malloc(taille*sizeof(float));
    for (int i=0;i<taille;i++){
        hauteur[i]=newton(x0,eps,h);
        x0=x0+pas;
    }
    return(hauteur);
}

void affiche_tab(float* tab, int n){
    for(int i=0;i<n;i++){
        printf("%f",tab[i]);
    }
}

void export_txt(int n, float* value, float* hauteur){
    FILE* fichier;
    fichier=fopen("eta.txt","w");
    for (int i=0;i<n;i++)
        fprintf(fichier,"%f %f\n",value[i],hauteur[i]);

    fclose(fichier);
}

float* x_value(int deb, int fin, float pas){
    int a=(fin-deb)/pas;
    float* value=(float*)malloc(sizeof(float));
    for (int i=0;i<a;i++){
        value[i]=deb;
        deb=deb+pas;
    }
    return value;
}

int main(){
    //float zero;
    float* hauteur;
    float* value;
    float pas=0.001;
    int deb=0;
    int fin=10;
    float eps=0.01;
    float h=0.001;
    //zero=newton(2,0.001,0.0001);
    //printf("%f",zero);
    hauteur=eta(deb,fin,h,pas,eps);
    value=x_value(deb,fin,pas);
    affiche_tab(hauteur,(fin-deb)/pas);
    export_txt((fin-deb)/pas,value,hauteur);
    return 0;
}