
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
void lafonction(int *data)
{
/* Calcul */
#pragma omp critical(sectioncritique)
    {
        *data = rand();
        
    }
}
int main()
{
    int data1, data2, tid;
#pragma omp parallel private (tid)
    {
        tid = omp_get_thread_num();
        lafonction(&data1);
        printf("thread=%d, data1=%d\n", tid, data1);
        /* Un peu de calcul */
        lafonction(&data2);
        printf("thread=%d, data2=%d\n", tid, data2);
    }
    printf("data1=%d, data2=%d\n", data1, data2);
    return EXIT_SUCCESS;
}