#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>


using namespace std;

#define N 64

float magnetizacion (float s[][N]);
float energia (float s[][N]);

int main (void){

    float T;
    int i, j,k,n,m,aux,pmonte;
    float s[N][N],p, DE, xi, mn,en,cn;
    ofstream fich;

    //Inicializamso las variables necesarias

    T=0.05;


    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            s[i][j]=1;
        }
        
    }


 //Si queremos que sean aleatorias   

/*
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            if((rand()%(11))<5){
                s[i][j]=-1.;
            }
            else{
                s[i][j]=1.;    
            }           
        }
        
    }
    
*/
  
    fich.open("ising_data.dat");



    for ( i = 0; i < 200*N*N; i++)
    {
        //Escogemos dos numeros al azar de los posibles que tenemos

        n=rand()%(N);
        m=rand()%(N);

        //Escribamos la matriz en el fichero

        aux= (i%(N*N));
        pmonte=0;

        if ((i%(N*N))==0)
        {
                for ( k = 0; k < N; k++)
            {
                for (j = 0; j < N-1; j++)
                {
                    fich << s[k][j] << ", ";
                }   

                fich << s[k][N-1] << endl;

            }
                fich << endl;
            pmonte++;
        }
        
        

        //Procedemso a calcular deltaE según todos los posibles casos, basandonos en las condiciones periodicas para no salirnos de la matriz

        if (n+1>N)
        {
            if (m+1>N)
            {
                DE=2*s[n][m]*(s[1][m]+s[n-1][m]+s[n][1]+s[n][m-1]);
            }
            else if (m==0)
            {
                DE=2*s[n][m]*(s[1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else{

                DE=2*s[n][m]*(s[1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
            }
        }
        else if (n==0)
        {
            if (m+1>N)
            {
                DE=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][1]+s[n][m-1]);
            }
            else if (m==0)
            {
                DE=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else{

                DE=2*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
            }

        }
        else{

            if (m+1>N)
            {
                DE=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][1]+s[n][m-1]);
            }
            else if (m==0)
            {
                DE=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else{

                DE=2*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
            }

            

        }
        

        p = min(float(1),exp(-DE/T));

        //Calculamos un numero aleatorio nuevo, esta vez dividimos entre el maximo para que esté entre 0 y 1

        xi = (rand()%(N-1))/N;

        //Si xi es menor que p, cambiamos el signo de nuestro elemento

        if (xi<p)
        {
            s[n][m]= -s[n][m];
        }
        

    }
    
    fich.close();

    mn=0;
    en=0;
    cn=0;

    //Para el voluntario vamos a hacer la media

    if ((pmonte%100)==0)
    {
        mn= mn + magnetizacion(s);
    }
    
    mn= mn/(pmonte/100);


    return 0;

}


float magnetizacion (float s[][N]){


    float m;
    int i,j;
    m=0;

    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            m=m+s[i][j];
        }
        
    }
    
    m=m/(N*N);

    return m;
}

float energia (float s[][N]){

    float E=0;
    int i,j;

    //Hacemos la suma teniendo en cuanta qu eno queremos que desborde la matriz

    for ( i = 1; i < N-1; i++)
    {
        for ( j = 1; j < N-1; j++)
        {
            E=s[i][j]*(s[i][j+1]);
        }
        
    }
    





    return E;
}

