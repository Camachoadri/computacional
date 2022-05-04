#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>
#include <complex>

using namespace std;
#define N 500
#define h 0.1
#define PI 3.14
#define n_ciclos 100

int main(void){

    int j,n,k;

    complex <double> phi[N][N], alpha[N], beta[N], xi[N][N], i=(0.,1.);
    double s, k_0, V[N], lambda;

    //Vamos a iniciar la matriz de la funcion de onda y los parametros necesarios

    lambda=0.3;
    s=1./(4.*k_0*k_0);

    k_0=n_ciclos*2*PI/(N);

    for ( j = 1; j < N-1; j++)
    {

        phi[j][0]= exp(((double) j)*k_0*i)*exp(-8*(4*j-(N*N))/(N*N));
    } 

    phi[0][0]=0;
    phi[N][0]=0;

    //Ahora vamos a iniciar la barrera de potencial

    for ( j = 1; j < N-1; j++)
    {
        phi[j][0]= exp((double) j*k_0*i)*exp(-8*(4*j-(N*N))/(N*N));
    } 
    


    return 0;
}