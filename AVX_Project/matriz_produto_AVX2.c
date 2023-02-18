#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char *argv[])
{
    const int TAM = atoi(argv[1]) ; // TAMANHO MATRIZ QUADRADA  
    const int LIN = TAM ; 
    const int COL = TAM ; 

    int** matriz_A = (int**)malloc(LIN * sizeof(int*)) ; 
    int** matriz_B = (int**)malloc(LIN * sizeof(int*)) ;
    int** matriz_C = (int**)malloc(LIN * sizeof(int*)) ;  
        // AQUI EU CRIO MINHA MATRIZ DINAMICAMENTE
        //Utilizei aligned_malloc para alinar a memória em chunks de 64 bytes == 512bits
        for(int i=0 ; i<LIN ; i++)
            matriz_A[i] = (int*)aligned_alloc(32 ,COL * sizeof(int)) ;  
        
        for(int i=0 ; i<LIN ; i++)
            matriz_B[i] = (int*)aligned_alloc(32 ,COL * sizeof(int)) ; 

        for(int i=0 ; i<LIN ; i++)
            matriz_C[i] = (int*)aligned_alloc(32 ,COL * sizeof(int)) ; 
        
        //Povoar as matrizes com numeros randomicos entre 0 e 9999
        for(int i=0 ; i<LIN ; i++)
        {
            for(int j=0 ; j<COL ; j++)
            {
                matriz_A[i][j] = (rand() % 1000) ; 
                matriz_B[i][j] = (rand() % 1000) ; 
            }
        }
    //aqui eu vou criar uma mask caso a ordem da matriz nao seja divisivel por 8

        for(int i = 0 ; i<LIN ; i++)
        {
            for(int j = 0 ; j<COL ; j+=64) // Irei vetorizar 128 em 128 elementos. Matriz máxima deve ser de 
            {
                __m256i soma256_0 = _mm256_setzero_si256();
                __m256i soma256_1 = _mm256_setzero_si256();
                __m256i soma256_2 = _mm256_setzero_si256();
                __m256i soma256_3 = _mm256_setzero_si256();
                __m256i soma256_4 = _mm256_setzero_si256();
                __m256i soma256_5 = _mm256_setzero_si256();
                __m256i soma256_6 = _mm256_setzero_si256();
                __m256i soma256_7 = _mm256_setzero_si256();
  /*            __m256i soma256_8 = _mm256_setzero_si256();
                __m256i soma256_9 = _mm256_setzero_si256();
                __m256i soma256_10 = _mm256_setzero_si256();
                __m256i soma256_11 = _mm256_setzero_si256();
                __m256i soma256_12 = _mm256_setzero_si256();
                __m256i soma256_13 = _mm256_setzero_si256();
                __m256i soma256_14 = _mm256_setzero_si256();
                __m256i soma256_15 = _mm256_setzero_si256(); */

                
                for(int k = 0 ; k<LIN ; k++)
                {
                    // Vetor com elementos iguais.
                    __m256i Elemento_LIN_A = _mm256_set1_epi32(matriz_A[i][k]) ; 

                    __m256i vect00 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j]) ;
                    __m256i vect01 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+8]) ;  
                    __m256i vect02 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+16]) ; 
                    __m256i vect03 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+24]) ; 
                    __m256i vect04 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+32]) ; 
                    __m256i vect05 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+40]) ; 
                    __m256i vect06 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+48]) ;
                    __m256i vect07 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+56]) ;
/*                  __m256i vect08 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+64]) ;  
                    __m256i vect09 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+72]) ; 
                    __m256i vect10 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+80]) ; 
                    __m256i vect11 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+88]) ; 
                    __m256i vect12 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+96])  ; 
                    __m256i vect13 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+104]) ; 
                    __m256i vect14 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+112]) ;
                    __m256i vect15 = _mm256_loadu_si256((__m256i*)&matriz_B[k][j+120]) ; */

                    //MULTIPLICO O ELEMENTO DA LINHA A POR TODOS OS ELEMENTOS 128 COLUNAS SUBSEQUENTES
                    __m256i prod00 = _mm256_mullo_epi32(Elemento_LIN_A , vect00) ; 
                    __m256i prod01 = _mm256_mullo_epi32(Elemento_LIN_A , vect01) ; 
                    __m256i prod02 = _mm256_mullo_epi32(Elemento_LIN_A , vect02) ; 
                    __m256i prod03 = _mm256_mullo_epi32(Elemento_LIN_A , vect03) ; 
                    __m256i prod04 = _mm256_mullo_epi32(Elemento_LIN_A , vect04) ; 
                    __m256i prod05 = _mm256_mullo_epi32(Elemento_LIN_A , vect05) ; 
                    __m256i prod06 = _mm256_mullo_epi32(Elemento_LIN_A , vect06) ; 
                    __m256i prod07 = _mm256_mullo_epi32(Elemento_LIN_A , vect07) ;
   /*               __m256i prod08 = _mm256_mullo_epi32(Elemento_LIN_A , vect08) ; 
                    __m256i prod09 = _mm256_mullo_epi32(Elemento_LIN_A , vect09) ; 
                    __m256i prod10 = _mm256_mullo_epi32(Elemento_LIN_A , vect10) ; 
                    __m256i prod11 = _mm256_mullo_epi32(Elemento_LIN_A , vect11) ; 
                    __m256i prod12 = _mm256_mullo_epi32(Elemento_LIN_A , vect12) ; 
                    __m256i prod13 = _mm256_mullo_epi32(Elemento_LIN_A , vect13) ; 
                    __m256i prod14 = _mm256_mullo_epi32(Elemento_LIN_A , vect14) ; 
                    __m256i prod15 = _mm256_mullo_epi32(Elemento_LIN_A , vect15) ;  */

                    soma256_0 = _mm256_add_epi32(soma256_0 , prod00) ;
                    soma256_1 = _mm256_add_epi32(soma256_1 , prod01) ; 
                    soma256_2 = _mm256_add_epi32(soma256_2 , prod02) ; 
                    soma256_3 = _mm256_add_epi32(soma256_3 , prod03) ; 
                    soma256_4 = _mm256_add_epi32(soma256_4 , prod04) ;  
                    soma256_5 = _mm256_add_epi32(soma256_5 , prod05) ; 
                    soma256_6 = _mm256_add_epi32(soma256_6 , prod06) ; 
                    soma256_7 = _mm256_add_epi32(soma256_7 , prod07) ; 
        /*          soma256_8 = _mm256_add_epi32(Elemento_LIN_A , prod08) ; 
                    soma256_9 = _mm256_add_epi32(Elemento_LIN_A , prod09) ; 
                    soma256_10 = _mm256_add_epi32(Elemento_LIN_A , prod10) ; 
                    soma256_11 = _mm256_add_epi32(Elemento_LIN_A , prod11) ; 
                    soma256_12 = _mm256_add_epi32(Elemento_LIN_A , prod12) ; 
                    soma256_13 = _mm256_add_epi32(Elemento_LIN_A , prod13) ; 
                    soma256_14 = _mm256_add_epi32(Elemento_LIN_A , prod14) ; 
                    soma256_15 = _mm256_add_epi32(Elemento_LIN_A , prod15) ;   */
                }  
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j] , soma256_0) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+8] , soma256_1) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+16] , soma256_2) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+24] , soma256_3) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+32] , soma256_4) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+40] , soma256_5) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+48] , soma256_6) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+56] , soma256_7) ; 
     /*         _mm256_storeu_si256((__m256i*)&matriz_C[i][j+64] , soma256_8) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+72] , soma256_9) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+80] , soma256_10) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+88] , soma256_11) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+96] , soma256_12) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+104] , soma256_13) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+112] , soma256_14) ; 
                _mm256_storeu_si256((__m256i*)&matriz_C[i][j+120] , soma256_15) ;   */
            }
        }    

       
    return 0 ; 
}