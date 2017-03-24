#include <omp.h>
#include <stdio.h>
#include<stdlib.h>
int main() {
    int numthreads, tid, i;
    #pragma omp parallel private ( tid ) shared ( numthreads )
    {
        tid = omp_get_thread_num();
        
        tid = omp_get_thread_num();
        #pragma omp for ordered schedule( static, 2)
        for( i = 0 ; i < 12; i++ ) {
            #pragma omp ordered
            printf("Hello World from thread = %d \n", tid );
        }
    }   
    return EXIT_SUCCESS;
}