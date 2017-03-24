#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX 300


void init(int *tab, int taille)
{
    int i;
    for (i = 0; i < taille; i++) {
        tab[i] = (int)((double)rand() * MAX / (double)RAND_MAX);
    }
}

int main()
{
    int *data, localMax, globalMax, i, tid;
    data = (int*)malloc(sizeof(int)*10);
    srand(time(NULL));
    init(data,10);
    localMax = data[0];
    globalMax = data[0];
    #pragma omp parallel private(localMax, tid) shared (data, globalMax) 
    {
        tid = omp_get_thread_num();
        #pragma omp for
        for (i=0; i<10; i++){
            printf("Thread %d: %d\n", tid, i);
            if (localMax < data[i]) {
                localMax = data[i];
            }
        }
        printf("Thread %d - max %d\n", tid, localMax);
        #pragma omp critical(abc)
        {
            printf("Thread %d: local max: %d, global max: %d\n", tid, localMax, globalMax);
            if (globalMax < localMax){
                globalMax = localMax;
            }
        }
    }
    printf("Global max: %d\n", globalMax);
}