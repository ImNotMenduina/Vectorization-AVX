#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    const int TAM = atoi(argv[1]) ; 
    const int LIN = TAM ; 
    const int COL = TAM ; 

    int** mi = (int**) malloc(LIN * sizeof(int*)) ;
    int** mb = (int**) malloc(LIN * sizeof(int*)) ;
    int** mc = (int**) malloc(LIN * sizeof(int*)) ;  

    for(int i=0 ; i<LIN ; i++)
    {
        mi[i] = (int*)malloc(COL * sizeof(int)) ;
        mb[i] = (int*)malloc(COL * sizeof(int)) ;
        mc[i] = (int*)malloc(COL * sizeof(int)) ;
    }
    for(int i=0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j++)
        {
            if(i==j) mi[i][j] = 1 ; 
            else     mi[i][j] = 0 ;

            mb[i][j] = rand() % 1000 ;
            mc[i][j] = 0 ;   
        }
    }

    for(int i=0 ; i < TAM ; i++)
    {
        for(int j=0 ; j < TAM ; j++)
        {
            for(int k=0 ; k < TAM ; k++)
            {
                mc[i][j] += mi[i][k]*mb[k][j] ; 
            }
        }
    }

    for(int i=0 ; i<TAM ; i++)
    {
        for(int j=0 ; j<TAM ; j++)
        {
            if(mc[i][j] != mb[i][j])
            {
                return -1 ; 
            }
        }
    }
return 0 ; 
}








