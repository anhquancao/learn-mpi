#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    int data, i, tid;
    #pragma omp parallel private (tid, data) 
    {
        tid = omp_get_thread_num();

        #pragma omp for 
        for (i = 0; i < 24;i++){
            data = i * i;
            printf("Thread %d: %d\n", tid, data);
        }
    }
    return EXIT_SUCCESS;
}