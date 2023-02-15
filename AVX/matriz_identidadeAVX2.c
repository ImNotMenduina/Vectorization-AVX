#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>

#define LIN 1024
#define COL 1024

int verifica_linha(int* v , int index_linha) ; 

int main()
{
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
            else    matrix[i][j] = 2 ; 
        }
    }
    
    for(int i=0 ; i<LIN ; i++)
    {
        __m256i sum = _mm256_setzero_si256() ; 
        for(int j=0 ; j<COL ; j+=8)
        {   
            __m256i load_line256BITS  ;
            load_line256BITS =_mm256_load_si256((__m256i*)&matrix[i][j]) ; 
            sum = _mm256_add_epi32(sum , load_line256BITS) ; 
        }
        int* v = (int*)&sum ; 

        verifica_linha(v , i) ; 
    }   

    return 0 ; 
}

int verifica_linha(int* v , int index_linha)
{
    if(v[index_linha] == 1)
        {
            int sum = 0 , i = 0 ; 

            for(int i=0 ; i<COL && sum < 2 ; i++)
                sum += v[i] ; 
            
            if(sum > 1)
            {
                return 1 ; 
            }
        }
        else
        {
                return 1 ; 
        }
}
