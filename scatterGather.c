#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int randomRange(int min, int max)
{
    double scale = (double)rand() / RAND_MAX;
    return (max - min + 1) * scale + min;
}

int main()
{
    MPI_Init(NULL, NULL);
    int rank, size;
    srand(time(NULL));

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numPerProc = 1024;
    int recvData[numPerProc];
    int *data;
    double recvAvg[size];
    int i;

    if (rank == 0)
    {
        data = (int *)malloc(sizeof(int) * numPerProc * size);
        for (i = 0; i < numPerProc * size; i++)
        {
            data[i] = randomRange(-100, 100);
        }
    }

    MPI_Scatter(data, numPerProc, MPI_INT, recvData, numPerProc, MPI_INT, 0, MPI_COMM_WORLD);
    int sum = 0;
    for (i = 0; i < numPerProc; i++)
    {

        sum += recvData[i];
    }
    double avg = (double)sum / numPerProc;
    printf("process %d: %f\n", rank, avg);

    MPI_Gather(&avg, 1, MPI_DOUBLE, recvAvg, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (i = 0; i < size; i++)
        {
            printf("process %d: %f\n", rank, recvAvg[i]);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}