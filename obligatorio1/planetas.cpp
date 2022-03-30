#include <iostream>
#include<cmath>
#include<fstream>


using namespace std;

void cambr(float r[], int N);
float cambt(float t);
void cambm(float m[], int N);
void aceleracion(float ax[], float ay[], float x[], float y[], float  m[], int N);
void cambv(float v[], int N);
float cenergia(float vx[], float vy[], float x[], float y[], float m[], int N);


//Vamos a crear las funciones que nos seran utiles luego



int main (void){

    // Vamos a declarar las variables que usaremos
    int N, i;

    //Damos valor a cuantos planetas vamos a tener inicialmente

    N=9;

    float h, t, t_f,  x[N], y[N], vx[N], vy[N],  ax[N], ay[N],  wx[N], wy[N], m[N], E;
    ofstream fich, energia;

    //Damos valores al resto de variables e inciamos las necesarias
 
    x[0]=0;
    x[1]=57910000000;
    x[2]=108200000000;
    x[3]=146600000000;
    x[4]=227940000000;
    x[5]=778330000000;
    x[6]=1429400000000;
    x[7]=2870990000000;
    x[8]=4504300000000;

    // Inicializamos la y a 0 con un bucle

    for ( i = 0; i < N; i++)
    {
        y[i]=0;
    }

    // Ahora inicializamos los valores de las velocidades

    vy[0]=0;
    vy[1]=48000.92;
    vy[2]=35000.02;
    vy[3]=29000.78;
    vy[4]=24000.07;
    vy[5]=13000.05;
    vy[6]=9000.64;
    vy[7]=6000.81;
    vy[8]=5000.43;

    for ( i = 0; i < N; i++)
    {
        vx[i]=0;
    }
    

    // Por ultimo metemos las masas

    m[0]=1.98*pow(10,30);
    m[1]=3.28*pow(10,23);
    m[2]=4.83*pow(10,24);
    m[3]=5.98*pow(10,24);
    m[4]= 6.4*pow(10,23);
    m[5]= 1.9*pow(10,27);
    m[6]=5.98*pow(10,26);
    m[7]= 8.67*pow(10,25);
    m[8]=1.05*pow(10,26);



    



    // Tiempo para el que queremos que acabe
    h=0.1;
    t_f=1000;
    //Ahora nombraremos las constantes del problema

    cambm(m , N);
    cambr(x , N);
    cambv(vy, N);
    cambt(t);
    cambt(t_f);

    //Vamos a calcular la aceleración inicial

    aceleracion(ax, ay, x, y, m, N);

    //Comenzamos el buble y abrimos el fichero de volcado

    fich.open("planets_data.dat");
    energia.open("energias.dat");


    for (t=0; t <= t_f ; t=t+h)
    {

        //Vamos a volcar las energias en un fichero con el tiempo
        E= cenergia(vx, vy, x, y, m, N);
        energia << t <<  "  " << E << endl;


        for ( i = 0; i < N; i++)
        {
            //Escribimos en el archivo la posicion

            fich << x[i] << ", " << y[i] << endl;

            //Calculamos la posicion del tiempo t+h
            x[i]=x[i]+ h*vx[i] + h*h*ax[i]/2.;
            y[i]=y[i]+ h*vy[i] + h*h*ay[i]/2.;

            
            wx[i]= vx[i] + h*ax[i]/2.;
            wy[i]= vy[i] + h*ay[i]/2.;
        }

        // Realizamos un salto de linea mas.

        fich << endl;

        //Ahora sacamos las nuevas aceleraciones

        aceleracion(ax, ay, x, y, m, N);

        //Recalculamos la nueva velocidad en t+h

        for ( i = 0; i < N; i++)
        {
            vx[i]= wx[i] +h*ax[i]/2.;
            vy[i]= wy[i] +h*ay[i]/2.;
        }
        
        
    }
    
    fich.close();
    energia.close();

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

    t1=sqrt(G*M_s/pow(c,3));
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

void aceleracion(float ax[], float ay[], float x[], float y[], float  m[], int N){

    int i,j;
    float r[N];
    

    for ( i = 0; i < N; i++)
    {
        ax[i]=0;
        ay[i]=0;
    }
    


    for (i = 1; i < N; i++)
    {
        for (j = 0; j < i; j++)
        {
            ax[i]=(ax[i]-m[j]*(x[i]-x[j])/pow(abs(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))),3));
            ay[i]=(ay[i]-m[j]*(y[i]-y[j])/pow(abs(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))),3));
        }
        
        
        for (j = i+1; j < N; j++)
        {
            ax[i]=(ax[i]-m[j]*(x[i]-x[j])/pow(abs(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))),3));
            ay[i]=(ay[i]-m[j]*(y[i]-y[j])/pow(abs(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))),3));
        }
        
        
    }
    


}


void cambv(float vy[], int N){

    float G, M_s, c;
    int i;
    G= 6.67*pow(10,-11);
    M_s= 1.99*pow(10,30);
    c= 1.496*pow(10,11);

    for ( i = 0; i < N; i++)
    {
        vy[i]=vy[i]*pow(c/(G*M_s),1/2.);
    }
    return;

}

float cenergia(float vx[], float vy[], float x[],float m[],  float y[], int N){

    int i;
    float E=0, G, c= 1.496*pow(10,11);
    G= 6.67*pow(10,-11);


    //Calculamos las velocidades y distancias en modulo


    //Le vamos a dar las velocidades y las posiciones de los planetas y calculará la energia total como al suma de las energias de todos

    for ( i = 1; i < N; i++)
    {
        E=E+0.5*m[i]*(vx[i]*vx[i]+vy[i]*vy[i])-G*G*m[i]*m[0]/(sqrt(x[i]*x[i]+y[i]*y[i])*c*c*c);
    }


    return E;

}