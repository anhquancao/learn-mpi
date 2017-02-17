// Implement a master-slave static skeleton using collective 
// operations to distribute the data and retrieve the results.

#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(){
	MPI_Init(NULL,NULL);
	int rank, size, i;
	int *sendData;
	int recvData;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		sendData = (int*)malloc(sizeof(int)*size);
		for (i=0; i<size; i++){
			sendData[i] = i;
		}
	}

	MPI_Scatter(sendData, 1, MPI_INT, &recvData, 1,MPI_INT, 0, MPI_COMM_WORLD);

	printf("process %d: %d\n", rank, recvData);

	MPI_Finalize();
	return EXIT_SUCCESS;
}