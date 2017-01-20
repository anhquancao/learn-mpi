#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
	int rank;
	int data;
	int tag = 0;
	
	int size;
	MPI_Status status, send_status1;
	MPI_Request request, send_req1;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (rank != 0){
		MPI_Recv(&data, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
		printf("process %d received %d from process %d\n", rank, data, rank-1);
	} else {
		data = 22;
	}
	
	MPI_Send(&data, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

	// process rank 0 receive from the last process
	if (rank == 0) {
		MPI_Recv(&data, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
		printf("process %d received %d from process %d\n", rank, data, size-1);
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}
