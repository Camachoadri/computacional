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
#define npasos 1000
#define m 1000

int main(void){

    //Comencemos con el algoritmo declarando las varibles necesarias, tanto contadores como posiciones de la nave y la luna

    float lunap[2], cohete[2], p_r, p_phi, h=1., k[4][4];
    int i,j;

    //Ahora inicializamos los parametro

    lunap[0]=dtl;
    lunap[1]=0.;
    cohete[0]=R_t;
    cohete[1]=0;
    p_r=0;
    p_phi=0;

    //A continuacion emepzamos el ciclo

    for ( i = 0; i < npasos; i++)
    {
        //Evaluamos los k donde el primer indice indica el superindice de k y el segundo indica de que coordenada

        k[0][0]=h*p_r/m;
        k[1][0]=h*(p_r+k[0][0]/2);
        k[2][0]=h*(p_r+k[1][0]/2);
        k[3][0]=h*(p_r+k[2][0]);

        k[0][1]=h*p_phi/(cohete[0]*cohete[0]);
        k[1][1]=h*(p_phi+k[0][1]/2)/(((cohete[0]+k[0][1]/2)*(cohete[0]+k[0][1]/2)));
        k[2][1]=h*(p_phi+k[1][1]/2)/(((cohete[0]+k[1][1]/2)*(cohete[0]+k[1][1]/2)));
        k[3][1]=h*(p_phi+k[2][1]/2)/(((cohete[0]+k[2][1])*(cohete[0]+k[2][1])));

        
    }
    




    return 0;
}