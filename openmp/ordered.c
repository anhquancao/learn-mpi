#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    int numthreads, i, tid;

    #pragma omp parallel private (tid) shared (numthreads) 
    {
        tid = omp_get_thread_num();
        numthreads = omp_get_num_threads();
        #pragma omp for ordered schedule (dynamic, 2)
        for (i = 0; i < numthreads;i++){
            #pragma omp ordered
            printf("Hello World from thread = %d \n", tid );

        }
    }
    return EXIT_SUCCESS;
}