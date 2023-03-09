#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[])
{
    const int TAM = atoi(argv[1]) ; // TAMANHO MATRIZ QUADRADA  
    const int LIN = TAM ; 
    const int COL = TAM ; 

    float** matriz_A = (float**)malloc(LIN * sizeof(float*)) ; 
    float** matriz_B = (float**)malloc(LIN * sizeof(float*)) ;
    float** matriz_C = (float**)malloc(LIN * sizeof(float*)) ;  
        // AQUI EU CRIO MINHA MATRIZ DINAMICAMENTE
        //Utilizei aligned_malloc para alinar a memória em chunks de 64 bytes == 512bits
        for(int i=0 ; i<LIN ; i++)
            matriz_A[i] = (float*)aligned_alloc(32 ,COL * sizeof(float)) ;  
        
        for(int i=0 ; i<LIN ; i++)
            matriz_B[i] = (float*)aligned_alloc(32 ,COL * sizeof(float)) ; 

        for(int i=0 ; i<LIN ; i++)
            matriz_C[i] = (float*)aligned_alloc(32 ,COL * sizeof(float)) ; 
        
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
     time_t t_init = time(NULL) ; 
        for(int i = 0 ; i<LIN ; i++)
        {
            for(int j = 0 ; j<COL ; j+=128) // Irei vetorizar 128 em 128 elementos. Matriz máxima deve ser de 
            {
                __m256 soma256_0 = _mm256_setzero_ps();
                __m256 soma256_1 = _mm256_setzero_ps();
                __m256 soma256_2 = _mm256_setzero_ps();
                __m256 soma256_3 = _mm256_setzero_ps();
                __m256 soma256_4 = _mm256_setzero_ps();
                __m256 soma256_5 = _mm256_setzero_ps();
                __m256 soma256_6 = _mm256_setzero_ps();
                __m256 soma256_7 = _mm256_setzero_ps();
                __m256 soma256_8 = _mm256_setzero_ps();
                __m256 soma256_9 = _mm256_setzero_ps();
                __m256 soma256_10 = _mm256_setzero_ps();
                __m256 soma256_11 = _mm256_setzero_ps();
                __m256 soma256_12 = _mm256_setzero_ps();
                __m256 soma256_13 = _mm256_setzero_ps();
                __m256 soma256_14 = _mm256_setzero_ps();
                __m256 soma256_15 = _mm256_setzero_ps(); 

              
                for(int k = 0 ; k<LIN ; k++)
                {
                    // Vetor com elementos iguais.
                    __m256 Elemento_LIN_A = _mm256_set1_ps(matriz_A[i][k]) ; 

                    __m256 vect00 = _mm256_loadu_ps((float*)&matriz_B[k][j]) ;
                    __m256 vect01 = _mm256_loadu_ps((float*)&matriz_B[k][j+8]) ;  
                    __m256 vect02 = _mm256_loadu_ps((float*)&matriz_B[k][j+16]) ; 
                    __m256 vect03 = _mm256_loadu_ps((float*)&matriz_B[k][j+24]) ; 
                    __m256 vect04 = _mm256_loadu_ps((float*)&matriz_B[k][j+32]) ; 
                    __m256 vect05 = _mm256_loadu_ps((float*)&matriz_B[k][j+40]) ; 
                    __m256 vect06 = _mm256_loadu_ps((float*)&matriz_B[k][j+48]) ;
                    __m256 vect07 = _mm256_loadu_ps((float*)&matriz_B[k][j+56]) ;
                    __m256 vect08 = _mm256_loadu_ps((float*)&matriz_B[k][j+64]) ;  
                    __m256 vect09 = _mm256_loadu_ps((float*)&matriz_B[k][j+72]) ; 
                    __m256 vect10 = _mm256_loadu_ps((float*)&matriz_B[k][j+80]) ; 
                    __m256 vect11 = _mm256_loadu_ps((float*)&matriz_B[k][j+88]) ; 
                    __m256 vect12 = _mm256_loadu_ps((float*)&matriz_B[k][j+96])  ; 
                    __m256 vect13 = _mm256_loadu_ps((float*)&matriz_B[k][j+104]) ; 
                    __m256 vect14 = _mm256_loadu_ps((float*)&matriz_B[k][j+112]) ;
                    __m256 vect15 = _mm256_loadu_ps((float*)&matriz_B[k][j+120]) ;  

                    //MULTIPLICO O ELEMENTO DA LINHA A POR TODOS OS ELEMENTOS 128 COLUNAS SUBSEQUENTES
                    __m256 prod00 = _mm256_mul_ps(Elemento_LIN_A , vect00) ; 
                    __m256 prod01 = _mm256_mul_ps(Elemento_LIN_A , vect01) ; 
                    __m256 prod02 = _mm256_mul_ps(Elemento_LIN_A , vect02) ; 
                    __m256 prod03 = _mm256_mul_ps(Elemento_LIN_A , vect03) ; 
                    __m256 prod04 = _mm256_mul_ps(Elemento_LIN_A , vect04) ; 
                    __m256 prod05 = _mm256_mul_ps(Elemento_LIN_A , vect05) ; 
                    __m256 prod06 = _mm256_mul_ps(Elemento_LIN_A , vect06) ; 
                    __m256 prod07 = _mm256_mul_ps(Elemento_LIN_A , vect07) ;
                    __m256 prod08 = _mm256_mul_ps(Elemento_LIN_A , vect08) ; 
                    __m256 prod09 = _mm256_mul_ps(Elemento_LIN_A , vect09) ; 
                    __m256 prod10 = _mm256_mul_ps(Elemento_LIN_A , vect10) ; 
                    __m256 prod11 = _mm256_mul_ps(Elemento_LIN_A , vect11) ; 
                    __m256 prod12 = _mm256_mul_ps(Elemento_LIN_A , vect12) ; 
                    __m256 prod13 = _mm256_mul_ps(Elemento_LIN_A , vect13) ; 
                    __m256 prod14 = _mm256_mul_ps(Elemento_LIN_A , vect14) ; 
                    __m256 prod15 = _mm256_mul_ps(Elemento_LIN_A , vect15) ;   

                    soma256_0 = _mm256_add_ps(soma256_0 , prod00) ;
                    soma256_1 = _mm256_add_ps(soma256_1 , prod01) ; 
                    soma256_2 = _mm256_add_ps(soma256_2 , prod02) ; 
                    soma256_3 = _mm256_add_ps(soma256_3 , prod03) ; 
                    soma256_4 = _mm256_add_ps(soma256_4 , prod04) ;  
                    soma256_5 = _mm256_add_ps(soma256_5 , prod05) ; 
                    soma256_6 = _mm256_add_ps(soma256_6 , prod06) ; 
                    soma256_7 = _mm256_add_ps(soma256_7 , prod07) ; 
                    soma256_8 = _mm256_add_ps(soma256_8 , prod08) ; 
                    soma256_9 = _mm256_add_ps(soma256_9 , prod09) ; 
                    soma256_10 = _mm256_add_ps(soma256_10 , prod10) ; 
                    soma256_11 = _mm256_add_ps(soma256_11 , prod11) ; 
                    soma256_12 = _mm256_add_ps(soma256_12 , prod12) ; 
                    soma256_13 = _mm256_add_ps(soma256_13 , prod13) ; 
                    soma256_14 = _mm256_add_ps(soma256_14 , prod14) ; 
                    soma256_15 = _mm256_add_ps(soma256_15 , prod15) ;   
                }  
                _mm256_storeu_ps((float*)&matriz_C[i][j] , soma256_0) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+8] , soma256_1) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+16] , soma256_2) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+24] , soma256_3) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+32] , soma256_4) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+40] , soma256_5) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+48] , soma256_6) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+56] , soma256_7) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+64] , soma256_8) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+72] , soma256_9) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+80] , soma256_10) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+88] , soma256_11) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+96] , soma256_12) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+104] , soma256_13) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+112] , soma256_14) ; 
                _mm256_storeu_ps((float*)&matriz_C[i][j+120] , soma256_15) ;   
            }
        }
        time_t t_fim = time(NULL) ; 

        float TIME_Mul = difftime(t_fim,t_init) ; 
        printf("%f\n" , TIME_Mul) ;  
       
    return 0 ; 
}