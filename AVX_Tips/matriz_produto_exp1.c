#include<stdio.h>
#include<stdlib.h> 
#include<immintrin.h>
#include<omp.h>

int main(int argc , char* argv[])
{
    const int N = atoi(argv[1]) ;
    const int LIN = N ; 
    const int COL = N ; 

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
            mb[i][j] = 4.0 ; 
            
     for(int i=0 ; i<LIN ; i++)
        mc[i] = (int*) aligned_alloc(32 , COL*sizeof(int)) ;         
   
    

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j += 16) 
        {
            __m256i sumA = _mm256_setzero_si256();
            __m256i sumB = _mm256_setzero_si256();
            for (int k = 0; k < N; k++) 
            {
                __m256i bc_mat1 = _mm256_set1_epi32(ma[i][k]);
                
                __m256i vecA_mat2 = _mm256_loadu_si256((__m256i*)&mb[k][j]);
                __m256i vecB_mat2 = _mm256_loadu_si256((__m256i*)&mb[k][j + 8]);
                __m256i prodA = _mm256_mullo_epi32(bc_mat1, vecA_mat2);
                __m256i prodB = _mm256_mullo_epi32(bc_mat1, vecB_mat2);
                sumA = _mm256_add_epi32(sumA, prodA);
                sumB = _mm256_add_epi32(sumB, prodB);
            }
            _mm256_storeu_si256((__m256i*)&mc[i][j], sumA);
            _mm256_storeu_si256((__m256i*)&mc[i][j + 8], sumB);
        }
    }
    
}