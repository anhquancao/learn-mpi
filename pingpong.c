#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char** argv){
	int rank;
	int token;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (0 == rank){
		token = 23;
		while(1){
			MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			MPI_Recv(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
			printf("Process 0 received number %d from process 1\n",token);
		}

	} else {
		if (rank == 1) {
			while(1) {
				MPI_Recv(&token, 1, MPI_INT, 0,0, MPI_COMM_WORLD, &status);
				printf("Process 1 received number %d from process 0\n",token);
				token += 1;
				MPI_Send(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
	}
	MPI_Finalize();
	return EXIT_SUCCESS;
}
