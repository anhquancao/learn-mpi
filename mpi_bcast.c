#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
	int size, rank, token;
	MPI_Init(NULL,NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, & rank);

	if (rank == 0) {
		token = 100;
	}

	MPI_Bcast(&token, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("process %d: %d\n", rank, token);

	MPI_Finalize();
	return EXIT_SUCCESS;
}