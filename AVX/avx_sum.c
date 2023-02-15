#include<immintrin.h>
#include<stdio.h>


int main()
{
    __m256 v1 = _mm256_set_ps(1,2,3,4,5,6,7,8) ; 
    __m256 v2 = _mm256_set_ps(1,2,3,4,5,6,7,8) ; 

    __m256 sum = _mm256_add_ps (v1 , v2) ; 
    float* f = (float*)&sum;

   printf("%.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f" , sum[0] , sum[1] , sum[2] , sum[3] , sum[4] , sum[5] , sum[6] , sum[7]) ; 

    return 0 ; 
}