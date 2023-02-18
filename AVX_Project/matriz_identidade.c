#include<stdio.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
    const int TAM = atoi(argv[1]) ; 
    const int LIN = TAM ; 
    const int COL = TAM ; 

    int** m = (int**) malloc(LIN * sizeof(int*)) ; 
    for(int i=0 ; i<LIN ; i++)
        m[i] = (int*)malloc(COL * sizeof(int)) ; 

    for(int i=0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j++)
        {
            if(i==j) m[i][j] = 1 ; 
            else     m[i][j] = 0 ; 
        }
    }

    int soma_linha ; 

    for(int i=0 ; i<LIN ; i++)
    {
        soma_linha = 0 ; 

        for(int j = 0 ; j < COL ; j++)
        { 
            if(soma_linha > 1 || (i == j && m[i][j] != 1)) exit(1) ;
            soma_linha += m[i][j] ;  
        }
    }

    printf("Matriz Identidade") ; 

    

    return 0 ; 
}