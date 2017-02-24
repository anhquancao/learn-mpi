#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    MPI_Init(NULL, NULL);
    int rank, i;
    int numberPerProc = 1014;
    int data[numberPerProc];
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (i = 0; i < numberPerProc; i++)
    {
        srand(time(NULL));
        data[i] = rand();
    }

    int max = data[0];
    for (i = 0; i < numberPerProc; i++)
    {
        if (data[i] > max)
        {
            max = data[i];
        }
    }
    printf("process %d: %d\n", rank, max);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int recvData[size];

    MPI_Gather(&max, 1, MPI_INT, recvData, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Process 0\n");
        for (i = 0; i < size; i++)
        {
            printf("process %d: %d\n",rank, recvData[i]);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}