#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define ROW 3
#define COL 3

void printMatrix(float matrix[][COL], int rowsNum, int colsNum)
{
    int r, c;
    for (r = 0; r < rowsNum; r++)
    {
        for (c = 0; c < colsNum; c++)
        {
            printf("%.1f ", matrix[r][c]);
        }
        printf("\n");
    }
}

int main()
{

    float a[ROW][COL] = {
        {3, 5, 7},
        {2, 4, 8},
        {1, -2, 3}};

    int r, c, r2;
    omp_set_num_threads(3);
    for (r = 0; r < ROW; r++)
    {
        #pragma omp parallel for 
        for (r2 = r + 1; r2 < ROW; r2++)
        {
            printf("thread %d\n",omp_get_thread_num());
            float factor = (float)a[r][r] / a[r2][r];
            for (c = 0; c < COL; c++)
            {
                a[r2][c] = a[r2][c] * factor - a[r][c];
            }
        }
    }
    for (r = ROW-1; r >= 0; r--)
    {
        #pragma omp parallel for
        for (r2 = r - 1; r2 >= 0; r2--)
        {

            float factor = (float)a[r][r] / a[r2][r];
            for (c = 0; c < COL; c++)
            {
                a[r2][c] = a[r2][c] * factor - a[r][c];
            }
        }
    }
    printMatrix(a, ROW, COL);
    return EXIT_SUCCESS;
}