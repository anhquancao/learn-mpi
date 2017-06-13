#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#define PING_PONG_LIMIT 20
int main()
{
    MPI_Init(NULL, NULL);
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int count = 0;
    int partner_rank = (rank + 1) % 2;
    while (count < PING_PONG_LIMIT)
    {
        if (rank == count % 2)
        {
            count++;
            MPI_Send(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("%d sent and incremented count %d to %d\n",
                   rank, count, partner_rank);
        }
        else
        {
            MPI_Recv(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d received count %d from %d\n",
                   rank, count, partner_rank);
        }
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}