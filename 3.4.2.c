// Implement a master-slave static skeleton using collective 
// operations to distribute the data and retrieve the results.

#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(){
	MPI_Init(NULL,NULL);
	int rank, size, i;
	int *recvData;
	int sendData;

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		recvData = (int*)malloc(sizeof(int)*size);
	}
	sendData = rank;
	MPI_Gather(&sendData, 1, MPI_INT, recvData, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		for (i=0; i<size; i++) {
			printf("%d \n",recvData[i]);
		}	
	}
	
	MPI_Finalize();
	return EXIT_SUCCESS;
}