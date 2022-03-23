#include <iostream>
#include<cmath>

using namespace std;

void cambr(float r[], int N);
float cambt(float t);
void cambm(float m[], int N);
void aceleracion(float a[], float r[],float m[], int N);


//Vamos a crear las funciones que nos seran utiles luego



int main (void){

    // Vamos a declarar las variables que usaremos
    int N;

    //Damos valor a cuantos planetas vamos a tener inicialmente

    N=9;

    float h, t, t_f,  r[N], v[N], a[N], w[N], m[N];

    //Damos valores al resto de variables e inciamos las necesarias
    h=0.1;
    r[0]=0;
    r[1]=57910000;
    r[2]=108200000;
    r[3]=146600000;
    r[4]=227940000;
    r[5]=778330000;
    r[6]=1429400000;
    r[7]=2870990000;
    r[8]=4504300000;



    // Tiempo para el que queremos que acabe
    t_f=4;
    //Ahora nombraremos las constantes del problema

    cambm(m, N);
    cambr(r, N);
    cambt(t);
    cambt(t_f);

    //Comenzamos el buble

    for (t=0; t <= t_f ; t=t+h)
    {
        
    }
    
    

    return 0;
}

void cambr(float r[], int N){

    float c;
    int i;

    c= 1.496*pow(10,11);

    for ( i = 0; i < N; i++)
    {
        r[i]=r[i]/c;
    }

}

float cambt(float t){

    float G, M_s, c,t1;

    G= 6.67*pow(10,-11);
    M_s= 1.99*pow(10,30);
    c= 1.496*pow(10,11);

    t1=pow(G*M_s/pow(c,3),1/2);
        return t1;

}


void cambm(float m[], int N){

    float M_s;
    int i;
    M_s= 1.99*pow(10,30);

    for ( i = 0; i < N; i++)
    {
        m[i]=m[i]/M_s;
    }
    return;
}

void aceleracion(float a[], float r[],float  m[], int N){

    int i,j;

    for ( i = 0; i < N; i++)
    {
        a[i]=0;
    }
    

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < i; j++)
        {
            a[i]=a[i]-m[j]*(r[i]-r[j])/pow(abs(r[i]-r[j]),3);
        }
        
        
        for (j = i+1; j < N; j++)
        {
            a[i]=a[i]-m[j]*(r[i]-r[j])/pow(abs(r[i]-r[j]),3);
        }
        
        
    }
    


}


