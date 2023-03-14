#include<stdio.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    const int TAM = atoi(argv[1]) ; 
    const int LIN = TAM ; 
    const int COL = TAM ;  

    int** ma = (int**) malloc(LIN * sizeof(int*)) ; 
    int** mb = (int**) malloc(LIN * sizeof(int*)) ; 
    int** mc = (int**) malloc(LIN * sizeof(int*)) ; 

    for(int i=0 ; i<LIN ; i++)
        ma[i] = (int*) malloc(COL * sizeof(int)) ; 
    
    for(int i=0 ; i<COL ; i++)
        mb[i] = (int*) malloc(COL * sizeof(int)) ;

    for(int i=0 ; i<COL ; i++)
        mc[i] = (int*) malloc(COL * sizeof(int)) ;

    for(int i=0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j++)
        {
            ma[i][j] = (rand() % 1000);
            mb[i][j] = (rand() % 1000) ;
        }
    } 

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