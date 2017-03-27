#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tmp = 22;
#pragma omp parallel for lastprivate(tmp)
    for (int j = 0; j < 1; ++j)
    {
        tmp += 20;
    }
    printf("tmp=%d\n", tmp);
}