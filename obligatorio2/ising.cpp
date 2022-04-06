#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>


using namespace std;

int main (void){

    float T;
    int N=64, i, j,k,n,m,aux;
    float s[N][N],p, DE, xi;
    ofstream fich;

    //Inicializamso las variables necesarias

    T=0.0000001;
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            s[i][j]=1;
        }
        
    }


/* Si queremos que sean aleatorias   

    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            if(rand()%(11)<5){
                s[i][j]=-1;
            }
            else if(rand()%(11)>5){
                s[i][j]=1;    
            }           
        }
        
    }
    
  
*/  
    fich.open("ising_data.dat");



    for ( i = 0; i < 100*N*N; i++)
    {
        //Escogemos dos numeros al azar de los posibles que tenemos

        n=rand()%(N);
        m=rand()%(N);

        //Escribamos la matriz en el fichero

        aux= (i%(N*N));

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

    return 0;

}
