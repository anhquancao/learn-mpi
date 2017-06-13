#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    MPI_Request request1, request2;
    int number1, number2, rank, size;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    number1 = (rank + 1) * 100;
    int right = (rank + 1) % size;
    int left = rank - 1;
    number1 = rank;
    if (left == -1)
    {
        left = size - 1;
    }
    MPI_Isend(&number1, 1, MPI_INT, right, 0, MPI_COMM_WORLD, &request1);
    MPI_Irecv(&number2, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &request2);
    MPI_Wait(&request1, &status);
    printf("Process %d send %d from to %d\n", rank, number1, right);
    MPI_Wait(&request2, &status);
    printf("Process %d receive %d from process %d\n", rank, number2, left);
    MPI_Finalize();

    return EXIT_SUCCESS;
}