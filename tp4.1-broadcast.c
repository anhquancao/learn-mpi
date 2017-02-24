#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
    MPI_Init(NULL, NULL);
    int rank;
    int data;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        data = 999;
        printf("Process 0 send %d\n", data);
        MPI_Bcast(&data, 1, MPI_INT, 0 , MPI_COMM_WORLD);
    } else {
        MPI_Bcast(&data, 1, MPI_INT, 0 , MPI_COMM_WORLD);
        printf("Process %d received: %d\n", rank, data);
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}