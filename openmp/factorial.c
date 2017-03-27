#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int facto(int nb)
{
    int fac = 1;
    int n;
#pragma omp parallel for reduction(* : fac)
    for (n = 2; n <= nb; n++)
    {
        fac *= n;
    }
    return fac;
}

int main()
{
    printf("10!=%d\n", facto(10));
}