#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    #pragma omp parallel num_threads(2)
    {
        printf("hello1\n");
        #pragma omp parallel num_threads(2)
        printf("hello\n");
    }
}