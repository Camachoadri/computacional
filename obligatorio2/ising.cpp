#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>


using namespace std;

#define N 32
//Definimos el aprametro para la funcion de correlacion
#define Corr 7

float magnetizacion (float s[][N]);
float energia (float s[][N]);

int main (void){

    float T;
    int i, j,k,n,m,aux,pmonte,l;
    float p, DE, xi, mn,en,cn, ex,s[N][N], ma,prom_e,prom_ecuad,auxe,fi, prom_s[N][N];
    ofstream fich;

    //Inicializamso las variables necesarias

    T=2.5;


    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            s[i][j]=-1;
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
  
 //   fich.open("ising_data.dat");

//Iniciamos el contador de monte carlos y del voluntario
    pmonte=0;

    mn=0;
    en=0;
    cn=0;
    fi=0;
    prom_e=0;
    prom_ecuad=0;

    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            prom_s[i][j]=0;
        }
        
    }
    


//Comenzamos el algoritmo en si

    for ( i = 0; i < pow(10,3)*N*N; i++)
    {
        //Escogemos dos numeros al azar de los posibles que tenemos

        n=rand()%(N);
        m=rand()%(N);

        //Escribamos la matriz en el fichero

        aux= (i%(N*N));
        

        //Procedemso a calcular deltaE según todos los posibles casos, basandonos en las condiciones periodicas para no salirnos de la matriz

        if (n+1==N)
        {
            if (m+1==N)
            {
                DE=2.*s[n][m]*(s[0][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
            }
            else if (m==0)
            {
                DE=2.*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else{

                DE=2.*s[n][m]*(s[0][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
            }
        }
        else if (n==0)
        {
            if (m+1==N)
            {
                DE=2.*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][0]+s[n][m-1]);
            }
            else if (m==0)
            {
                DE=2.*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else{

                DE=2.*s[n][m]*(s[n+1][m]+s[N-1][m]+s[n][m+1]+s[n][m-1]);
            }

        }
        else{

            if (m+1==N)
            {
                DE=2.*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][0]+s[n][m-1]);
            }
            if (m==0)
            {
                DE=2.*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][N-1]);
            }
            else{

                DE=2.*s[n][m]*(s[n+1][m]+s[n-1][m]+s[n][m+1]+s[n][m-1]);
            }

            

        }

        ex=exp(-DE/T);

        if (ex<1)
        {
            p=ex;
        }
        else{
            p=1.;
        }
        

        //Calculamos un numero aleatorio nuevo, esta vez dividimos entre el maximo para que esté entre 0 y 1

        xi = ((float) (rand()%(N+1)))/N;

        //Si xi es menor que p, cambiamos el signo de nuestro elemento

        if (xi<p)
        {
            s[n][m]= -s[n][m];
        }


        if ((i%(N*N))==0)
        {
           /*     for ( k = 0; k < N; k++)
            {
                for (j = 0; j < N-1; j++)
                {
                    fich << s[k][j] << ", ";
                }   

                fich << s[k][N-1] << endl;

            }
                fich << endl;
           */
           pmonte=pmonte +1;
        }
        


    //Para el voluntario vamos a hacer la media

    if (((pmonte%100)==0)&&(i%(N*N)==0))
    {
        ma=magnetizacion(s);
        mn= mn + ma;
        auxe=energia(s);
        prom_e= prom_e + auxe;
        prom_ecuad= prom_ecuad + auxe*auxe;

          //Ahora vamos a calcular la funcion de correlacion

        for ( j = 0; j < N; j++)
        {
            //Vamos a añadir un cotnador extra, para que cuando nos salgamos de la matriz empiece a contar por el uno, dos...
            l=0;            
            for ( k = 0; k < N; k++)
            {
                if ((j+Corr)<N)
                {
                    prom_s[j][k]= prom_s[j][k] + s[j][k]*s[j+Corr][k];
                }
                else{
                    prom_s[j][k]= prom_s[j][k] + s[j][k]*s[l][k];
                    l++;
                }
                
            }
            
        }   
        
    }

}

    //Dividimos para hacer la media

    mn= mn/(pmonte/100);
    prom_e= prom_e/(pmonte/100);
    prom_ecuad=prom_ecuad/(pmonte/100);
    en=prom_e/(2*N+N);
    cn=(prom_ecuad-prom_e*prom_e)/(N*N*T);

    for ( j = 0; j < N; j++)
    {
        for ( k = 0; k < N; k++)
        {
            fi= fi + prom_s[j][k];
        }
            
    }   
    fi=fi/(N*N);
    

  //  fich.close();

    


    return 0;

}


float magnetizacion (float s[][N]){


    float ma;
    int i,j;
    ma=0;

    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            ma=ma+s[i][j];
        }
        
    }
    ma=abs(ma);
    ma=ma/(N*N);

    return ma;
}

float energia (float s[][N]){

    float E=0;
    int i,j;

    //Hacemos la suma teniendo en cuanta qu eno queremos que desborde la matriz

    for ( i = 1; i < N-1; i++)
    {
        for ( j = 1; j < N-1; j++)
        {
            E=s[i][j]*(s[i][j+1]+s[i][j-1]+s[i+1][j]+s[i-1][j]);
        }
        
    }

    //Ahora sumamos los terminos qu efaltaban por el desbordamiento (los extremos)

    //El de i=0 y j=0
    E=s[i][j]*(s[i][j+1]+s[i][N-1]+s[i+1][j]+s[N-1][j]);
    //El de i=0 j=N-1
    E=s[i][j]*(s[i][0]+s[i][j-1]+s[i+1][j]+s[N-1][j]);
    //El de i=0 y j lo q sea

    for ( j = 1; j < N-1; j++)
    {
        E=s[i][j]*(s[i][j+1]+s[i][j-1]+s[i+1][j]+s[N-1][j]);
    }

  //El de i=N-1 y j=0
    E=s[i][j]*(s[i][j+1]+s[i][N-1]+s[0][j]+s[i-1][j]);
    //El de i=N-1 j=N-1
    E=s[i][j]*(s[i][0]+s[i][j-1]+s[0][j]+s[i-1][j]);
    //El de i=N-1 y j lo q sea

    for ( j = 1; j < N-1; j++)
    {
        E=s[i][j]*(s[i][j+1]+s[i][j-1]+s[0][j]+s[i-1][j]);
    }      
    





    return -(1/2)*E;
}

