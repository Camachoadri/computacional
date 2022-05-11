#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>
#include <complex>

using namespace std;
#define N 200
#define h 0.1
#define PI 3.14
#define n_ciclos N/8
#define npasos 1000

int main(void){

    int j,n,k;

    complex <double> phi[200], alpha[200], beta[200], xi[200], i;
    double s, k_0, V[200], lambda, norma;
    ofstream fich, norm_fich;
    i= complex<double>(0.0,1.0); 

    //Vamos a iniciar la matriz de la funcion de onda y los parametros necesarios

    lambda=0.3;
    k_0=n_ciclos*2*PI/(N);
    s=(1./(4.*k_0*k_0));

    phi[0]=0;
    phi[N-1]=0;

    for ( j = 1; j < N-1; j++)
    {

        phi[j]= exp(j*1.0*k_0*i)*exp(-8.*(4.*j-N)*(4.*j-N)/(N*N));
    } 


    //Ahora vamos a iniciar la barrera de potencial

    for ( j = 0; j < N; j++)
    {
        if((j>=(2*N/5))&&(j<=(3*N/5))){
            V[j]=lambda*k_0*k_0;
        }
        else{
            V[j]=0.;
        }
    } 


    //Ahora comenzaremos el bucle inicializando alpha
    alpha[N-2]=0.;
    //Y generamos todos los alpha ya que no dependen de n
    for ( j = N-2; j > 0; j--)
    {
        alpha[j-1]=-1./(-2.+2.*(i/s)+alpha[j]-V[j]);
    }
    
    fich.open("schrodinger_data.dat"); 
    norm_fich.open("norma.dat");


    for ( n = 0; n < npasos; n++)
    {
        //Para empezar escribimos en el ficheros los valroes de la funcion de onda, ademas los sumaremos todos y tmb ploteamos esta suma
        norma=0;
        
        for ( j = 0; j < N; j++)
        {
            norma=norma + norm(phi[j]);
            fich << j*h << ", " << norm(phi[j]) << ", " << V[j] << endl;
        }
        

        //Lo primero será incicializar y calcular beta
        beta[N-2]=0.;
        for ( j = N-2; j > 0; j--)
          {
           beta[j-1]=(1./(-2.+2.*(i/s)+alpha[j]-V[j]))*(4.*i*(phi[j]/s)-beta[j]);
          }
        //Ahora ya podemos calcular la xi
    
        xi[0]=0.;    
        for ( j = 0; j < N-2 ; j++)
        {
            xi[j+1]= alpha[j]*xi[j]+beta[j];
        }

        
        //Finalmetne vamos a calcular la funcion de onda
        for ( j = 0; j < N; j++)
        {
            phi[j]=xi[j]-phi[j];
        }
         
      //  cout << phi[0];
        
        norm_fich << norma << endl;
                
        fich << endl;
    }
    
    fich.close();
    norm_fich.close();


    return 0;
}
