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

float courant_inverse1(float i, float x, float z, float f1, float f2){
    float d1 = x - f1;
    float R1 = sqrt(pow(z,2)+pow(d1,2));
    float theta1 = atan(d1/z);
    float Hx1 = i/(2*PI*R1*sin(theta1));
    float Hy1 = i/(2*PI*R1*cos(theta1));

    float d2 = x - f2;
    float R2 = sqrt(pow(z,2)+pow(d2,2));
    float theta2 = atan(d2/z);
    float Hx2 = i/(2*PI*R2*sin(theta2));
    float Hy2 = i/(2*PI*R2*cos(theta2));
    
    float Hx = Hx1 + Hx2;
    float Hy = Hy1 + Hy2;
    float champ = sqrt(pow(Hx,2)+pow(Hy,2));
    return champ; 
}

float courant_inverse2(float i, float x, float z, float f1, float f2, float r){
    float x1 = x - f1;
    float d1 = sqrt(pow(x1,2)+pow(z,2));
    float p1 = sqrt((pow(d1,2)/4 - pow(r,2)));
    float Hx1 = (-1/PI)*p1*i*(2*x*z)/(pow(x*x-z*z-p1*p1,2)+4*pow(x,2)*pow(z,2));
    float Hz1 = (-1/PI)*p1*i*(pow(x,2)-pow(z,2)-pow(p1,2))/(pow(x*x-z*z-p1*p1,2)+4*pow(x,2)*pow(z,2));

    float x2 = x - f2;
    float d2 = sqrt(pow(x2,2)+pow(z,2));
    float p2 = sqrt((pow(d2,2)/4 - pow(r,2)));
    float Hx2 = (-1/PI)*p2*i*(2*x*z)/(pow(x*x-z*z-p2*p2,2)+4*pow(x,2)*pow(z,2));
    float Hz2 = (-1/PI)*p2*i*(pow(x,2)-pow(z,2)-pow(p2,2))/(pow(x*x-z*z-p2*p2,2)+4*pow(x,2)*pow(z,2));
    
    float Hx = Hx1 + Hx2;
    float Hz = Hz1 + Hz2;
    float H = sqrt(pow(Hx,2)+pow(Hz,2));
    return H;
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

float fonction(float x){
    return 2*sin(x);
}

float dichotomie(float n0, float n1){
    float temp = 0;
    float n= (n0 + n1)/2;
    while(abso(n,temp)>pow(10,-5)){
        //printf("Valeur de n : %.9f\n",n);
        temp = n;
        if(fonction(n)<0){
            n0 = n;
        }
        else{
            n1 = n;
        }
        n = (n0 + n1)/2;
        //printf("Les valeurs absolues sont : %.9f\n",abso(n,temp));
    }
    return n;
}


float picard(float n){
    float x = n;
    float temp = 0;
    while(abso(temp,x)>pow(10,-5)){
        temp = x;
        x = fonction(x);
        //printf("Les valeurs absolues sont : %.9f\n",abso(n,temp));
    }
    return temp;
}

int main(){
    float x=0.1;
    float z = 0.01;
    float i = INTENSITY;
    float champ1 = courant_inverse2(i,x,z,0.05,0.15,0.001);
    float champ3 = courant_inverse1(i,x,z,0.05,0.15);
    float champ2 = nappe_courant_y(i,0.20,0.20);
    float champ4 = dipole_magnetique(i,x,0,z,0.005);
    float hauteur1 = eta(x,champ1);
    float hauteur2 = eta(x,champ2);
    float hauteur3 = eta(x,champ3);
    float hauteur4 = eta(x,champ4);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ1,hauteur1);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ2,hauteur2);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ3,hauteur3);
    printf("Champ en x = %.2f est %.6f, Hauteur est : %.6f\n",x,champ4,hauteur4);
    return 0;
}