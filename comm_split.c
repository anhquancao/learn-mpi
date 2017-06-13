#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int color = rank / 4;

    MPI_Comm row_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &row_comm);

    int row_rank, row_size;
    MPI_Comm_rank(row_comm, &row_rank);
    MPI_Comm_size(row_comm, &row_size);
    printf("WORLD RANK/SIZE: %d/%d \t ROW RANK/SIZE: %d/%d\n", rank, size, row_rank, row_size);
    MPI_Comm_free(&row_comm);
    MPI_Finalize();
    return EXIT_SUCCESS;
}