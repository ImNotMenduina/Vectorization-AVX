#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>

int verifica_linha(int* v , int* soma) ; 

int main(int argc , char* argv[])
{
    const int TAM = atoi(argv[1]) ; 
    const int LIN = TAM ; 
    const int COL = TAM ; 
    int* v   ;
    int soma = 0 ; 
    __m256i load_line256BITS  ;

    int** matrix = (int**) aligned_alloc(32 , sizeof(int*)*LIN) ; 
    for(int i=0; i<LIN ; i++)
    {
        matrix[i] = (int*) aligned_alloc(32 , sizeof(int)*COL) ; 
    }

    for(int i=0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j++)
        {
            if(i==j) matrix[i][j] = 1 ; 
            else    matrix[i][j] = 0 ; 
        }
    }
    
    for(int i=0 ; i<LIN ; i++)
    {
        
        for(int j=0 ; j<COL ; j+=8)
        {   
            //sum = _mm256_setzero_si256() ; 
            if(j == i && matrix[i][j] != 1)
                return -1 ; 

            load_line256BITS =_mm256_load_si256((__m256i*)&matrix[i][j]) ; 
            v = (int*)&load_line256BITS ; 
            
            if(!verifica_linha(v , &soma)) 
                return -1 ; 
        }
        soma = 0 ;

    }  
        
    printf("Matriz Identidade !") ; 

    return 0 ; 
}

int verifica_linha(int* v , int* soma)
{
            int i = 0; 

            while(*soma <= 1 && i < 8)
            {
                *soma += v[i] ; 
                i++ ; 
            }  
            if(*soma > 1)
            {
                return 0 ; 
            }
            else
            {
                return 1 ; 
            }   
}
