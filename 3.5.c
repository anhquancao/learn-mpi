// Implement a dynamic master-slave skeleton in pull mode: slaves request work from the master when 
// sending a new result or initialization, and the master sends data (an array of integers) 
// as long as it in a.

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define WORKTAG     1
#define REQUESTTAG     2
#define DIETAG     3

void master(){
	int	ntasks, rank, work,i;
	int request;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

	for (work = 0; work < 10; work++) {

		// receive request
		MPI_Recv(&request,1, MPI_INT, MPI_ANY_SOURCE, REQUESTTAG, MPI_COMM_WORLD, &status);
		printf("process %d request for work %d\n",request,work);
		// send the work
		MPI_Send(&work, 1, MPI_INT, status.MPI_SOURCE, WORKTAG, MPI_COMM_WORLD);
	}
	
	for (rank = 1; rank < ntasks; ++rank) {
		printf("master receive %d send \n", rank);
		MPI_Recv(&request, 1, MPI_INT, rank, REQUESTTAG, MPI_COMM_WORLD, &status);
	}

	for (rank = 1; rank < ntasks; ++rank) {
		printf("master send die to %d  \n", rank);
		MPI_Send(0, 0, MPI_INT, rank, DIETAG, MPI_COMM_WORLD);
	}
}

void slave(int rank) {
	int request = rank;
	int work;
	MPI_Status status;
	while (1)	{
		printf("process %d send \n", rank);
		MPI_Send(&request, 1, MPI_INT, 0, REQUESTTAG, MPI_COMM_WORLD);
		printf("process %d receive \n", rank);
		MPI_Recv(&work, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if (status.MPI_TAG == WORKTAG) {
			printf("process %d: work %d\n",rank, work);
		} else {
			printf("die");
			return;
		}
	}
}

int main(){
	MPI_Init(NULL,NULL);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		master();
	}else {
		slave(rank);
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}