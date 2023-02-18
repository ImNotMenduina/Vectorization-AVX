#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    const int TAM = atoi(argv[1]) ; 
    const int LIN = TAM ; 
    const int COL = TAM ;  

    int** ma = (int**) aligned_alloc(32 , LIN * sizeof(int*)) ; 
    int** mb = (int**) aligned_alloc(32 , LIN * sizeof(int*)) ; 
    int** mc = (int**) aligned_alloc(32 , LIN * sizeof(int*)) ; 

    for(int i=0 ; i<LIN ; i++)
        ma[i] = (int*) aligned_alloc(32 , COL * sizeof(int)) ; 
    
    for(int i=0 ; i<COL ; i++)
        mb[i] = (int*) aligned_alloc(32 , COL * sizeof(int)) ;

    for(int i=0 ; i<COL ; i++)
        mc[i] = (int*) aligned_alloc(32 , COL * sizeof(int)) ;

    for(int i=0 ; i<LIN ; i++)
        for(int j=0 ; j<COL ; j++)
            ma[i][j] = 5; 

    for(int i=0 ; i<LIN ; i++)
        for(int j=0 ; j<COL ; j++)
            mb[i][j] = 4 ; 

    for(int i=0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j++)
        {
            for(int k=0 ; k<LIN ; k++)
            {
                mc[i][j] += ma[i][k] * mb[k][j] ; 
            }
        }
    }

return 0 ; 
}