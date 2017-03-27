#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m1[3][2] = {
        {1, 2},
        {2, 3},
        {4, 5}};
    int m2[2][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}};

    int result[3][4];
    int r, c;
    #pragma omp for
    // #pragma omp parallel for
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 4; c++)
        {
            int temp = 0,k;
            #pragma omp parallel for reduction (+:temp) private(k)
            for (k=0;k<2;k++){
                temp += m1[r][k] * m2[k][c];
            }
            result[r][c] =  temp;
        }
    }
    #pragma omp barrier
    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 4; c++)
        {
            printf("%d ",result[r][c]);
        }
        printf("\n");
    }
}