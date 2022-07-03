#include<iostream>
#include<cmath>
#include<fstream>
#include<algorithm>
#include <unistd.h>


using namespace std;

float magnetizacion (int s[][128],int N);
float energia (int s[][128], int N);

int main (void){

    float T;
    int i, j,k,n,m,pmonte,l,N,Corr,s[128][128],contador,conttemp;
    float p, DE, xi, mn,en,cn, ex, ma,prom_e,prom_ecuad,auxe,fi, prom_s[128][128],ma_cuad,erroren;
    ofstream fich,ener,magnet,calor,correlacion;

    N=128;
    Corr=1;

ener.open("energia.dat");
magnet.open("magnetizacion.dat");
calor.open("calor.dat");
correlacion.open("correlacione.dat");

for ( conttemp = 0; conttemp < 10 ; conttemp++)
{

    T=1.7+0.2*conttemp;

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
                s[i][j]=-1;
            }
            else{
                s[i][j]=1;
            }
        }

    }

*/

   // fich.open("ising_data.dat");


//Iniciamos el contador de monte carlos y del voluntario
    pmonte=-1;

    mn=0.;
    en=0.;
    cn=0.;
    fi=0.;
    prom_e=0.;
    prom_ecuad=0.;
    ma_cuad=0.;
    auxe=0.;
    contador=0;
    //Inicializamos los numeros aleatorios con la misma semilla, para garantizar "misma aleatoriedad"
    srand(1);

    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            prom_s[i][j]=0.;
        }

    }



//Comenzamos el algoritmo en si

    for ( i = 0; i < pow(10,6); i++)
    {
        //Hacemos un for para cada Pmc
    for ( k = 0; k < N*N; k++)
    {
        //Escogemos dos numeros al azar de los posibles que tenemos

        n=rand()%(N);
        m=rand()%(N);


        //A continuacion procedemos a aplicar las condiciones de contorno, como solo hay sumas de uno en uno se pueden resumir en:
/*
        for ( j = 0; j < N; j++)
        {
            //Cuando nos salimso por la derecha o izq tenemos el contorno
            s[N+1][j]=s[1][j];
            s[0][j]=s[N][j];

            //Cuando nos salimos por arriba o abajo tenemos el contorno

            s[j][N+1]=s[j][1];
            s[j][0]=s[j][N];
        }


*/

         // Esta forma es mas costosa computacionalmente
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

        p=exp(-DE/T);
        if (p>1)
        {
            p=1.0;
        }

        //Calculamos un numero aleatorio nuevo, esta vez dividimos entre el maximo para que esté entre 0 y 1

         xi=rand()/(RAND_MAX*1.0);
        if(xi<p)
        {
            s[n][m]=-s[n][m];
        }
    }


    /*
       // No escribimos anda para el voluntario
            for ( k = 0; k < N; k++)
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





    //Para el voluntario vamos a hacer la media

    if ((pmonte==100))
    {
        ma=magnetizacion(s,N);
        mn= mn + ma;
        ma_cuad= ma_cuad + ma*ma;
        auxe=energia(s,N);
        prom_e= prom_e + auxe;
        prom_ecuad= prom_ecuad + auxe*auxe;

          //Ahora vamos a calcular la funcion de correlacion esto solo lo usaremos para un caso especifico

        for ( j = 0; j < N; j++)
        {
            //Vamos a añadir un contador extra, para que cuando nos salgamos de la matriz empiece a contar por el uno, dos...
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
        pmonte=-1;
        contador++;
    }
}

    //Dividimos para hacer la media

    mn= mn/(1.0*(contador));
    ma_cuad=ma_cuad/(1.0*contador);
    prom_e= prom_e/(1.0*contador);
    prom_ecuad=prom_ecuad/(1.0*contador);
    en=prom_e/(2.0*N*N);
    erroren=sqrt(prom_ecuad-(prom_e*prom_e));
    cn=erroren*erroren/(N*N*T*T);


    for ( j = 0; j < N; j++)
    {
        for ( k = 0; k < N; k++)
        {
            fi= fi + prom_s[j][k];
        }

    }
    fi=fi/((N*N)*(1.0*contador));

/*
    //fich.close();

    cout << en << "    " << erroren/(sqrt(1.0*contador)*2.0*N) << endl;
    cout << mn << "     " << sqrt(ma_cuad-mn*mn)/sqrt(1.0*contador) << endl;
    cout << cn << endl;
    cout << fi << endl;
*/
    ener << en << "    " << erroren/(sqrt(1.0*contador)*2.0*N) << endl;
    magnet << mn << "     " << sqrt(ma_cuad-mn*mn)/sqrt(1.0*contador) << endl;
    calor << cn << endl;
    correlacion << fi << endl;

}

ener.close();
magnet.close();
calor.close();
correlacion.close();


    return 0;

}


float magnetizacion (int s[][128], int N){


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

float energia (int s[][128], int N){

    float E=0.;
    int i,j;

    //Hacemos la suma teniendo en cuanta qu eno queremos que desborde la matriz

    for ( i = 1; i < N-1; i++)
    {
        for ( j = 1; j < N-1; j++)
        {
            E=E+ 1.*s[i][j]*(s[i][j+1]+s[i][j-1]+s[i+1][j]+s[i-1][j]);
        }

    }

    //Ahora sumamos los terminos qu efaltaban por el desbordamiento (los extremos)

    //El de i=0 y j=0
    E=E+ 1.*s[0][0]*(s[0][1]+s[0][N-1]+s[1][0]+s[N-1][0]);
    //El de i=0 j=N-1
    E=E+1.*s[0][N-1]*(s[0][0]+s[0][N-2]+s[1][N-1]+s[N-1][N-1]);
    //El de i=0 y j lo q sea

    for ( j = 1; j < N-1; j++)
    {
        E=E+1.*s[0][j]*(s[0][j+1]+s[0][j-1]+s[1][j]+s[N-1][j]);
    }

  //El de i=N-1 y j=0
    E=E+1.*s[N-1][0]*(s[N-1][1]+s[N-1][N-1]+s[0][0]+s[N-2][0]);
    //El de i=N-1 j=N-1
    E=E+1.*s[N-1][N-1]*(s[N-1][0]+s[N-1][N-2]+s[0][N-1]+s[N-2][N-1]);
    //El de i=N-1 y j lo q sea

    for ( j = 1; j < N-1; j++)
    {
        E=E+1.*s[N-1][j]*(s[N-1][j+1]+s[N-1][j-1]+s[0][j]+s[N-2][j]);
    }

    //El de j=0 i lo que sea
    for ( i = 1; i < N-1; i++)
    {
        E=E+ 1.*s[i][0]*(s[i][1]+s[i][N-1]+s[i+1][0]+s[i-1][0]);
    }
    //El de j=N-1 i lo que sea
    for ( i = 1; i < N-1; i++)
    {
        E=E+ 1.*s[i][N-1]*(s[i][0]+s[i][N-2]+s[i+1][N-1]+s[i-1][N-1]);
    }




    E=-(0.5)*E;



    return E;
}
