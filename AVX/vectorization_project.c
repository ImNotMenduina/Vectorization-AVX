#include<stdio.h>
#include<stdlib.h> 
#include<immintrin.h>
#include<omp.h>

#define LIN 8 
#define COL 8

int main()
{
    int** ma = (int**) aligned_alloc(32 ,LIN * sizeof(int*)) ; 
    int** mb = (int**) aligned_alloc(32 ,LIN * sizeof(int*)) ; 
    int** mc = (int**) aligned_alloc(32 ,LIN * sizeof(int*)) ; 
    for(int i=0 ; i<LIN ; i++)
        ma[i] = aligned_alloc(32 , COL*sizeof(int)) ; 

    for(int i=0 ; i<LIN ; i++)
        for(int j=0 ; j<COL ; j++)
            ma[i][j] = 5.0 ; 
        
     for(int i=0 ; i<LIN ; i++)
        mb[i] = aligned_alloc(32 , COL*sizeof(int)) ; 

    for(int i=0 ; i<LIN ; i++)
        for(int j=0 ; j<COL ; j++)
            mb[i][j] = 5.0 ; 
            
    for(int i=0 ; i<LIN ; i++)
        mc[i] = aligned_alloc(32 , COL*sizeof(int)) ;

    for(int i=0 ; i<LIN ; i++)
        for(int j=0 ; j<COL ; j++)
            mc[i][j] = 0.0 ; 
    

    for(int i =0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j+=8)
        {
            __m256i inteiros = _mm256_set1_epi32(ma[i][j]) ;
            __m256i inteiros2 = _mm256_set1_epi32(mb[i][j]) ; 
            __m256i soma = _mm256_add_epi32(inteiros , inteiros2) ;
            _mm256_storeu_si256( (__m256i*)&mc[i][j],soma) ; 
        }
    } 

    for(int i=0 ; i<LIN ; i++)
    {
        for(int j=0 ; j<COL ; j++)
        {
            printf("%d " , mc[i][j]) ;
        }  
        printf("\n") ; 
    }
        
             


  


    
}