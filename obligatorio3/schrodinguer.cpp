#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>
#include <complex>

using namespace std;
#define N 200
#define h 0.1
#define PI 3.14
#define n_ciclos N/16
#define npasos 1000

int main(void){

    int j,n,k;

    complex <double> phi[200], alpha[200], beta[200], xi[200], i=(0.,1.);
    double s, k_0, V[200], lambda;

    //Vamos a iniciar la matriz de la funcion de onda y los parametros necesarios

    lambda=0.3;
    s=1./(4.*k_0*k_0);

    k_0=n_ciclos*2*PI/(N);

    for ( j = 1; j < N-1; j++)
    {

        phi[j]= exp(((double) j)*k_0*i)*exp(-8*(4*j-(N*N))/(N*N));
    } 

    phi[0]=0;
    phi[N-1]=0;

    //Ahora vamos a iniciar la barrera de potencial

    for ( j = 0; j < N; j++)
    {
        if((j>=(2*N/5))&&(j<=(3*N/5))){
            V[j]=lambda*k_0*k_0;
        }
        else{
            V[j]=0;
        }
    } 


    //Ahora comenzaremos el bucle inicializando alpha
    alpha[N-1]=0.;
    //Y generamos todos los alpha ya que no dependen de n
    for ( j = N-1; j > 0; j--)
    {
        alpha[j-1]=-1./(-2.+2.*i/s+alpha[j]);
    }
    


    for ( n = 0; n < npasos; n++)
    {
        //Para empezar escribimos en el ficheros los valroes de la funcion de onda

        
        //Lo primero será incicializar y calcular beta
        beta[N-1]=0.;
        for ( j = N-1; j > 0; j--)
          {
           beta[j-1]=(1./(-2.+2.*i/s+alpha[j]))*(4.*i*phi[j]/s);
          }
        //Ahora ya podemos calcular la xi
        for ( j = 0; j < N-1 ; j++)
        {
            xi[j+1]= alpha[j]*xi[j]+beta[j];
        }
        xi[N-1]=0;
        
        //Finalmetne vamos a calcular la funcion de onda
        for ( j = 0; j < N; j++)
        {
            phi[j]=xi[j]-phi[j];
        }
        

    }
    
    


    return 0;
}