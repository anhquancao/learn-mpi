// Ex 3.2
// 1. Create an MPI derived type containing non-contiguous integers:
// - one integer per block
// - the stride (number of elements between the beginning of a block and the beginning of the next) is equal to a parameter N
// The number of blocks is equal to a number M
// 2. Write a program where two processes each have a matrix of M rows and N columns stored linearly in a one-dimensional array.
// These processes exchange the first elements of each row:
// (A) Implement it with communications sending elements one by one. 
// How many messages does this method involve? What is the volume of data (total and per message) sent?
// (B) Implement it using the derived type you just defined. 
// Compare the number of messages and the volume of data carried with the previous implementation.

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main() {
	MPI_Init(NULL,NULL);
	int rank, i;
	MPI_Status status;

	int row = 2; // number of blocks
	int col = 3; // number of elements per block
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Datatype type;
	MPI_Type_vector(2, 1, 3, MPI_INT, &type);
	MPI_Type_commit(&type);

	// matrix: 
	// [1,2,3]
	// [4,5,6]
	int matrix[6];
	if (rank == 0) {
		for (i=0 ; i < 6; i++) {
			matrix[i] = i+1;
		}
		MPI_Send(matrix, 1, type, 1, 0, MPI_COMM_WORLD);
		printf("Matrix sended");
	} else {
		MPI_Recv(matrix, 1, type, 0, 0, MPI_COMM_WORLD, &status);
		for (i=0 ; i < 6; i++) {
			printf("%d ",matrix[i]);
		}
		printf("\n");
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}