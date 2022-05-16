#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>
#include <complex>



using namespace std;
#define G 6.67*pow(10,-11)
#define M_t 5.9736*pow(10,24)
#define M_l 0.07349*pow(10,24)
#define dtl 3.844*pow(10,8)
#define w 2.6617*pow(10,-6)
#define R_t 6.378*pow(10,6)
#define R_l 1.7374*pow(10,6)
#define npasos 250000
#define m 10000
#define theta 0.26

//Vamos a hacer una funcion para la p_phi

float ppunto_r(float coheter, float cohetephi, float p_phi, float t);
float ppunto_phi(float coheter, float cohetephi, float t);


int main(void){

    //Comencemos con el algoritmo declarando las varibles necesarias, tanto contadores como posiciones de la nave y la luna

    float lunar, lunaphi, coheter, cohetephi, p_r, p_phi, h=0.8, k[4][4],v;
    int i,j;
    ofstream fich;

    //Ahora inicializamos los parametro

    lunar=dtl;
    lunaphi=0.;
    coheter=R_t;
    cohetephi=0.;
    v=11194.444;

    //Vamos a reescalar

    lunar=lunar/(1.*dtl);
    coheter=R_t/(1.*dtl);
    v=v/(1.*dtl);
    p_r=v*cos(theta);
    p_phi=v*coheter*sin(theta);  

    //A continuacion emepzamos el ciclo y abrimos el fichero

    fich.open("planets_data.dat");

    for ( i = 0; i < npasos; i++)
    {
        //Lo primero es escribir en el documento las posiciones    

        if((i%500)==0){

        fich << coheter*cos(cohetephi) << ", " << coheter*sin(cohetephi) << endl << lunar*cos(w*i*h*1.) << ", " << lunar*sin(w*i*h*1.) << endl << endl;


        }    


        //Evaluamos los k donde el primer indice indica el superindice de k y el segundo indica de que coordenada
        //El primero es r el segundo es phi el tercero p_r y el cuarto p_phi

        k[0][0]=h*p_r;
        k[0][1]=h*p_phi/(coheter*coheter);
        k[0][2]=h*ppunto_r(coheter, cohetephi, p_phi, i*h);
        k[0][3]=h*ppunto_phi(coheter, cohetephi, i*h);

        k[1][0]=h*(p_r+k[0][2]/2);
        k[1][1]=h*(p_phi+k[0][3]/2)/(((coheter+k[0][0]/2)*(coheter+k[0][0]/2)));
        k[1][2]=h*ppunto_r(coheter+ k[0][2]/2, cohetephi + k[0][1]/2, p_phi+ k[0][3]/2 , i*h);
        k[1][3]=h*ppunto_phi(coheter+ k[0][0]/2, cohetephi+k[0][1]/2, i*h);

        k[2][0]=h*(p_r+k[1][2]/2);
        k[2][1]=h*(p_phi+k[1][3]/2)/(((coheter+k[1][0]/2)*(coheter+k[1][0]/2)));
        k[2][2]=h*ppunto_r(coheter+ k[1][2]/2, cohetephi + k[1][1]/2, p_phi+ k[1][3]/2 , i*h);
        k[2][3]=h*ppunto_phi(coheter+ k[1][0]/2, cohetephi+k[1][1]/2, i*h);

        k[3][0]=h*(p_r+k[2][2]); 
        k[3][1]=h*(p_phi+k[2][3])/(((coheter+k[2][0])*(coheter+k[2][0])));
        k[3][2]=h*ppunto_r(coheter+ k[2][2], cohetephi + k[2][1], p_phi+ k[2][3] , i*h);
        k[3][3]=h*ppunto_phi(coheter+ k[2][0], cohetephi+k[2][1], i*h);

        //Ahora calcularemos los valores de y

        p_phi= p_phi + (k[0][3]+2*k[1][3]+2*k[2][3]+k[3][3])/6;
        coheter=coheter + (k[0][0]+2*k[1][0]+2*k[2][0]+k[3][0])/6;
        cohetephi= cohetephi + (k[0][1]+2*k[1][1]+2*k[2][1]+k[3][1])/6;
        p_r= p_r + (k[0][2]+2*k[1][2]+2*k[2][2]+k[3][2])/6;


    }
    

    fich.close();


    return 0;
}

float ppunto_r(float coheter, float cohetephi, float p_phi, float t){

    float ppunto_r,DELTA, mu,rprima;

    DELTA=G*M_t/(1.*dtl*dtl*dtl);
    mu=M_l/(1.*M_t);
    rprima=sqrt(1+coheter*coheter-2*coheter*cos(cohetephi-1.*w*t));

    ppunto_r=p_phi*p_phi/(coheter*coheter*coheter)-DELTA*(1/(coheter*coheter)+mu/(rprima*rprima*rprima)*(coheter-cos(cohetephi-1.*w*t)));



    return ppunto_r;
}

float ppunto_phi(float coheter, float cohetephi, float t){


    float ppunto_phi,DELTA, mu,rprima;

    DELTA=G*M_t/(1.*dtl*dtl*dtl);
    mu=M_l/(1.*M_t);
    rprima=sqrt(1+coheter*coheter-2*coheter*cos(cohetephi-1.*w*t));

    ppunto_phi=-DELTA*mu*coheter*sin(cohetephi-1.*w*t)/(rprima*rprima*rprima);



    return ppunto_phi;
}
