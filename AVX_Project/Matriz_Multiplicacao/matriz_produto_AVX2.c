#include <stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<immintrin.h>

int main(int argc, char *argv[])
{
    const int TAM = atoi(argv[1]) ;
    const int LIN = TAM ; 
    const int COL = TAM ; 

 
    float** matriz_A = (float**)_mm_malloc(LIN * sizeof(float*) , 32) ; 
    float** matriz_B = (float**)_mm_malloc(LIN * sizeof(float*) , 32) ; 
    float** matriz_C = (float**)_mm_malloc(LIN * sizeof(float*) , 32) ;  

        for(int i=0 ; i<LIN ; i++)
            matriz_A[i] = (float*)_mm_malloc(COL * sizeof(float) , 32) ;   
        
        for(int i=0 ; i<LIN ; i++)
            matriz_B[i] =  (float*)_mm_malloc(COL * sizeof(float) , 32) ;

        for(int i=0 ; i<LIN ; i++)
            matriz_C[i] =  (float*)_mm_malloc(COL * sizeof(float) , 32) ;

        for(int i=0 ; i<LIN ; i++)
        {
            for(int j=0 ; j<COL ; j++)
            {
                matriz_A[i][j] = (rand() % 1000) ; 
                matriz_B[i][j] = (rand() % 1000) ; 
            }
        }

        for(int i = 0 ; i<LIN ; i++)
        {
            for(int j = 0 ; j<COL ; j+=32) 
            {
                __m256 soma256_0 = _mm256_setzero_ps();
                __m256 soma256_1 = _mm256_setzero_ps();
                __m256 soma256_2 = _mm256_setzero_ps();
                __m256 soma256_3 = _mm256_setzero_ps();

                for(int k = 0 ; k<LIN ; k+=2)
                {
                    // Vetor com elementos iguais.
                    __m256 Elemento_LIN = _mm256_set1_ps(matriz_A[i][k]) ; 

                    __m256 vect00 = _mm256_loadu_ps((float*)&matriz_B[k][j]) ;
                    __m256 vect01 = _mm256_loadu_ps((float*)&matriz_B[k][j+8]) ;  
                    __m256 vect02 = _mm256_loadu_ps((float*)&matriz_B[k][j+16]) ; 
                    __m256 vect03 = _mm256_loadu_ps((float*)&matriz_B[k][j+24]) ; 

                    __m256 prod00 = _mm256_mul_ps(Elemento_LIN , vect00) ; 
                    __m256 prod01 = _mm256_mul_ps(Elemento_LIN , vect01) ; 
                    __m256 prod02 = _mm256_mul_ps(Elemento_LIN , vect02) ; 
                    __m256 prod03 = _mm256_mul_ps(Elemento_LIN , vect03) ; 
 
                    soma256_0 = _mm256_add_ps(soma256_0 , prod00) ;
                    soma256_1 = _mm256_add_ps(soma256_1 , prod01) ; 
                    soma256_2 = _mm256_add_ps(soma256_2 , prod02) ; 
                    soma256_3 = _mm256_add_ps(soma256_3 , prod03) ;
 
                    //REUTILIZAÇÃO DE REGISTRADORES
                    Elemento_LIN = _mm256_set1_ps(matriz_A[i][k+1]) ; 

                    vect00 = _mm256_loadu_ps((float*)&matriz_B[k+1][j]) ;
                    vect01 = _mm256_loadu_ps((float*)&matriz_B[k+1][j+8]) ;  
                    vect02 = _mm256_loadu_ps((float*)&matriz_B[k+1][j+16]) ; 
                    vect03 = _mm256_loadu_ps((float*)&matriz_B[k+1][j+24]) ;

                    prod00 = _mm256_mul_ps(Elemento_LIN , vect00) ; 
                    prod01 = _mm256_mul_ps(Elemento_LIN , vect01) ; 
                    prod02 = _mm256_mul_ps(Elemento_LIN , vect02) ; 
                    prod03 = _mm256_mul_ps(Elemento_LIN , vect03) ; 
                    
                    soma256_0 = _mm256_add_ps(soma256_0 , prod00) ;
                    soma256_1 = _mm256_add_ps(soma256_1 , prod01) ; 
                    soma256_2 = _mm256_add_ps(soma256_2 , prod02) ; 
                    soma256_3 = _mm256_add_ps(soma256_3 , prod03) ; 

                }  
                    _mm256_storeu_ps((float*)&matriz_C[i][j] , soma256_0) ; 
                    _mm256_storeu_ps((float*)&matriz_C[i][j+8] , soma256_1) ; 
                    _mm256_storeu_ps((float*)&matriz_C[i][j+16] , soma256_2) ; 
                    _mm256_storeu_ps((float*)&matriz_C[i][j+24] , soma256_3) ; 
            }
        }

    return 0 ; 
}