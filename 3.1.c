#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

void printIntArray(int*buffer, int length){
	int i;
	for (i=0;i<length;i++){
		printf("%d ", buffer[i]);
	}
	printf("\n");
}
int main(){

	MPI_Init(NULL,NULL);
	MPI_Datatype type;
	MPI_Status status;
	int buffer[10];
	int i;
	for (i=0;i<10;i++){
		buffer[i] = i;
	}
	MPI_Type_contiguous(10, MPI_INT, &type);
	MPI_Type_commit(&type);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		MPI_Send(buffer, 1, type, 1, 0 , MPI_COMM_WORLD);
		printf("Process %d: sended \n", rank);
	} else {
		MPI_Recv(buffer, 1, type, 0, 0, MPI_COMM_WORLD, &status);
		printf("Process %d: received \n", rank);
		printIntArray(buffer, 10);
	}

	MPI_Finalize();
	return EXIT_SUCCESS;
}