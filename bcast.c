#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
	MPI_Init(NULL,NULL);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int data;
	if (rank == 0){
		data = 100;
		printf("process %d broadcast %d\n", rank, data);
		MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	} else {
		MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("process %d received %d\n", rank, data);
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}