#include <iostream>
#include<cmath>
#include<fstream>
#include <algorithm>


using namespace std;

int main (void){

    float T;
    int N=1000, i, j,n,m;
    float s[N][N],p, DE;

    //Inicializamso las variables necesarias

    T=1;
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            s[i][j]=1;
        }
        
    }
    
    for ( i = 0; i < N*N; i++)
    {
        //Escogemos dos numeros al azar de los posibles que tenemos

        n=rand()%(N-1);
        m=rand()%(N-1);

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
        

        p = min(1,exp(-DE/T));

    }
    

    return 0;

}
