#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int nb)
{
    int fac = 1, i;
    #pragma omp parallel for
    for (i = 2; i <= nb; i++)
    {
        #pragma omp atomic
        fac*=i;
    }
    return fac;
}

int main()
{
    printf("10!=%d\n",factorial(10));
}