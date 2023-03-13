#include<stdio.h>
#include<immintrin.h>
#include<stdlib.h>

int main(int argc , char* argv[])
{
   
    const int TAM = atoi(argv[1]) ; 
    const int LIN = TAM ; 
    const int COL = TAM ; 

    float** mi = (float**)_mm_malloc(LIN * sizeof(float*) , 32) ; 
    float** mb = (float**)_mm_malloc(LIN * sizeof(float*) , 32) ; 
    float** mc = (float**)_mm_malloc(LIN * sizeof(float*) , 32) ;  

        for(int i=0 ; i<LIN ; i++)
            mi[i] = (float*)_mm_malloc(COL * sizeof(float) , 32) ;   
        
        for(int i=0 ; i<LIN ; i++)
            mb[i] =  (float*)_mm_malloc(COL * sizeof(float) , 32) ;

        for(int i=0 ; i<LIN ; i++)
            mc[i] =  (float*)_mm_malloc(COL * sizeof(float) , 32) ;

        for(int i=0 ; i<LIN ; i++)
        {
            for(int j=0 ; j<COL ; j++)
            {
                if(i==j) mi[i][j] = 1 ; 
                else mi[i][j] = 0 ; 

                mb[i][j] = (rand() % 1000) ; 
                mc[i][j] = 0 ; 
            }
        }

for(int i = 0 ; i<LIN ; i++)
        {
            for(int j = 0 ; j<COL ; j+=32) // Vetorização de 32 elementos  
            {
                __m256i soma256_0 = _mm256_setzero_si256();
                __m256i soma256_1 = _mm256_setzero_si256();
                __m256i soma256_2 = _mm256_setzero_si256();
                __m256i soma256_3 = _mm256_setzero_si256();

                for(int k = 0 ; k<LIN ; k+=2)
                {
                    // VETOR COM OS ELEMENTOS IGUAL (ELEMENTO DA MATRIZ I)a 
                    __m256i Elemento_LIN = _mm256_set1_epi32(mi[i][k]) ; 

                    __m256i vect00 = _mm256_loadu_si256((__m256i*)&mb[k][j]) ;
                    __m256i vect01 = _mm256_loadu_si256((__m256i*)&mb[k][j+8]) ;  
                    __m256i vect02 = _mm256_loadu_si256((__m256i*)&mb[k][j+16]) ; 
                    __m256i vect03 = _mm256_loadu_si256((__m256i*)&mb[k][j+24]) ;

                    //MULTIPLICO O ELEMENTO DA LINHA A POR TODOS OS 32 ELEMENTOS DAS COLUNAS SUBSEQUENTES
                    __m256i prod00 = _mm256_mullo_epi32(Elemento_LIN , vect00) ; 
                    __m256i prod01 = _mm256_mullo_epi32(Elemento_LIN , vect01) ; 
                    __m256i prod02 = _mm256_mullo_epi32(Elemento_LIN , vect02) ; 
                    __m256i prod03 = _mm256_mullo_epi32(Elemento_LIN , vect03) ; 

                    //SOMA LINHA 8 EM 8 
                    soma256_0 = _mm256_add_epi32(soma256_0 , prod00) ;
                    soma256_1 = _mm256_add_epi32(soma256_1 , prod01) ; 
                    soma256_2 = _mm256_add_epi32(soma256_2 , prod02) ; 
                    soma256_3 = _mm256_add_epi32(soma256_3 , prod03) ;

                    //REUTILIZAÇÃO DE REGISTRADORES
                    Elemento_LIN = _mm256_set1_epi32(mi[i][k+1]) ; 

                    vect00 = _mm256_loadu_si256((__m256i*)&mb[k+1][j]) ;
                    vect01 = _mm256_loadu_si256((__m256i*)&mb[k+1][j+8]) ;  
                    vect02 = _mm256_loadu_si256((__m256i*)&mb[k+1][j+16]) ; 
                    vect03 = _mm256_loadu_si256((__m256i*)&mb[k+1][j+24]) ;

                    prod00 = _mm256_mullo_epi32(Elemento_LIN , vect00) ; 
                    prod01 = _mm256_mullo_epi32(Elemento_LIN , vect01) ; 
                    prod02 = _mm256_mullo_epi32(Elemento_LIN , vect02) ; 
                    prod03 = _mm256_mullo_epi32(Elemento_LIN , vect03) ; 
                    
                    soma256_0 = _mm256_add_epi32(soma256_0 , prod00) ;
                    soma256_1 = _mm256_add_epi32(soma256_1 , prod01) ; 
                    soma256_2 = _mm256_add_epi32(soma256_2 , prod02) ; 
                    soma256_3 = _mm256_add_epi32(soma256_3 , prod03) ;

                }  
                    _mm256_storeu_si256((__m256i*)&mc[i][j] , soma256_0) ; 
                    _mm256_storeu_si256((__m256i*)&mc[i][j+8] , soma256_1) ; 
                    _mm256_storeu_si256((__m256i*)&mc[i][j+16] , soma256_2) ; 
                    _mm256_storeu_si256((__m256i*)&mc[i][j+24] , soma256_3) ;
            }
        }
        
        __m256i all_one = _mm256_set1_epi32(1) ; 
        for(int i=0 ; i<LIN ; i++)
        {
            for(int j=0 ; j<COL ; j+=32)
            {
                __m256i sum = _mm256_setzero_si256() ; 
                //MATRIZ RESULTANTE
                __m256i mc_8ints_0 = _mm256_loadu_si256((__m256i*)&mc[i][j]) ;
                __m256i mc_8ints_1 = _mm256_loadu_si256((__m256i*)&mc[i][j + 8]) ; 
                __m256i mc_8ints_2 = _mm256_loadu_si256((__m256i*)&mc[i][j + 16]) ; 
                __m256i mc_8ints_3 = _mm256_loadu_si256((__m256i*)&mc[i][j + 24]) ; 

                //MATRIZ ALEATORIA
                __m256i mb_8ints_0 = _mm256_loadu_si256((__m256i*)&mb[i][j]) ;
                __m256i mb_8ints_1 = _mm256_loadu_si256((__m256i*)&mb[i][j + 8]) ; 
                __m256i mb_8ints_2 = _mm256_loadu_si256((__m256i*)&mb[i][j + 16]) ;  
                __m256i mb_8ints_3 = _mm256_loadu_si256((__m256i*)&mb[i][j + 24]) ; 

                //SE OS PEDAÇOS SAO IGUAIS, ENTAO SUB DA ZERO
                __m256i verif_iguais_0 = _mm256_sub_epi32(mc_8ints_0 , mb_8ints_0) ; 
                __m256i verif_iguais_1 = _mm256_sub_epi32(mc_8ints_1 , mb_8ints_1) ; 
                __m256i verif_iguais_2 = _mm256_sub_epi32(mc_8ints_2 , mb_8ints_2) ; 
                __m256i verif_iguais_3 = _mm256_sub_epi32(mc_8ints_3 , mb_8ints_3) ;

                sum = _mm256_add_epi32(sum , verif_iguais_0) ; 
                sum = _mm256_add_epi32(sum , verif_iguais_1) ; 
                sum = _mm256_add_epi32(sum , verif_iguais_2) ; 
                sum = _mm256_add_epi32(sum , verif_iguais_3) ; 
                
                int IF_ZERO_SET_ONE ; 
                IF_ZERO_SET_ONE = _mm256_testc_si256(all_one , sum) ; 

                if(IF_ZERO_SET_ONE != 1)
                    exit(1) ;      

            }
        }

    return 0 ; 
}