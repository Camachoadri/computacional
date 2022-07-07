#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>
#include <complex>

using namespace std;
#define h 0.1
#define PI 3.14
#define n_ciclos N/8
#define npasos 2000
#define nmin 500

int main(void){

    int j,n,k,nmax,cont,otrocont,N,contadorglobal;

    N=500;

    complex <double> phi[2000], alpha[2000], beta[2000], xi[2000], i;
    double s, k_0, V[2000], lambda, norma, normaantigua,normaantiguantigua,x,prob,mt,normatot,normatotant,normatotantant;
    double tiros,x_e,mom_e,energiac_e,energiapot_e,normaestepaso,x_ecuad,auxmom,auxcinetica,diferencia;
    float K[100], Ktotal, errork;
    ofstream fich, norm_fich,energiac,energiapot,momento,posicion,etot,transmision;
    i= complex<double>(0.0,1.0);

transmision.open("transmision.dat");

for ( contadorglobal = 0; contadorglobal < 1; contadorglobal++)
{
    //Vamos a iniciar la matriz de la funcion de onda y los parametros necesarios

    lambda=0.5 + contadorglobal*0.1;
    k_0=n_ciclos*2.*PI/(N*1.);
    s=(1./(4.*k_0*k_0));
    tiros=pow(10,6);
    mt=0.;
    srand(1);

    phi[0]=0;
    phi[N-1]=0;

    for ( j = 1; j < N-1; j++)
    {

        phi[j]= exp(j*1.0*k_0*i)*exp(-8.*(4.*j-N)*(4.*j-N)/(N*N));
    }


    //Ahora vamos a iniciar la barrera de potencial

    for ( j = 0; j < N; j++)
    {
        if(/*(j>=(12*N/30))&&(j<=(13*N/30))||(j>=(14*N/30))&&(j<=(15*N/30))||(j>=(16*N/30))&&(j<=(17*N/30))||(j>=(18*N/30))&&(j<=(19*N/30))||(j>=(20*N/30))&&(j<=(21*N/30))||(j>=(22*N/30))&&(j<=(23*N/30))||(j>=(24*N/30))&&(j<=(25*N/30))||*/(j>=(26*N/30))&&(j<=(27*N/30))){
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
    energiac.open("energiac.dat");
    momento.open("momento.dat");
    energiapot.open("energiapot.dat");
    posicion.open("posicion.dat");
    etot.open("energiatotal.dat");

    norma=0.;
    normatot=0.;
    n=0;
    //Le damos valores negativos en un inicio para qu eno interfiera con el valor de 0 y acabe el bucle
    normaantigua=-0.0000001;
    normaantiguantigua=-0.0000001;
    normatotant=-0.0000001;
    normatotantant=-0.0000001;

    //Repetiremos la iteracion hasta que la norma nueva sea menor que la antigua (y por tanto el punto anterior era un maximo local)

    do
    {
        //Colcamos la norma en una norma auxiliar para comparar luego
        normaantiguantigua=normaantigua;
        normaantigua=norma;

        //Tambien necesitamos la norma total, para poder normalizar el resultado

        normatotantant=normatotant;
        normatotant=normatot;

        //Para empezar escribimos en el ficheros los valores de la funcion de onda, ademas los sumaremos todos y tmb ploteamos esta suma
        norma=0;
        normatot=0.;


        //Inicializamos los valores esperados

        x_e=0.;
        mom_e=0.;
        energiac_e=0.;
        energiapot_e=0.;
        x_ecuad=0.;



        //Para el voluntario solo miramos la norma de la derecha

        for ( j = 0; j < N; j++) //4*N/5
        {
            normaestepaso=norm(phi[j]);
            normatot= normatot + normaestepaso;
            fich << j*h << ", " << normaestepaso << ", " << V[j] << endl;
        }

        for ( j = 28*N/30; j < N; j++)
        {
            norma=norma + norm(phi[j]);
        }

        //Ahora calculamos los valores esperados y su cuadrado para las incertidumbres

        //Para la energia cinetica y el momento debemos hacer la primera iteración aparte

        auxmom= sqrt(norm(-0.5*i*conj(phi[0])*(phi[1]-phi[0])));
        mom_e= mom_e + auxmom/(normatot);
        auxcinetica = sqrt(norm(-1.0*conj(phi[0])*(phi[1]+phi[0]-2.0*phi[0])));
        energiac_e= energiac_e + auxcinetica/(normatot);

        for ( j = 0; j < N; j++)
        {
            normaestepaso=norm(phi[j]);
            prob=normaestepaso/(normatot);
            x_e=x_e+ j*prob;
            x_ecuad=x_ecuad + j*j*prob;
        }

        for ( j = 1; j < N-1; j++)
        {
            auxmom= sqrt(norm(-0.5*i*conj(phi[j])*(phi[j+1]-phi[j-1])));
            mom_e= mom_e + auxmom/(normatot);

            auxcinetica= sqrt(norm(-1.0*conj(phi[j])*(phi[j+1]+phi[j-1]-2.0*phi[j])));
            energiac_e= energiac_e + auxcinetica/(normatot);
        }


        //Calculamos aparte el ultimo termino
        auxmom= sqrt(norm(-0.5*i*conj(phi[N-1])*(phi[N-1]-phi[N-2])));
        mom_e= mom_e + auxmom/(normatot);

        auxcinetica= sqrt(norm(-1.0*conj(phi[N-1])*(phi[N-1]+phi[N-2]-2.0*phi[N-1])));
        energiac_e= energiac_e + auxcinetica/(normatot);



        //Ahora vamos con el valor esperado de V

        for ( j = 2*N/5  ; j < 3*N/5 ; j++)
        {
            normaestepaso=norm(phi[j]);
            prob=normaestepaso/(normatot);
            energiapot_e= energiapot_e + V[j]*prob;
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


        //Finalmente vamos a calcular la funcion de onda
        for ( j = 0; j < N; j++)
        {
            phi[j]=xi[j]-phi[j];
        }

      //  cout << phi[0];


        norm_fich << norma/normatot<< endl;
        posicion << n << "   " << x_e <<  "    " << sqrt(x_ecuad-x_e*x_e)/sqrt(N) << endl;
        energiapot << n <<  "    " << energiapot_e  << endl;
        energiac << n << "   " << energiac_e << endl;
        momento << n << "    " << mom_e << "    " << sqrt(energiac_e- mom_e*mom_e)/sqrt(N) << endl;

        etot << energiac_e + energiapot_e << endl;


        fich << endl;
        diferencia= abs(norma/normatot-abs(normaantiguantigua/normatotantant));
        n++;

    }
    while ((n<npasos)&&((diferencia<0.001)||((norma>normaantigua)||(normaantigua>normaantiguantigua))));

    fich.close();
    norm_fich.close();
    energiac.close();
    momento.close();
    energiapot.close();
    posicion.close();
    etot.close();

    //Como por mucho que lo simulemos hasta ahora no hay nada aleatorio, la probabilidad será la misma, luego esta no variará
    normaantiguantigua=normaantiguantigua/normatotantant;
    prob=normaantiguantigua;


    for ( otrocont = 0; otrocont < 40; otrocont++)
    {
        mt=0;
        for ( cont = 0; cont < tiros; cont++)
        {
            x=rand()/(RAND_MAX*1.0);
            if (x<prob)
            {
                mt++;
            }
        }
        K[otrocont]= mt/tiros;
    }

    Ktotal=0;
    for ( otrocont = 0; otrocont < 40; otrocont++)
    {
        Ktotal= Ktotal + K[otrocont];
    }

    Ktotal=Ktotal/40.;

    //Ahora calculamos su incertidumbre

    errork=0.;

    for ( otrocont = 0; otrocont < 40; otrocont++)
    {
        errork= errork + (K[otrocont]-Ktotal)*(K[otrocont]-Ktotal);
    }

    errork= errork/50.;

    errork= 2.*sqrt(errork)/sqrt(40);



    //Volcamos k en el fichero
    cout << lambda << "   " << Ktotal << "   " << errork << endl;

}

transmision.close();

    return 0;
}
