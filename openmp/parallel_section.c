#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                printf("Hello\n");
            }
#pragma omp section
            {
                printf("Hello2\n");
            }
        }
    }
}