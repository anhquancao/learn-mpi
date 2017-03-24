#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int a[10], i;
    for (i = 0; i < 10; i++)
    {
        a[i] = (int)((double)rand() * MAX / (double)RAND_MAX);
        printf("%d\n", a[i]);
    }
    int max = a[0];
    #pragma omp parallel shared(max)
    {
        #pragma omp for
        for (i=0;i<10;i++){
            #pragma omp critical
            {
                printf("Thread: %d\n", omp_get_thread_num());
                if (a[i] > max) {
                    max = a[i];
                }
            }
        }
    }
    printf("Max=%d\n",max);
    
}